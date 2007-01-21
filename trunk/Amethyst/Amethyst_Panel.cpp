// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#include "Amethyst_Panel.h"
#include "OpenGUI_Macros.h"

namespace OpenGUI {
	namespace Amethyst {
		//############################################################################
		SimpleProperty_Face( PanelP_FaceBG, "FaceBG", Panel, getFaceBG, setFaceBG );
		SimpleProperty_Float( PanelP_PaddingTop, "Padding_Top", Panel, getPaddingTop, setPaddingTop );
		SimpleProperty_Float( PanelP_PaddingBottom, "Padding_Bottom", Panel, getPaddingBottom, setPaddingBottom );
		SimpleProperty_Float( PanelP_PaddingLeft, "Padding_Left", Panel, getPaddingLeft, setPaddingLeft );
		SimpleProperty_Float( PanelP_PaddingRight, "Padding_Right", Panel, getPaddingRight, setPaddingRight );
		//############################################################################
		class Panel_ObjectAccessorList : public ObjectAccessorList {
		public:
			Panel_ObjectAccessorList() {
				addAccessor( &PanelP_FaceBG );
				addAccessor( &PanelP_PaddingTop );
				addAccessor( &PanelP_PaddingBottom );
				addAccessor( &PanelP_PaddingLeft );
				addAccessor( &PanelP_PaddingRight );
			}
			~Panel_ObjectAccessorList() {}
		}
		gPanel_ObjectAccessorList;
		//############################################################################
		//############################################################################
		Widget* Panel::createPanelFactory() {
			return new Panel;
		}
		//############################################################################
		ObjectAccessorList* Panel::getAccessors() {
			return &gPanel_ObjectAccessorList;
		}
		//############################################################################
		Panel::Panel() {
			if ( gPanel_ObjectAccessorList.getParent() == NULL )
				gPanel_ObjectAccessorList.setParent( ContainerControl::getAccessors() );

			//mScrollingOffset = FVector2(0,0);
			//mCanvasSize = FVector2(0,0);
		}
		//############################################################################
		Panel::~Panel() {
			/**/
		}
		//############################################################################
		void Panel::setFaceBG( FacePtr backgroundFace ) {
			mFaceBG = backgroundFace;
			invalidate();
		}
		//############################################################################
		FacePtr Panel::getFaceBG() const {
			return mFaceBG;
		}
		//############################################################################
		void Panel::setPaddingTop( float padding ) {
			m_ClientAreaOffset_UL.y = padding;
			invalidate();
		}
		//############################################################################
		float Panel::getPaddingTop() const {
			return m_ClientAreaOffset_UL.y;
		}
		//############################################################################
		void Panel::setPaddingBottom( float padding ) {
			m_ClientAreaOffset_LR.y = padding;
			invalidate();
		}
		//############################################################################
		float Panel::getPaddingBottom() const {
			return m_ClientAreaOffset_LR.y;
		}
		//############################################################################
		void Panel::setPaddingLeft( float padding ) {
			m_ClientAreaOffset_UL.x = padding;
			invalidate();
		}
		//############################################################################
		float Panel::getPaddingLeft() const {
			return m_ClientAreaOffset_UL.x;
		}
		//############################################################################
		void Panel::setPaddingRight( float padding ) {
			m_ClientAreaOffset_LR.x = padding;
			invalidate();
		}
		//############################################################################
		float Panel::getPaddingRight() const {
			return m_ClientAreaOffset_LR.x;
		}
		//############################################################################
		void Panel::onDrawBG( Object* sender, Draw_EventArgs& evtArgs ) {
			Brush& b = evtArgs.brush;
			b.Image.drawFace( mFaceBG, getRect() );
		}
		//############################################################################
	} // namespace Amethyst
}  //namespace OpenGUI
