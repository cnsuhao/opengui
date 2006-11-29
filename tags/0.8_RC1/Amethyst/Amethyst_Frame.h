#ifndef Amethyst_Frame_h__
#define Amethyst_Frame_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {

		class AMETHYST_API Frame: public ContainerControl {
		public:
			typedef enum {
				UL,
				UM,
				UR,
				ML,
				MM,
				MR,
				LL,
				LM,
				LR
			}eFrameImageIndex;

			Frame();
			virtual ~Frame();

			//! Sets the various frame imagery.
			void setImagery( std::string imageryName, eFrameImageIndex indx);
			//! Gets the various frame imagery.
			std::string getImagery(eFrameImageIndex indx);
			//! Gets the FRect of the background
			const FRect& getBGRect() const;

			static Widget* CreateFrameFactory();

		protected:
			virtual void onDraw( Object* sender, Draw_EventArgs& evtArgs );
			ImageryPtr mFramePieces[9];
			FRect mBGRect;
		};

	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_Frame_h__
