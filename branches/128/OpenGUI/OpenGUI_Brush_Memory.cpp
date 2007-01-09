// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_Brush_Memory.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Screen.h"

namespace OpenGUI {
	//############################################################################
	Brush_Memory::Brush_Memory( Screen* parentScreen ): mScreen( parentScreen ) {
		if ( !mScreen )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Constructor requires a valid pointer to destination Screen", __FUNCTION__ );
		mHasContent = false;
	}
	//############################################################################
	Brush_Memory::~Brush_Memory() {
		/**/
	}
	//############################################################################
	void Brush_Memory::emerge( Brush& targetBrush ) {
		RenderOperationList::iterator iter, iterend = mRopList.end();
		for ( iter = mRopList.begin(); iter != iterend; iter++ ) {
			//!\todo Having a copy operation here makes this incredibly slow! This should be removed as part of Brush optimization

			// we need to make a copy because addrenderOperation modifies the input directly
			RenderOperation &thisRop = ( *iter );
			RenderOperation tmp = thisRop;
			tmp.triangleList = new TriangleList;
			*( tmp.triangleList ) = *( thisRop.triangleList );

			targetBrush._addRenderOperation( tmp );
		}
	}
	//############################################################################
	const FVector2& Brush_Memory::getPPU_Raw() const {
		return mScreen->getPPU();
	}
	//############################################################################
	const FVector2& Brush_Memory::getUPI_Raw() const {
		return mScreen->getUPI();
	}
	//############################################################################
	void Brush_Memory::appendRenderOperation( RenderOperation &renderOp ) {
		mRopList.push_back( renderOp );
		RenderOperation& newRop = mRopList.back();
		newRop.triangleList = new TriangleList;
		TriangleList& inList = *( renderOp.triangleList );
		TriangleList& outList = *( newRop.triangleList );
		outList = inList;
		mHasContent = true;
	}
	//############################################################################
	void Brush_Memory::onActivate() {
		/* No special action required */
	}
	//############################################################################
	void Brush_Memory::onClear() {
		mRopList.clear();
		mHasContent = false;
	}
	//############################################################################
} // namespace OpenGUI{
