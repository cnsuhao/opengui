#include "OpenGUI.h"
#include "OpenGUI_GenericCursor.h"

namespace OpenGUI{
	//############################################################################
	GenericCursor::GenericCursor()
	{
	
	}
	//############################################################################
	void GenericCursor::setImagery(std::string imageryName,FVector2 offset)
	{
		mImagery = ImageryManager::getSingleton().getImagery(imageryName);
		mOffset = offset;
	}
	//############################################################################
	void GenericCursor::show()
	{
		RegisterForDraw();
	}
	//############################################################################
	void GenericCursor::hide()
	{
		UnRegisterForDraw();
	}
	//############################################################################
	Render::RenderOperationList GenericCursor::getCursorRenderOpList()
	{
		//!\todo fix me
		FVector2 mPos = System::getSingleton().getCursorPos();
		FRect boxRect;
		boxRect.setSize(FVector2(0.05f,0.05f));
		mPos = mPos - (FVector2(0.05f,0.05f) * mOffset);
		boxRect.setPosition(mPos);
		Render::PrimitiveBox box;
		box.setRect(boxRect);
		if(mImagery)
			box.setTextureImagery(mImagery);
		return box.getRenderOperationList();
	}
	//############################################################################
};//namespace OpenGUI{
