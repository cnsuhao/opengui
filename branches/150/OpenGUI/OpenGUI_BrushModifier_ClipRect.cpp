// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_BrushModifier_ClipRect.h"

namespace OpenGUI {
	//############################################################################
	void BrushModifier_ClipRect::apply( RenderOperation& in_out ) {
		TriangleList* inListPtr = in_out.triangleList;
		TriangleList* outListPtr = new TriangleList;
		in_out.triangleList = outListPtr;

		Triangle extra;
		unsigned int outCount;
		TriangleList& inList = *inListPtr;
		TriangleList& outList = *outListPtr;

		while ( inList.size() > 0 ) {
			Triangle& tri = inList.front();
			TriangleList::iterator iter = inList.begin();
			iter++;

			_SliceRenderOp_Vert_SaveLeft( tri, extra, outCount, mRect.max.x );
			if ( outCount == 0 ) {
				inList.pop_front();
				continue;
			} else if ( outCount == 2 ) {
				inList.insert( iter, extra );
			}

			_SliceRenderOp_Vert_SaveRight( tri, extra, outCount, mRect.min.x );
			if ( outCount == 0 ) {
				inList.pop_front();
				continue;
			} else if ( outCount == 2 ) {
				inList.insert( iter, extra );
			}

			_SliceRenderOp_Horiz_SaveTop( tri, extra, outCount, mRect.max.y );
			if ( outCount == 0 ) {
				inList.pop_front();
				continue;
			} else if ( outCount == 2 ) {
				inList.insert( iter, extra );
			}

			_SliceRenderOp_Horiz_SaveBottom( tri, extra, outCount, mRect.min.y );
			if ( outCount == 0 ) {
				inList.pop_front();
				continue;
			} else if ( outCount == 2 ) {
				inList.insert( iter, extra );
			}

			outList.push_back( tri );
			inList.pop_front();
		}

		delete inListPtr;
	}
	//############################################################################
	void BrushModifier_ClipRect::_sliceLineSegment( const Vertex& vert1, const Vertex& vert2,
			Vertex& resultVert, float cutPosition, bool cutHorizontal ) {
		const Vertex* higher;
		const Vertex* lower;
		if ( !cutHorizontal ) {
			if ( vert1.position.x < vert2.position.x ) {
				lower = &vert1;
				higher = &vert2;
			} else {
				lower = &vert2;
				higher = &vert1;
			}
		} else {
			if ( vert1.position.y < vert2.position.y ) {
				lower = &vert1;
				higher = &vert2;
			} else {
				lower = &vert2;
				higher = &vert1;
			}
		}

		float cutPercent;
		if ( !cutHorizontal ) {
			cutPercent = ( cutPosition - lower->position.x ) / ( higher->position.x - lower->position.x );
		} else {
			cutPercent = ( cutPosition - lower->position.y ) / ( higher->position.y - lower->position.y );
		}

		//calculate new position
		resultVert.position.x = (( higher->position.x - lower->position.x ) * cutPercent ) + lower->position.x;
		resultVert.position.y = (( higher->position.y - lower->position.y ) * cutPercent ) + lower->position.y;

		//calculate new UVs
		resultVert.textureUV.x = (( higher->textureUV.x - lower->textureUV.x ) * cutPercent ) + lower->textureUV.x;
		resultVert.textureUV.y = (( higher->textureUV.y - lower->textureUV.y ) * cutPercent ) + lower->textureUV.y;
		resultVert.maskUV.x = (( higher->maskUV.x - lower->maskUV.x ) * cutPercent ) + lower->maskUV.x;
		resultVert.maskUV.y = (( higher->maskUV.y - lower->maskUV.y ) * cutPercent ) + lower->maskUV.y;

		//calculate new colors
		resultVert.color.Red = (( higher->color.Red - lower->color.Red ) * cutPercent ) + lower->color.Red;
		resultVert.color.Green = (( higher->color.Green - lower->color.Green ) * cutPercent ) + lower->color.Green;
		resultVert.color.Blue = (( higher->color.Blue - lower->color.Blue ) * cutPercent ) + lower->color.Blue;
		resultVert.color.Alpha = (( higher->color.Alpha - lower->color.Alpha ) * cutPercent ) + lower->color.Alpha;

		//done
	}
	//############################################################################
	void BrushModifier_ClipRect::_SliceRenderOp_Vert_SaveLeft( Triangle& in_out1,
			Triangle& out2, unsigned int& outCount, float cutPosition ) {
		unsigned int toKeepCount = 0;
		unsigned int toKeep[3];
		unsigned int toDropCount = 0;
		unsigned int toDrop[3];
		for ( unsigned int i = 0; i < 3; i++ ) {
			if ( in_out1.vertex[i].position.x > cutPosition )
				toDrop[toDropCount++] = i;
			else
				toKeep[toKeepCount++] = i;
		}

		if ( toKeepCount == 0 ) {
			outCount = 0;
			return;
		}

		if ( toKeepCount == 1 ) {
			//only one render operation as output
			outCount = 1;
			Vertex tmp1, tmp2;
			_sliceLineSegment( in_out1.vertex[toKeep[0]], in_out1.vertex[toDrop[0]], tmp1, cutPosition, false );
			_sliceLineSegment( in_out1.vertex[toKeep[0]], in_out1.vertex[toDrop[1]], tmp2, cutPosition, false );
			in_out1.vertex[toKeep[0]] = in_out1.vertex[toKeep[0]];
			in_out1.vertex[toDrop[0]] = tmp1;
			in_out1.vertex[toDrop[1]] = tmp2;
			return;
		}

		if ( toKeepCount == 2 ) {
			//two render operations as output
			outCount = 2;
			Vertex tmp1, tmp2;
			_sliceLineSegment( in_out1.vertex[toKeep[0]], in_out1.vertex[toDrop[0]], tmp1, cutPosition, false );
			_sliceLineSegment( in_out1.vertex[toKeep[1]], in_out1.vertex[toDrop[0]], tmp2, cutPosition, false );
			out2.vertex[toKeep[0]] = in_out1.vertex[toKeep[0]];
			out2.vertex[toKeep[1]] = in_out1.vertex[toKeep[1]];
			out2.vertex[toDrop[0]] = tmp2;
			in_out1.vertex[toKeep[0]] = in_out1.vertex[toKeep[0]];
			in_out1.vertex[toKeep[1]] = tmp2;
			in_out1.vertex[toDrop[0]] = tmp1;
			return;
		}

		outCount = 1;
	}
	//############################################################################
	void BrushModifier_ClipRect::_SliceRenderOp_Vert_SaveRight( Triangle& in_out1,
			Triangle& out2, unsigned int& outCount, float cutPosition ) {
		unsigned int toKeepCount = 0;
		unsigned int toKeep[3];
		unsigned int toDropCount = 0;
		unsigned int toDrop[3];
		for ( unsigned int i = 0; i < 3; i++ ) {
			if ( in_out1.vertex[i].position.x < cutPosition )
				toDrop[toDropCount++] = i;
			else
				toKeep[toKeepCount++] = i;
		}

		if ( toKeepCount == 0 ) {
			outCount = 0;
			return;
		}

		if ( toKeepCount == 1 ) {
			//only one render operation as output
			outCount = 1;
			Vertex tmp1, tmp2;
			_sliceLineSegment( in_out1.vertex[toDrop[0]], in_out1.vertex[toKeep[0]], tmp1, cutPosition, false );
			_sliceLineSegment( in_out1.vertex[toDrop[1]], in_out1.vertex[toKeep[0]], tmp2, cutPosition, false );
			in_out1.vertex[toKeep[0]] = in_out1.vertex[toKeep[0]];
			in_out1.vertex[toDrop[0]] = tmp1;
			in_out1.vertex[toDrop[1]] = tmp2;
			return;
		}

		if ( toKeepCount == 2 ) {
			//two render operations as output
			outCount = 2;
			Vertex tmp1, tmp2;
			_sliceLineSegment( in_out1.vertex[toDrop[0]], in_out1.vertex[toKeep[0]], tmp1, cutPosition, false );
			_sliceLineSegment( in_out1.vertex[toDrop[0]], in_out1.vertex[toKeep[1]], tmp2, cutPosition, false );
			out2.vertex[toKeep[0]] = in_out1.vertex[toKeep[0]];
			out2.vertex[toKeep[1]] = in_out1.vertex[toKeep[1]];
			out2.vertex[toDrop[0]] = tmp2;
			in_out1.vertex[toKeep[0]] = in_out1.vertex[toKeep[0]];
			in_out1.vertex[toKeep[1]] = tmp2;
			in_out1.vertex[toDrop[0]] = tmp1;
			return;
		}

		outCount = 1;
	}
	//############################################################################
	void BrushModifier_ClipRect::_SliceRenderOp_Horiz_SaveTop( Triangle& in_out1,
			Triangle& out2, unsigned int& outCount, float cutPosition ) {
		unsigned int toKeepCount = 0;
		unsigned int toKeep[3];
		unsigned int toDropCount = 0;
		unsigned int toDrop[3];
		for ( unsigned int i = 0; i < 3; i++ ) {
			if ( in_out1.vertex[i].position.y > cutPosition )
				toDrop[toDropCount++] = i;
			else
				toKeep[toKeepCount++] = i;
		}

		if ( toKeepCount == 0 ) {
			outCount = 0;
			return;
		}

		if ( toKeepCount == 1 ) {
			//only one render operation as output
			outCount = 1;
			Vertex tmp1, tmp2;
			_sliceLineSegment( in_out1.vertex[toKeep[0]], in_out1.vertex[toDrop[0]], tmp1, cutPosition, true );
			_sliceLineSegment( in_out1.vertex[toKeep[0]], in_out1.vertex[toDrop[1]], tmp2, cutPosition, true );
			in_out1.vertex[toKeep[0]] = in_out1.vertex[toKeep[0]];
			in_out1.vertex[toDrop[0]] = tmp1;
			in_out1.vertex[toDrop[1]] = tmp2;
			return;
		}

		if ( toKeepCount == 2 ) {
			//two render operations as output
			outCount = 2;
			Vertex tmp1, tmp2;
			_sliceLineSegment( in_out1.vertex[toKeep[0]], in_out1.vertex[toDrop[0]], tmp1, cutPosition, true );
			_sliceLineSegment( in_out1.vertex[toKeep[1]], in_out1.vertex[toDrop[0]], tmp2, cutPosition, true );
			out2.vertex[toKeep[0]] = in_out1.vertex[toKeep[0]];
			out2.vertex[toKeep[1]] = in_out1.vertex[toKeep[1]];
			out2.vertex[toDrop[0]] = tmp2;
			in_out1.vertex[toKeep[0]] = in_out1.vertex[toKeep[0]];
			in_out1.vertex[toKeep[1]] = tmp2;
			in_out1.vertex[toDrop[0]] = tmp1;
			return;
		}

		outCount = 1;
	}
	//############################################################################
	void BrushModifier_ClipRect::_SliceRenderOp_Horiz_SaveBottom( Triangle& in_out1,
			Triangle& out2, unsigned int& outCount, float cutPosition ) {
		unsigned int toKeepCount = 0;
		unsigned int toKeep[3];
		unsigned int toDropCount = 0;
		unsigned int toDrop[3];
		for ( unsigned int i = 0; i < 3; i++ ) {
			if ( in_out1.vertex[i].position.y < cutPosition )
				toDrop[toDropCount++] = i;
			else
				toKeep[toKeepCount++] = i;
		}

		if ( toKeepCount == 0 ) {
			outCount = 0;
			return;
		}

		if ( toKeepCount == 1 ) {
			//only one render operation as output
			outCount = 1;
			Vertex tmp1, tmp2;
			_sliceLineSegment( in_out1.vertex[toDrop[0]], in_out1.vertex[toKeep[0]], tmp1, cutPosition, true );
			_sliceLineSegment( in_out1.vertex[toDrop[1]], in_out1.vertex[toKeep[0]], tmp2, cutPosition, true );
			in_out1.vertex[toKeep[0]] = in_out1.vertex[toKeep[0]];
			in_out1.vertex[toDrop[0]] = tmp1;
			in_out1.vertex[toDrop[1]] = tmp2;
			return;
		}

		if ( toKeepCount == 2 ) {
			//two render operations as output
			outCount = 2;
			Vertex tmp1, tmp2;
			_sliceLineSegment( in_out1.vertex[toDrop[0]], in_out1.vertex[toKeep[0]], tmp1, cutPosition, true );
			_sliceLineSegment( in_out1.vertex[toDrop[0]], in_out1.vertex[toKeep[1]], tmp2, cutPosition, true );
			out2.vertex[toKeep[0]] = in_out1.vertex[toKeep[0]];
			out2.vertex[toKeep[1]] = in_out1.vertex[toKeep[1]];
			out2.vertex[toDrop[0]] = tmp2;
			in_out1.vertex[toKeep[0]] = in_out1.vertex[toKeep[0]];
			in_out1.vertex[toKeep[1]] = tmp2;
			in_out1.vertex[toDrop[0]] = tmp1;
			return;
		}

		outCount = 1;
	}
	//############################################################################

} // namespace OpenGUI {
