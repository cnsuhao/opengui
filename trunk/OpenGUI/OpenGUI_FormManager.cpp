#include "OpenGUI_FormManager.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_XMLParser.h"

namespace OpenGUI{
	//############################################################################
	template<> FormManager* Singleton<FormManager>::mptr_Singleton = 0;
	//############################################################################
	FormManager& FormManager::getSingleton( void ) {
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	FormManager* FormManager::getSingletonPtr( void ) {
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	FormManager::FormManager(){
		LogManager::SlogMsg( "INIT", OGLL_INFO2 ) << "Creating FormManager" << Log::endlog;
		XMLParser::getSingleton().RegisterLoadHandler( "FormDef", &FormManager::_FormDef_XMLNode_Load );
		XMLParser::getSingleton().RegisterUnloadHandler( "FormDef", &FormManager::_FormDef_XMLNode_Unload );
	}
	//############################################################################
	FormManager::~FormManager(){
		LogManager::SlogMsg( "SHUTDOWN", OGLL_INFO2 ) << "Destroying FormManager" << Log::endlog;
		XMLParser::getSingleton().UnregisterLoadHandler( "FormDef", &FormManager::_FormDef_XMLNode_Load );
		XMLParser::getSingleton().UnregisterUnloadHandler( "FormDef", &FormManager::_FormDef_XMLNode_Unload );
	}
	//############################################################################
	bool FormManager::_FormDef_XMLNode_Load( const XMLNode& node, const std::string& nodePath ){
		OG_NYI;
	}
	//############################################################################
	bool FormManager::_FormDef_XMLNode_Unload( const XMLNode& node, const std::string& nodePath ){
		OG_NYI;
	}
	//############################################################################
}
