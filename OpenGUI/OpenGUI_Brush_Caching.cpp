#include "OpenGUI_Brush_Caching.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Screen.h"

namespace OpenGUI {
	//############################################################################
	Brush_Caching::Brush_Caching(Screen* parentScreen):mScreen(parentScreen) {
		if(!mScreen)
			OG_THROW(Exception::ERR_INVALIDPARAMS,"Constructor requires a valid pointer to destination Screen",__FUNCTION__);
	}
	//############################################################################
	Brush_Caching::~Brush_Caching() {
		/**/
	}
	//############################################################################
	void Brush_Caching::emerge( Brush& targetBrush ) {
		for(RenderOperationList::iterator iter = mRopList.begin(); mRopList.end() != iter; iter++){
			//!\todo Having a copy operation here makes this incredibly slow! This should be removed as part of Brush optimization

			// we need to make a copy because addrenderOperation modifies the input directly
			RenderOperation &thisRop = (*iter);
			RenderOperation tmp = thisRop;
			tmp.triangleList = new TriangleList;
			*(tmp.triangleList) = *(thisRop.triangleList);

			targetBrush._addRenderOperation( tmp );
		}
	}
	//############################################################################
	const FVector2& Brush_Caching::getPPU_Raw() const {
		return mScreen->getPPU();
	}
	//############################################################################
	const FVector2& Brush_Caching::getUPI_Raw() const {
		return mScreen->getUPI();
	}
	//############################################################################
	void Brush_Caching::appendRenderOperation( RenderOperation &renderOp ) {
		mRopList.push_back(renderOp);
		RenderOperation& newRop = mRopList.back();
		newRop.triangleList = new TriangleList;
		TriangleList& inList = *(renderOp.triangleList);
		TriangleList& outList = *(newRop.triangleList);
		outList = inList;
	}
	//############################################################################
	void Brush_Caching::onActivate() {
		/* No special action required */
	}
	//############################################################################
	void Brush_Caching::onClear() {
		mRopList.clear();
	}
	//############################################################################
} // namespace OpenGUI{
