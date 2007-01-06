// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_FaceDef.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//############################################################################
	SliceDef& FaceDef::getSlice( size_t col, size_t row ) {
		if (( row + 1 ) > Rows.size() )
			Rows.resize( row + 1 );

		if (( col + 1 ) > Rows[row].size() )
			Rows[row].resize( col + 1 );

		return Rows[row][col];
	}
	//############################################################################
	size_t FaceDef::getRowSizeEstimate() const {
		size_t totalRows = 0;
		const size_t NumSliceRows = Rows.size();
		for ( size_t r = 0; r < NumSliceRows; r++ ) {
			size_t rowDepth = 0; // the depth this row reaches
			const size_t NumSlices = Rows[r].size();
			for ( size_t s = 0; s < NumSlices; s++ ) {
				if ( rowDepth < Rows[r][s].RowSpan )
					rowDepth = Rows[r][s].RowSpan;
			}
			rowDepth += ( r + 1 ); // offset row depth by the current row we're on to get final depth
			if ( totalRows < rowDepth )
				totalRows = rowDepth;
		}
		return totalRows;
	}
	//############################################################################
	size_t FaceDef::getColSizeEstimate() const {
		size_t totalCols = 0;
		const size_t NumSliceRows = Rows.size();
		for ( size_t r = 0; r < NumSliceRows; r++ ) {
			unsigned int rowCols = 0;
			const size_t NumSlices = Rows[r].size();
			for ( size_t s = 0; s < NumSlices; s++ ) {
				rowCols += 1 + Rows[r][s].ColSpan;
			}
			if ( totalCols < rowCols )
				totalCols = rowCols;
		}
		return totalCols;
	}
	//############################################################################
} // namespace OpenGUI {
