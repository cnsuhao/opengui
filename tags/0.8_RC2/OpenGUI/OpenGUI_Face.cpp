// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_Face.h"
#include "OpenGUI_FaceDef.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//############################################################################
	// We're doing this to ensure that memory destroyed within OpenGUI is also created within OpenGUI
	FacePtr Face::Create( const std::string& faceName, const FaceDef& faceDefinition ) {
		return new Face( faceName, faceDefinition );
	}
	//############################################################################
	Face::Face( const std::string& faceName, const FaceDef& faceDefinition ): Metric( faceDefinition.Metric ) {
		mName = faceName;

		//Note: these may be a waste of time, since they aren't always accurate to begin with
		// (they have the potential to report smaller sizes than they should)
		size_t initCols = faceDefinition.getColSizeEstimate();
		size_t initRows = faceDefinition.getRowSizeEstimate();

		// Construct a grid to represent the rows and columns needed
		typedef AutoArray2D<const SliceDef*> SliceDefArray;
		SliceDefArray tmpSDP_Grid; // Addressed as tmpSDP_Grid[Col][Row]
		tmpSDP_Grid.growSize( initCols, initRows, 0 ); // grow to an initial size to save some time

		//populate that grid, growing if necessary
		size_t row, col;
		FaceDef::SliceRowDefVector::const_iterator row_iter, row_iterend = faceDefinition.Rows.end();
		for ( row = 0, row_iter = faceDefinition.Rows.begin(); row_iter != row_iterend; row_iter++, row++ ) {
			const FaceDef::SliceDefVector& curRow = ( *row_iter );
			FaceDef::SliceDefVector::const_iterator col_iter, col_iterend = curRow.end();
			for ( col = 0, col_iter = curRow.begin(); col_iter != col_iterend; col_iter++, col++ ) {
				while ( tmpSDP_Grid[col][row] )col++; // advance past cells that are already taken
				const SliceDef& slice = ( *col_iter );
				size_t colspan = slice.ColSpan;
				size_t rowspan = slice.RowSpan;
				// mark all cells we cover to prevent anyone else from using them
				for ( size_t i = 0; i <= colspan; i++ ) {
					for ( size_t j = 0; j <= rowspan; j++ ) {
						tmpSDP_Grid.growSize( col + i, row + j, 0 ); // always perform a safe grow so new entries are initialized to 0
						tmpSDP_Grid[col+i][row+j] = &slice;
					}
				}
			}
		}

		tmpSDP_Grid.lock(); // lock the array from size changes

		// we now have the final grid size, so re-dim the columns and rows
		mColDims.resize( tmpSDP_Grid.getSizeX() );
		mRowDims.resize( tmpSDP_Grid.getSizeY() );

		// the upcoming section is a good opportunity to build the final SliceList
		// but we temporarily need to hang on to some extra information
		typedef std::map<const SliceDef*, Slice*> SliceMap; // maps slice definitions to their final entry in the slice list
		SliceMap sliceMap;

		// we're also going to need to maintain sets of slices that are deferred to a second pass because they span multiple columns/rows
		// (these sets are useless without the sliceMap)
		typedef std::set<const SliceDef*> SliceDefSet;
		SliceDefSet rowSpanned; // set of slices that are deferred because of row spanning
		SliceDefSet colSpanned; // set of slices that are deferred because of column spanning

		// now run all columns and rows
		// getting the minimum sizes and growth settings on those axis for single span entries only
		for ( col = 0; col < tmpSDP_Grid.getSizeX(); col++ ) {
			for ( row = 0; row < tmpSDP_Grid.getSizeY(); row++ ) {
				const SliceDef* slicePtr = tmpSDP_Grid[col][row];
				if ( !slicePtr ) continue; // skip blank entries

				// if this is a new entry, create the slice entry and map it
				if ( sliceMap.find( slicePtr ) == sliceMap.end() ) {
					Slice tmpSlice;
					tmpSlice.CellCol = col; // both column and row are accurate if this is the first time we've encountered the slice
					tmpSlice.CellRow = row;
					tmpSlice.ColSpan = slicePtr->ColSpan;
					tmpSlice.RowSpan = slicePtr->RowSpan;
					tmpSlice.Tiled = slicePtr->Tile;
					tmpSlice.Imagery = slicePtr->Imagery;
					mSlices.push_back( tmpSlice );
					Slice* finalPtr = &( mSlices.back() );
					sliceMap[slicePtr] = finalPtr;
				} else {
					assert( false ); // we should never find a previously touched slicedef
				}

				if ( slicePtr->ColSpan ) {
					//spans multiple columns, so we need to defer column expansion for this entry
					colSpanned.insert( slicePtr );
				} else {
					//spans a single column, so we can update the column information as necessary
					if ( slicePtr->GrowWidth )
						mColDims[col].Grow = true;
					if ( mColDims[col].MinSize < slicePtr->Width )
						mColDims[col].MinSize = slicePtr->Width;
				}

				if ( slicePtr->RowSpan ) {
					//spans multiple rows, so we need to defer for expansion for this entry
					rowSpanned.insert( slicePtr );
				} else {
					//spans a single row, so we can update the row information as necessary
					if ( slicePtr->GrowHeight )
						mRowDims[row].Grow = true;
					if ( mRowDims[row].MinSize < slicePtr->Height )
						mRowDims[row].MinSize = slicePtr->Height;
				}

				// in order to prevent unnecessary processing of duplicates, we'll zero out any spans
				for ( size_t i = 0; i <= slicePtr->ColSpan; i++ ) {
					for ( size_t j = 0; j <= slicePtr->RowSpan; j++ ) {
						if ( i != 0 || j != 0 ) { // only do this to the extended locations, not the root position
							tmpSDP_Grid[col+i][row+j] = 0;
						}
					}
				}
			}
		}

		// now go back through to 2nd pass items and deal with them as necessary

		// first do columns
		SliceDefSet::iterator iter, iterend = colSpanned.end();
		for ( iter = colSpanned.begin(); iter != iterend; iter++ ) {
			const SliceDef* sliceDefPtr = ( *iter );
			const Slice* slicePtr = sliceMap[sliceDefPtr];

			// we need to know the growing columns for both of the upcoming situations, so we calculate it here
			// might as well get the total span size while we're at it (since we need that later as well)
			float spanSize = 0.0f;
			typedef std::vector<size_t> SizeTVector;
			SizeTVector growingColumns;
			for ( size_t i = 0; i <= slicePtr->ColSpan; i++ ) {
				size_t col = slicePtr->CellCol + i;
				if ( mColDims[col].Grow )
					growingColumns.push_back( col );
				spanSize += mColDims[col].MinSize;
			}

			// do we need to force one of the columns to grow?
			if ( sliceDefPtr->GrowWidth && growingColumns.size() == 0 ) {
				// just force the first cell to grow
				mColDims[slicePtr->CellCol].Grow = true;
				growingColumns.push_back( slicePtr->CellCol );
			}

			// does the span fit into the current columns?
			if ( spanSize < sliceDefPtr->Width ) {
				// need to widen, so select who will grow
				SizeTVector widen_cols;
				if ( growingColumns.size() ) {
					// we have volunteers, so only widen them
					widen_cols = growingColumns;
				} else {
					// no volunteers means everyone gets to widen
					for ( size_t i = 0; i < slicePtr->ColSpan; i++ ) {
						size_t col = slicePtr->CellCol + i;
						widen_cols.push_back( col );
					}
				}
				// calculate the deficit and grow each selected column by an equal amount
				float deficit = sliceDefPtr->Width - spanSize;
				float amount_per_col = deficit / (( float )widen_cols.size() );
				for ( size_t i = 0; i < widen_cols.size(); i++ )
					mColDims[widen_cols[i]].MinSize += amount_per_col;

				// recalculate new span size and throw any remainder into the first column to complete the pass
				spanSize = 0.0f;
				for ( size_t i = 0; i <= slicePtr->ColSpan; i++ ) {
					size_t col = slicePtr->CellCol + i;
					spanSize += mColDims[col].MinSize;
				}
				deficit = sliceDefPtr->Width - spanSize;
				mColDims[slicePtr->CellCol].MinSize += deficit;
			}
		}

		// and then do rows
		iterend = rowSpanned.end();
		for ( iter = rowSpanned.begin(); iter != iterend; iter++ ) {
			const SliceDef* sliceDefPtr = ( *iter );
			const Slice* slicePtr = sliceMap[sliceDefPtr];

			// we need to know the growing rows for both of the upcoming situations, so we calculate it here
			// might as well get the total span size while we're at it (since we need that later as well)
			float spanSize = 0.0f;
			typedef std::vector<size_t> SizeTVector;
			SizeTVector growingRows;
			for ( size_t i = 0; i <= slicePtr->RowSpan; i++ ) {
				size_t row = slicePtr->CellRow + i;
				if ( mRowDims[row].Grow )
					growingRows.push_back( row );
				spanSize += mRowDims[row].MinSize;
			}

			// do we need to force one of the rows to grow?
			if ( sliceDefPtr->GrowHeight && growingRows.size() == 0 ) {
				// just force the first cell to grow
				mRowDims[slicePtr->CellRow].Grow = true;
				growingRows.push_back( slicePtr->CellRow );
			}

			// does the span fit into the current rows?
			if ( spanSize < sliceDefPtr->Height ) {
				// need to heighten, so select who will grow
				SizeTVector widen_rows;
				if ( growingRows.size() ) {
					// we have volunteers, so only widen them
					widen_rows = growingRows;
				} else {
					// no volunteers means everyone gets to widen
					for ( size_t i = 0; i < slicePtr->RowSpan; i++ ) {
						size_t row = slicePtr->CellRow + i;
						widen_rows.push_back( row );
					}
				}
				// calculate the deficit and grow each selected row by an equal amount
				float deficit = sliceDefPtr->Height - spanSize;
				float amount_per_row = deficit / (( float )widen_rows.size() );
				for ( size_t i = 0; i < widen_rows.size(); i++ )
					mRowDims[widen_rows[i]].MinSize += amount_per_row;

				// recalculate new span size and throw any remainder into the first row to complete the pass
				spanSize = 0.0f;
				for ( size_t i = 0; i <= slicePtr->RowSpan; i++ ) {
					size_t row = slicePtr->CellRow + i;
					spanSize += mRowDims[row].MinSize;
				}
				deficit = sliceDefPtr->Height - spanSize;
				mRowDims[slicePtr->CellRow].MinSize += deficit;
			}
		}

		// generate final caches of the total sizes so we can quickly tell what needs to happen during later usage
		m_CacheRowSize = 0.0f;
		m_CacheRowGrowing = 0;
		for ( size_t i = 0; i < mRowDims.size(); i++ ) {
			m_CacheRowSize += mRowDims[i].MinSize;
			if ( mRowDims[i].Grow )
				m_CacheRowGrowing++;
		}

		m_CacheColSize = 0.0f;
		m_CacheColGrowing = 0;
		for ( size_t i = 0; i < mColDims.size(); i++ ) {
			m_CacheColSize += mColDims[i].MinSize;
			if ( mColDims[i].Grow )
				m_CacheColGrowing++;
		}

		// At this point we have all rows and columns widened as necessary to
		// minimally fit their contents, and we have properly set the "grow"
		// attributes for each location. This completes the preprocessing.
		// There is nothing more we can do until we are asked for a specific
		// size to grow/shrink into. End of constructor. Thanks for playing.
	}
	//############################################################################
	void Face::getColumnWidths( float totalWidth, FaceDimArray& columnArray_out ) {
		columnArray_out.clear(); // start with a clean slate
		float dif = totalWidth - m_CacheColSize;

		// determine best stretch path
		if ( dif > 0 && m_CacheColGrowing ) {
			// we need to grow and we have designated "grow" columns...
			float addPer = dif / (( float )m_CacheColGrowing );
			size_t s = mColDims.size();
			for ( size_t i = 0; i < s; i++ ) {
				if ( mColDims[i].Grow )
					columnArray_out.push_back( mColDims[i].MinSize + addPer );
				else
					columnArray_out.push_back( mColDims[i].MinSize );
			}
		} else {
			if ( m_CacheColSize <= 0 ) {
				// this catches and handles divide by zero errors incurred by the preferred method
				size_t s = mColDims.size();
				float sizePer = totalWidth / ( float )s;
				for ( size_t i = 0; i < s; i++ ) {
					columnArray_out.push_back( sizePer );
				}
			} else {
				// This covers all other situations:
				//  * Need to grow uniformly
				//  * Need to shrink uniformly
				//  * Don't need to grow or shrink
				float mulPer = totalWidth / m_CacheColSize;
				size_t s = mColDims.size();
				for ( size_t i = 0; i < s; i++ ) {
					columnArray_out.push_back( mColDims[i].MinSize * mulPer );
				}
			}
		}
	}
	//############################################################################
	void Face::getRowHeights( float totalHeight, FaceDimArray& rowArray_out ) {
		rowArray_out.clear(); // start with a clean slate
		float dif = totalHeight - m_CacheRowSize;

		// determine best stretch path
		if ( dif > 0 && m_CacheRowGrowing ) {
			// we need to grow and we have designated "grow" rows...
			float addPer = dif / (( float )m_CacheRowGrowing );
			size_t s = mRowDims.size();
			for ( size_t i = 0; i < s; i++ ) {
				if ( mRowDims[i].Grow )
					rowArray_out.push_back( mRowDims[i].MinSize + addPer );
				else
					rowArray_out.push_back( mRowDims[i].MinSize );
			}
		} else {
			if ( m_CacheRowSize <= 0 ) {
				// this catches and handles divide by zero errors incurred by the preferred method
				size_t s = mRowDims.size();
				float sizePer = totalHeight / ( float )s;
				for ( size_t i = 0; i < s; i++ ) {
					rowArray_out.push_back( sizePer );
				}
			} else {
				// This covers all other situations:
				//  * Need to grow uniformly
				//  * Need to shrink uniformly
				//  * Don't need to grow or shrink
				float mulPer = totalHeight / m_CacheRowSize;
				size_t s = mRowDims.size();
				for ( size_t i = 0; i < s; i++ ) {
					rowArray_out.push_back( mRowDims[i].MinSize * mulPer );
				}
			}
		}
	}
	//############################################################################
	const SliceList& Face::getSlices() {
		return mSlices;
	}
	//############################################################################
} // namespace OpenGUI {