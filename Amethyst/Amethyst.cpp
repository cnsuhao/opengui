
#include "Amethyst.h"

//! This is the OpenGUI namespace, which contains the Amethyst namespace
namespace OpenGUI {
	//! All Amethyst classes are placed within this namespace
	namespace Amethyst {
		ThemeManager* g_ThemeManager = 0;

		// XML handlers for <Amethyst> tags - They just acknowledge the tag and defer back to the standard parser
		//############################################################################
		bool AMETHYST_API _Amethyst_XMLNode_Load( const XMLNode& node, const std::string& nodePath ) {
			if ( nodePath == "/" ) {
				std::string path = nodePath + node.getTagName() + "/";
				XMLParser::getSingleton().ProcessXML_Load( node, path );
				return true;
			}
			return false;
		}
		//############################################################################
		bool AMETHYST_API _Amethyst_XMLNode_Unload( const XMLNode& node, const std::string& nodePath ) {
			if ( nodePath == "/" ) {
				std::string path = nodePath + node.getTagName() + "/";
				XMLParser::getSingleton().ProcessXML_Unload( node, path );
				return true;
			}
			return false;
		}
		//############################################################################
	}
}


extern "C" {

	void __declspec( dllexport ) pluginStart() {
		using namespace OpenGUI;
		LogManager::SlogMsg( "Amethyst", OGLL_MSG )
		<< "Initializing Amethyst" << Log::endlog;

		// register the global <Amethyst> tag processors
		XMLParser::getSingleton().RegisterLoadHandler( "Amethyst", &Amethyst::_Amethyst_XMLNode_Load );
		XMLParser::getSingleton().RegisterUnloadHandler( "Amethyst", &Amethyst::_Amethyst_XMLNode_Unload );

		// initialize the ThemeManager
		assert( Amethyst::g_ThemeManager == 0 );
		Amethyst::g_ThemeManager = new Amethyst::ThemeManager();
	}

	void __declspec( dllexport ) pluginStop() {
		using namespace OpenGUI;
		LogManager::SlogMsg( "Amethyst", OGLL_MSG )
		<< "Shutting down Amethyst" << Log::endlog;

		// shutdown the ThemeManager
		assert( Amethyst::g_ThemeManager != 0 );
		delete Amethyst::g_ThemeManager;

		// unregister the global <Amethyst> tag processors
		XMLParser::getSingleton().UnregisterLoadHandler( "Amethyst", &Amethyst::_Amethyst_XMLNode_Load );
		XMLParser::getSingleton().UnregisterUnloadHandler( "Amethyst", &Amethyst::_Amethyst_XMLNode_Unload );
	}

}; // extern "C" {
