#include "OpenGUI_Brush_Caching.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Screen.h"
#include "OpenGUI_Renderer.h"
#include "OpenGUI_TextureManager.h"

namespace OpenGUI {
	//############################################################################
	Brush_Caching::Brush_Caching( Screen* parentScreen, const FVector2& size ): mScreen( parentScreen ), mDrawSize( size ) {
		if ( !mScreen )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Constructor requires a valid pointer to destination Screen", __FUNCTION__ );
		if ( !initRTT() )
			initMemory();
		mHasContent = false;
	}
	//############################################################################
	Brush_Caching::~Brush_Caching() {
		if ( isRTT() )
			cleanupRTT();
		else
			cleanupMemory();
	}
	//############################################################################
	void Brush_Caching::emerge( Brush& targetBrush ) {
		if ( isRTT() )
			emergeRTT( targetBrush );
		else
			emergeMemory( targetBrush );
	}
	//############################################################################
	const FVector2& Brush_Caching::getPPU_Raw() const {
		if ( isRTT() ) {
			static FVector2 retVal;
			const IVector2& texsize = mRenderTexture->getSize();
			retVal.x = ( float )texsize.x / mDrawSize.x;
			retVal.y = ( float )texsize.y / mDrawSize.y;
			return retVal;
		} else {
			return mScreen->getPPU();
		}
	}
	//############################################################################
	const FVector2& Brush_Caching::getUPI_Raw() const {
		return mScreen->getUPI();
	}
	//############################################################################
	void Brush_Caching::appendRenderOperation( RenderOperation &renderOp ) {
		mHasContent = true;
		if ( isRTT() )
			appendRTT( renderOp );
		else
			appendMemory( renderOp );
	}
	//############################################################################
	void Brush_Caching::onActivate() {
		if ( isRTT() )
			activateRTT();
		else
			activateMemory();
	}
	//############################################################################
	void Brush_Caching::onClear() {
		mHasContent = false;
		if ( isRTT() )
			clearRTT();
		else
			clearMemory();
	}
	//############################################################################
	//############################################################################
	//############################################################################
	void Brush_Caching::initMemory() {
		pushClippingRect( FRect( 0, 0, mDrawSize.x, mDrawSize.y ) );
		_pushMarker( this );
	}
	//############################################################################
	void Brush_Caching::cleanupMemory() {
		_popMarker( this );
		pop();
	}
	//############################################################################
	void Brush_Caching::clearMemory() {
		mRenderOpList.clear();
	}
	//############################################################################
	void Brush_Caching::activateMemory() {
		/* No special action required */
	}
	//############################################################################
	void Brush_Caching::appendMemory( RenderOperation &renderOp ) {
		//!\todo fix me to perform triangle list appending when renderOps are equal
		mRenderOpList.push_back( renderOp );
		RenderOperation& newRop = mRenderOpList.back();
		newRop.triangleList = new TriangleList;
		TriangleList& inList = *( renderOp.triangleList );
		TriangleList& outList = *( newRop.triangleList );
		outList = inList;
	}
	//############################################################################
	void Brush_Caching::emergeMemory( Brush& targetBrush ) {
		RenderOperationList::iterator iter, iterend = mRenderOpList.end();
		for ( iter = mRenderOpList.begin(); iter != iterend; iter++ ) {
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
	//############################################################################
	//############################################################################
	bool Brush_Caching::initRTT() {
		if ( !TextureManager::getSingleton().supportsRenderToTexture() )
			return false;

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
			return false;
		_clear();
		return true;
	}
	//############################################################################
	void Brush_Caching::cleanupRTT() {
		/* No special action required */
	}
	//############################################################################
	void Brush_Caching::clearRTT() {
		Renderer::getSingleton().clearContents();
	}
	//############################################################################
	void Brush_Caching::activateRTT() {
		Renderer::getSingleton().selectRenderContext( mRenderTexture.get() );
	}
	//############################################################################
	void Brush_Caching::appendRTT( RenderOperation &renderOp ) {
		TriangleList::iterator iter, iterend = renderOp.triangleList->end();
		for ( iter = renderOp.triangleList->begin(); iter != iterend; iter++ ) {
			Triangle& t = ( *iter );
			for ( int i = 0; i < 3; i++ ) {
				t.vertex[i].position.x /= mDrawSize.x;
				t.vertex[i].position.y /= mDrawSize.y;
			}
		}
		Renderer::getSingleton().doRenderOperation( renderOp );
	}
	//############################################################################
	void Brush_Caching::emergeRTT( Brush& targetBrush ) {
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

		targetBrush.pushPixelAlignment();
		targetBrush._addRenderOperation( rop );
		targetBrush.pop();
	}
	//############################################################################
} // namespace OpenGUI{