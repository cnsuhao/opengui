#ifndef CC39D68E_39E4_43d2_BFAB_97845ADBC8CC
#define CC39D68E_39E4_43d2_BFAB_97845ADBC8CC

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_RenderOperation.h"

namespace OpenGUI{

	namespace Render{

		/*! \brief
		A box primitive. Provides simple render operation generation
		for creating boxes of any dimension, location, and imagery.
		It provides automatic Texture* linking and UV generation for
		both textures and masks based on imagery.
		*/
		class OPENGUI_API PrimitiveBox : public Primitive{
		public:
			//! default constructor
			PrimitiveBox() : mRect(FRect(0.0f,0.0f,1.0f,1.0f)), mTextureImagery(0), mMaskImagery(0) {}
			virtual ~PrimitiveBox() {}
			//! Returns the RenderOperationList that is the result of this primitive
			RenderOperationList getRenderOperationList();
			//! Get the current position and size of the Box
			FRect getRect(){return mRect;}
			//! Sets the size and position of the Box to the given FRect
			void setRect(FRect rect){mRect=rect;}
			//! Sets the imagery that should be used for texturing the Box. 0 uses none (default)
			void setTextureImagery(ImageryPtr imagery) {mTextureImagery = imagery;}
			//! Sets the mask imagery that should be used for texturing the Box. 0 uses none (default)
			void setMaskImagery(ImageryPtr imagery) {mMaskImagery = imagery;}
		private:
			FRect mRect; //size and position of this Box
			ImageryPtr mTextureImagery;
			ImageryPtr mMaskImagery;
		};


		//! A primitive to draw a box shaped outline. The outline is drawn on the inside of the given rect
		class OPENGUI_API PrimitiveBoxOutline : public Primitive{
		public:
			//! default constructor
			PrimitiveBoxOutline() : mRect(FRect(0.0f,0.0f,1.0f,1.0f)), mThickness(1), mContext(0) {}
			virtual ~PrimitiveBoxOutline() {}
			//! Returns the RenderOperationList that is the result of this primitive
			RenderOperationList getRenderOperationList();
			//! Sets the element used as the context for obtaining pixel alignment
			void setContext(Element* contextElement){mContext = contextElement;}
			//! Get the current position and size of the Box
			FRect getRect(){return mRect;}
			//! Sets the size and position of the Box to the given FRect
			void setRect(FRect rect){mRect=rect;}
			//! Sets the thickness of the outline
			void setThickness(unsigned int thickness){mThickness=thickness;}
		private:
			FRect mRect; //size and position of this Box
			unsigned int mThickness; //pixel thickness of the outline
			Element* mContext;
			FVector2 _getPixelScale();
		};


	};//namespace Render{
};//namespace OpenGUI{

#endif
