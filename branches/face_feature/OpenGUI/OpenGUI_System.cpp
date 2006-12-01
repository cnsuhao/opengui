
#include "OpenGUI.h" // <-- This is the one place I would consider this acceptable

namespace OpenGUI {
	//############################################################################
	template<> System* Singleton<System>::mptr_Singleton = 0;
	//############################################################################
	System& System::getSingleton( void ) {
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	System* System::getSingletonPtr( void ) {
		return mptr_Singleton;
	}
	//############################################################################
	System::System( Renderer* renderer, ResourceProvider* resourceProvider, std::string logFile ) {
		if ( logFile == "" ) {
			System( renderer, resourceProvider, 0 );
		} else {
			mDefaultLogListener = new LogListenerToFile( logFile );
			m_LogManager = new LogManager( mDefaultLogListener );
			System::doConstructor( renderer, resourceProvider );
		}
	}
	//############################################################################
	System::System( Renderer* renderer, ResourceProvider* resourceProvider, LogListener* logListener ) {
		m_LogManager = new LogManager( logListener );
		mDefaultLogListener = 0;
		System::doConstructor( renderer, resourceProvider );
	}
	//############################################################################
	void System::doConstructor( Renderer* renderer, ResourceProvider* resourceProvider ) {
		LogManager::SlogMsg( "INIT", OGLL_MSG ) << "OpenGUI (ver ";
		LogManager::SlogMsg( "INIT", OGLL_MSG ) << OPENGUI_VERSION_STR << ") ";
#ifdef OPENGUI_DEBUG
		LogManager::SlogMsg( "INIT", OGLL_MSG ) << "[[[DEBUG]]] ";
#endif
		LogManager::SlogMsg( "INIT", OGLL_MSG ) << "http://OpenGUI.SourceForge.net/" << Log::endlog;
		LogManager::SlogMsg( "INIT", OGLL_INFO )
		<< " ################################ "
		<< "System Init Started"
		<< " ################################ "
		<< Log::endlog;
		mTimerManager = new TimerManager; //get this up asap

		mXMLParser = new XMLParser(); //subsystems register with XML system, so this needs to be available immediately
		mXMLParser->RegisterLoadHandler( "OpenGUI", &System::_OpenGUI_XMLNode_Load );
		mXMLParser->RegisterUnloadHandler( "OpenGUI", &System::_OpenGUI_XMLNode_Unload );

		m_PerformAutoTicks = true;

		//mActiveGUISheet = 0;
		//m_CurrentMouseElement = 0;
		//mCapturerMouse = 0;
		//mCapturerKeyboard = 0;

		//mUserDblClickRate = 500;
		//mUserClickAccuracy = 0.05f;

		assert( renderer );
		mRenderer = renderer;
		if ( !mRenderer ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "No valid Renderer provided", "System" );
		}

		bool RendererRTT = mRenderer->supportsRenderToTexture();
		LogManager::SlogMsg( "INIT", OGLL_INFO3 ) << "Renderer RTT Support: ";
		if ( RendererRTT ) LogManager::SlogMsg( "INIT", OGLL_INFO3 ) << "Detected!";
		else LogManager::SlogMsg( "INIT", OGLL_INFO3 ) << "Not Found";
		LogManager::SlogMsg( "INIT", OGLL_INFO3 ) << Log::endlog;

		if ( resourceProvider ) {
			mResourceProvider = resourceProvider;
			mUsingGenericResourceProvider = false;
			LogManager::SlogMsg( "INIT", OGLL_INFO3 ) << "Using custom resource provider: " << mResourceProvider << Log::endlog;
		} else {
			LogManager::SlogMsg( "INIT", OGLL_INFO3 ) << "Using built in resource provider" << Log::endlog;
			mResourceProvider = new GenericResourceProvider();
			mUsingGenericResourceProvider = true;
		}

		mTextureManager = new TextureManager( mRenderer ); //create the texture manager
		mImageryManager = new ImageryManager( mResourceProvider ); //create the imagery manager

		mFontManager = new FontManager();

		mCursorManager = new CursorManager();

		mWidgetManager = new WidgetManager();

		mFormManager = new FormManager();

		m_PluginManager = new PluginManager();

		mScreenManager = new ScreenManager();

		LogManager::SlogMsg( "INIT", OGLL_INFO )
		<< " ################################ "
		<< "System Init Complete"
		<< " ################################ "
		<< Log::endlog;
	}

	//############################################################################
	System::~System() {
		LogManager::SlogMsg( "SHUTDOWN", OGLL_INFO )
		<< " ################################ "
		<< "System Shutdown Started"
		<< " ################################ "
		<< Log::endlog;

		//System::_destroyAllGUISheets();
		if ( mScreenManager )
			delete mScreenManager;

		/*
		plugins are always unloaded as soon as possible to ensure that
		all other subsystems are still available to the pluginStop
		functions
		*/
		if ( m_PluginManager )
			delete m_PluginManager;

		if ( mFormManager )
			delete mFormManager;

		if ( mWidgetManager )
			delete mWidgetManager;

		if ( mCursorManager )
			delete mCursorManager;

		if ( mFontManager )
			delete mFontManager;

		if ( mImageryManager )
			delete mImageryManager;

		if ( mTextureManager )
			delete mTextureManager;

		if ( mUsingGenericResourceProvider )
			delete mResourceProvider;

		if ( mXMLParser ) {
			mXMLParser->UnregisterLoadHandler( "OpenGUI", &System::_OpenGUI_XMLNode_Load );
			mXMLParser->UnregisterUnloadHandler( "OpenGUI", &System::_OpenGUI_XMLNode_Unload );
			delete mXMLParser;
		}

		if ( mTimerManager )
			delete mTimerManager; //delete this last

		LogManager::SlogMsg( "SHUTDOWN", OGLL_INFO )
		<< " ################################ "
		<< "System Shutdown Ending"
		<< " ################################ "
		<< Log::endlog;

		//End logging facilities last
		if ( m_LogManager )
			delete m_LogManager;
		if ( mDefaultLogListener )
			delete mDefaultLogListener; //very lastly close default log listener if it was used
	}
	//############################################################################
	void System::loadPlugin( std::string filename ) {
		PluginManager::getSingleton().loadPlugin( filename );
	}
	//############################################################################
	void System::unloadPlugin( std::string filename ) {
		PluginManager::getSingleton().unloadPlugin( filename );
	}
	//############################################################################
	/*! The following functions are called in the given order:
	- System::updateTime()
	- System::updateScreens()
	*/
	void System::update() {
		updateTime();
		updateScreens();
	}
	//############################################################################
	void System::updateTime() {
		mTimerManager->_AutoAdvance();
	}
	//############################################################################
	/*!
	The following functions are called in the given order:
	- ScreenManager::updateTime()
	- ScreenManager::updateScreens()
	*/
	void System::updateScreens() {
		mScreenManager->updateTime();
		mScreenManager->updateScreens();
	}
	//############################################################################
	bool System::_OpenGUI_XMLNode_Load( const XMLNode& node, const std::string& nodePath ) {
		if ( nodePath == "/" ) {
			std::string path = nodePath + node.getTagName() + "/";
			XMLParser::getSingleton().ProcessXML_Load( node, path );
			return true;
		}
		return false;
	}
	//############################################################################
	bool System::_OpenGUI_XMLNode_Unload( const XMLNode& node, const std::string& nodePath ) {
		if ( nodePath == "/" ) {
			std::string path = nodePath + node.getTagName() + "/";
			XMLParser::getSingleton().ProcessXML_Unload( node, path );
			return true;
		}
		return false;
	}
	//############################################################################
}
;//namespace OpenGUI{


