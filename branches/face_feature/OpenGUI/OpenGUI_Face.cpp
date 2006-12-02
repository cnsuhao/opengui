#include "OpenGUI_Face.h"
#include "OpenGUI_FaceDef.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//############################################################################
	// We're doing this to ensure that memory destroyed within OpenGUI is also created within OpenGUI
	FacePtr Face::Create( const FaceDef& faceDefinition ) {
		return new Face( faceDefinition );
	}
	//############################################################################
	Face::Face( const FaceDef& faceDefinition ): Metric( faceDefinition.Metric ) {
		//Note: these may be a waste of time, since they aren't always accurate to begin with
		// (they have the potential to report smaller sizes than they should)
		size_t initCols = faceDefinition.getRequiredCols();
		size_t initRows = faceDefinition.getRequiredRows();

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
				if ( sliceMap.find( slicePtr ) != sliceMap.end() ) {
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
				}

				if ( slicePtr->ColSpan ) {
					//spans multiple columns, so we need to defer column expansion for this entry
					colSpanned.insert( slicePtr );
				} else {
					//spans a single column, so we can update the column information as necessary
					if ( slicePtr->GrowWidth ) mColDims[col].Grow = true;
					if ( mColDims[col].MinSize < slicePtr->Width ) mColDims[col].MinSize = slicePtr->Width;
				}

				if ( slicePtr->RowSpan ) {
					//spans multiple rows, so we need to defer for expansion for this entry
					rowSpanned.insert( slicePtr );
				} else {
					//spans a single row, so we can update the row information as necessary
					if ( slicePtr->GrowHeight ) mRowDims[row].Grow = true;
					if ( mRowDims[row].MinSize < slicePtr->Height ) mRowDims[row].MinSize = slicePtr->Height;
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
		// TODO: add me for rows and columns individually!


		// At this point we have all rows and columns widened as necessary to
		// minimally fit their contents, and we have properly set the "grow"
		// attributes for each location. This completes the preprocessing.
		// There is nothing more we can do until we are asked for a specific
		// size to grow/shrink into. End of constructor. Thanks for playing.
	}
	//############################################################################
} // namespace OpenGUI {