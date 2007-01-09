// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_Brush_RTT.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Screen.h"
#include "OpenGUI_Renderer.h"
#include "OpenGUI_TextureManager.h"

namespace OpenGUI {
	//############################################################################
	Brush_RTT::Brush_RTT( Screen* parentScreen, const FVector2& size ): mScreen( parentScreen ), mDrawSize( size ) {
		if ( !mScreen )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Constructor requires a valid pointer to destination Screen", __FUNCTION__ );
		mHasContent = false;
		IVector2 texSize;
		float xTexSize, yTexSize, xPixelSize, yPixelSize;
		xPixelSize = mDrawSize.x * getPPU_Raw().x;
		yPixelSize = mDrawSize.y * getPPU_Raw().y;
		xTexSize = Math::Ceil( xPixelSize );
		yTexSize = Math::Ceil( yPixelSize );
		mMaxUV.x = xPixelSize / xTexSize;
		mMaxUV.y = yPixelSize / yTexSize;

		texSize.x = ( int )( xTexSize );
		texSize.y = ( int )( yTexSize );
		mRenderTexture = TextureManager::getSingleton().createRenderTexture( texSize );
		if ( !mRenderTexture )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Failed to create valid render texture", __FUNCTION__ );
		_clear();
	}
	//############################################################################
	Brush_RTT::~Brush_RTT() {
		/**/
	}
	//############################################################################
	void Brush_RTT::emerge( Brush& targetBrush ) {
		RenderOperation rop;
		rop.texture = mRenderTexture.get();
		rop.triangleList = new TriangleList;
		Triangle tri;
		//ul
		tri.vertex[0].textureUV = FVector2( 0.0f, mMaxUV.y );
		tri.vertex[0].position = FVector2( 0.0f, 0.0f );
		//ll
		tri.vertex[1].textureUV = FVector2( 0.0f, 0.0f );
		tri.vertex[1].position = FVector2( 0.0f, mDrawSize.y );
		//ur
		tri.vertex[2].textureUV = FVector2( mMaxUV.x, mMaxUV.y );
		tri.vertex[2].position = FVector2( mDrawSize.x, 0.0f );
		rop.triangleList->push_back( tri );

		//ur
		tri.vertex[0] = tri.vertex[2];
		//ll
		// tri.vertex[1].textureUV = FVector2(0.0f,0.0f);
		// tri.vertex[1].position = FVector2(0.0f,1.0f);
		//lr
		tri.vertex[2].textureUV = FVector2( mMaxUV.x, 0.0f );
		tri.vertex[2].position = FVector2( mDrawSize.x, mDrawSize.y );
		rop.triangleList->push_back( tri );

		targetBrush._addRenderOperation( rop );
	}
	//############################################################################
	const FVector2& Brush_RTT::getPPU_Raw() const {
		return mScreen->getPPU();
	}
	//############################################################################
	const FVector2& Brush_RTT::getUPI_Raw() const {
		return mScreen->getUPI();
	}
	//############################################################################
	void Brush_RTT::appendRenderOperation( RenderOperation &renderOp ) {
		TriangleList::iterator iter, iterend = renderOp.triangleList->end();
		for ( iter = renderOp.triangleList->begin(); iter != iterend; iter++ ) {
			Triangle& t = ( *iter );
			for ( int i = 0; i < 3; i++ ) {
				t.vertex[i].position.x /= mDrawSize.x;
				t.vertex[i].position.y /= mDrawSize.y;
			}
		}
		Renderer::getSingleton().doRenderOperation( renderOp );
		mHasContent = true;
	}
	//############################################################################
	void Brush_RTT::onActivate() {
		Renderer::getSingleton().selectRenderContext( mRenderTexture.get() );
	}
	//############################################################################
	void Brush_RTT::onClear() {
		mHasContent = false;
		Renderer::getSingleton().clearContents();
	}
	//############################################################################
} // namespace OpenGUI{
