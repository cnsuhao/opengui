#include "OpenGUI_WidgetManager.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_Widget.h"
#include "OpenGUI_XMLParser.h"
#include "OpenGUI_I_WidgetContainer.h"

namespace OpenGUI {
	template<> WidgetManager* Singleton<WidgetManager>::mptr_Singleton = 0;
	WidgetManager& WidgetManager::getSingleton( void ) {
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	WidgetManager* WidgetManager::getSingletonPtr( void ) {
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	WidgetManager::WidgetManager() {
		LogManager::SlogMsg( "INIT", OGLL_INFO2 ) << "Creating WidgetManager" << Log::endlog;
		XMLParser::getSingleton().RegisterLoadHandler( "WidgetDef", &WidgetManager::_WidgetDef_XMLNode_Load );
		XMLParser::getSingleton().RegisterUnloadHandler( "WidgetDef", &WidgetManager::_WidgetDef_XMLNode_Unload );
	}
	//############################################################################
	WidgetManager::~WidgetManager() {
		LogManager::SlogMsg( "SHUTDOWN", OGLL_INFO2 ) << "Destroying WidgetManager" << Log::endlog;
		XMLParser::getSingleton().UnregisterLoadHandler( "WidgetDef", &WidgetManager::_WidgetDef_XMLNode_Load );
		XMLParser::getSingleton().UnregisterUnloadHandler( "WidgetDef", &WidgetManager::_WidgetDef_XMLNode_Unload );

		size_t w, l, d;
		getStats( w, l, d );
		LogManager::SlogMsg( "WidgetManager", OGLL_INFO )
		<< "Stagnant Entries Tally - "
		<< "Registration (Widget:Library): "
		<< "[" << w << ":" << l << "] "
		<< "Definitions: " << d
		<< Log::endlog;
	}
	//############################################################################
	/*! If \a Library is not given or is "", the value of \a Name will be tested to see
	if it is in a packed Name:Library format. If so then the packed value will be exploded and
	used, otherwise the full list of registered cursors is walked and the first entry with
	a matching \a Name is used. */
	Widget* WidgetManager::CreateRawWidget( const std::string& Name, const std::string& Library ) {
		if ( Library == "" ) { // either packed Name:Library or just Name with first match
			size_t nPos;
			nPos = Name.find( ':' );
			if ( nPos != std::string::npos ) { // packed Name:Library, so explode and recall
				std::string NewName, NewLib;
				NewName = Name.substr( 0, nPos );
				NewLib = Name.substr( nPos + 1 );
				return CreateRawWidget( NewName, NewLib );
			} else { // if we weren't given a library then we need to search for first match by Name
				for ( LibraryMap::iterator iter = mLibraryMap.begin(); iter != mLibraryMap.end(); iter++ ) {
					WidgetFactoryMap& fMap = iter->second;
					WidgetFactoryMap::iterator iter2 = fMap.find( Name );
					if ( iter2 != fMap.end() ) {
						const std::string& Lib = iter->first;
						return CreateRawWidget( Name, Lib );
					}
				}
				OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "No Widget registered with Name: " + Name, __FUNCTION__ );
			}
		}
		WidgetFactoryMap& fMap = mLibraryMap[Library];
		WidgetFactoryMap::iterator iter = fMap.find( Name );
		if ( iter == fMap.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Widget not registered: " + Name + ":" + Library, __FUNCTION__ );
		WidgetFactoryCallback* callback = iter->second;
		Widget* widget = ( *callback )();
		return widget;
	}
	//############################################################################
	void WidgetManager::RegisterWidgetFactory( const std::string& Name, const std::string& Library,
			WidgetFactoryCallback* factoryCallback ) {
		size_t nPos, lPos;
		nPos = Name.find( ':' );
		lPos = Library.find( ':' );
		if ( nPos != std::string::npos || lPos != std::string::npos )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Separator character ':' is not allowed in Name or Library", __FUNCTION__ );
		if ( Name.length() == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Name cannot be 0 length", __FUNCTION__ );
		if ( Library.length() == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Library cannot be 0 length", __FUNCTION__ );

		WidgetFactoryMap& fMap = mLibraryMap[Library];

		WidgetFactoryMap::iterator iter = fMap.find( Name );
		if ( iter != fMap.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Widget already registered: " + Name + ":" + Library, __FUNCTION__ );
		LogManager::SlogMsg( "WidgetManager", OGLL_INFO ) << "Register Widget: "
		<< Name << ":" << Library
		<< Log::endlog;
		fMap[Name] = factoryCallback;
	}
	//############################################################################
	void WidgetManager::UnregisterWidgetFactory( const std::string& Name, const std::string& Library ) {
		size_t nPos, lPos;
		nPos = Name.find( ':' );
		lPos = Library.find( ':' );
		if ( nPos != std::string::npos || lPos != std::string::npos )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Separator character ':' is not allowed in Name or Library", __FUNCTION__ );
		if ( Name.length() == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Name cannot be 0 length", __FUNCTION__ );
		if ( Library.length() == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Library cannot be 0 length", __FUNCTION__ );

		WidgetFactoryMap& fMap = mLibraryMap[Library];
		WidgetFactoryMap::iterator iter = fMap.find( Name );
		if ( iter == fMap.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "Widget not registered: " + Name + ":" + Library, __FUNCTION__ );

		LogManager::SlogMsg( "WidgetManager", OGLL_INFO ) << "Unregister Widget: "
		<< Name << ":" << Library
		<< Log::endlog;
		fMap.erase( iter );
	}
	//############################################################################
	void WidgetManager::DefineWidget( const std::string& Name, const ValueList& propertyList,
									  const std::string& BaseName, const std::string& BaseLibrary ) {
		WidgetDefinitionMap::iterator iter = mWidgetDefinitionMap.find( Name );
		if ( iter != mWidgetDefinitionMap.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "Widget already defined with given Name: " + Name, __FUNCTION__ );
		if ( Name.length() == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "Name cannot be 0 length", __FUNCTION__ );
		if ( BaseName.length() == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "BaseName cannot be 0 length", __FUNCTION__ );
		if ( BaseLibrary.length() == 0 )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "BaseLibrary cannot be 0 length", __FUNCTION__ );

		LogManager::SlogMsg( "WidgetManager", OGLL_INFO ) << "Define Widget: "
		<< Name << " -> " << BaseName << ":" << BaseLibrary
		<< Log::endlog;

		WidgetDefinition& wd = mWidgetDefinitionMap[Name];
		wd.Name = BaseName;
		wd.Library = BaseLibrary;
		wd.Properties = propertyList;
	}
	//############################################################################
	void WidgetManager::UndefineWidget( const std::string& Name ) {
		WidgetDefinitionMap::iterator iter = mWidgetDefinitionMap.find( Name );
		if ( iter == mWidgetDefinitionMap.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "No Widget defined with given Name: " + Name, __FUNCTION__ );
		LogManager::SlogMsg( "WidgetManager", OGLL_INFO ) << "Undefine Cursor: " << Name << Log::endlog;
		mWidgetDefinitionMap.erase( iter );
	}
	//############################################################################
	Widget* WidgetManager::CreateDefinedWidget( const std::string& Name ) {
		WidgetDefinitionMap::iterator iter = mWidgetDefinitionMap.find( Name );
		if ( iter == mWidgetDefinitionMap.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND, "No Widget defined with given Name: " + Name, __FUNCTION__ );
		WidgetDefinition& wd = iter->second;
		Widget* widget = CreateRawWidget( wd.Name, wd.Library );
		ValueList proplist = wd.Properties;
		while ( proplist.size() > 0 ) {
			Value val = proplist.pop_front();
			if ( val.getName().length() > 0 ) {
				widget->setProperty( val.getName(), val );
			}
		}
		return widget;
	}
	//############################################################################
	WidgetManager::WidgetRegPairList WidgetManager::GetRegisteredWidgets() {
		WidgetRegPairList retval;
		for ( LibraryMap::iterator iter = mLibraryMap.begin(); iter != mLibraryMap.end(); iter++ ) {
			std::string LibName = iter->first;
			WidgetFactoryMap& factoryMap = iter->second;
			for ( WidgetFactoryMap::iterator iter = factoryMap.begin(); iter != factoryMap.end(); iter++ ) {
				std::string BaseName = iter->first;
				retval.push_back( WidgetRegPair( BaseName, LibName ) );
			}
		}
		return retval;
	}
	//############################################################################
	WidgetManager::WidgetDefList WidgetManager::GetDefinedWidgets() {
		WidgetDefList retval;
		for ( WidgetDefinitionMap::iterator iter = mWidgetDefinitionMap.begin(); iter != mWidgetDefinitionMap.end(); iter++ ) {
			retval.push_back( iter->first );
		}
		return retval;
	}
	//############################################################################
	void WidgetManager::getStats( size_t& RegWidgets, size_t& RegLibs, size_t& DefWidgets ) {
		RegLibs = 0;
		RegWidgets = 0;
		for ( LibraryMap::iterator iter = mLibraryMap.begin(); iter != mLibraryMap.end(); iter++ ) {
			bool hadValue = false;
			WidgetFactoryMap& factoryMap = iter->second;
			for ( WidgetFactoryMap::iterator iter = factoryMap.begin(); iter != factoryMap.end(); iter++ ) {
				hadValue = true;
				RegWidgets++;
			}
			if ( hadValue ) RegLibs++;
		}

		DefWidgets = 0;
		for ( WidgetDefinitionMap::iterator iter = mWidgetDefinitionMap.begin(); iter != mWidgetDefinitionMap.end(); iter++ ) {
			DefWidgets++;
		}
	}
	//############################################################################
	bool WidgetManager::_WidgetDef_XMLNode_Load( const XMLNode& node, const std::string& nodePath ) {
		WidgetManager& manager = WidgetManager::getSingleton();

		// we only handle these tags within <OpenGUI>
		if ( nodePath != "/OpenGUI/" )
			return false;

		const std::string name = node.getAttribute( "Name" );
		const std::string basename = node.getAttribute( "BaseName" );
		const std::string baselib = node.getAttribute( "BaseLibrary" );
		ValueList propertyList;
		XMLNodeList xmlProps = node.getChildren( "Property" );
		for ( XMLNodeList::iterator iter = xmlProps.begin(); iter != xmlProps.end(); iter++ ) {
			XMLNode* prop = ( *iter );
			Value value;
			value.LoadFromXMLNode( *prop );
			propertyList.push_back( value );
		}
		manager.DefineWidget( name, propertyList, basename, baselib );
		return true;
	}
	//############################################################################
	bool WidgetManager::_WidgetDef_XMLNode_Unload( const XMLNode& node, const std::string& nodePath ) {
		WidgetManager& manager = WidgetManager::getSingleton();

		// we only handle these tags within <OpenGUI>
		if ( nodePath != "/OpenGUI/" )
			return false;

		const std::string name = node.getAttribute( "Name" );
		const std::string basename = node.getAttribute( "BaseName" );
		const std::string baselib = node.getAttribute( "BaseLibrary" );
		manager.UndefineWidget( name );
		return true;
	}
	//############################################################################
	void WidgetManager::_Widget_XMLNode_IntoContainer( const XMLNode& widgetNode, I_WidgetContainer& widgetContainer ) {
		if ( widgetNode.hasAttribute( "DefName" )
				&& ( widgetNode.hasAttribute( "BaseName" ) || widgetNode.hasAttribute( "BaseLibrary" ) ) ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "<Widget> attribute 'DefName' is mutually exclusive with 'BaseName' and 'BaseLibrary': " + widgetNode.dump(), __FUNCTION__ );
		}

		Widget* widget = 0;
		const std::string name = widgetNode.getAttribute( "Name" );
		if ( widgetNode.hasAttribute( "DefName" ) ) {
			const std::string defname = widgetNode.getAttribute( "DefName" );
			widget = WidgetManager::getSingleton().CreateDefinedWidget( defname );
		} else {
			const std::string basename = widgetNode.getAttribute( "BaseName" );
			const std::string baselib = widgetNode.getAttribute( "BaseLibrary" );
			widget = WidgetManager::getSingleton().CreateRawWidget( basename, baselib );
		}
		if ( !widget )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Failed to create Widget from XML: " + widgetNode.dump(), __FUNCTION__ );
		widget->setName( name );

		widgetContainer.Children.add_back( widget, true );

		//handle all properties
		XMLNodeList xmlProps = widgetNode.getChildren( "Property" );
		for ( XMLNodeList::iterator iter = xmlProps.begin(); iter != xmlProps.end(); iter++ ) {
			XMLNode* prop = ( *iter );
			Value value;
			value.LoadFromXMLNode( *prop );
			widget->setProperty( value.getName(), value );
		}

		// now process all tags and only handle the <Widget> and <Form> tags
		XMLNodeList childNodes = widgetNode.getChildren();
		for ( XMLNodeList::iterator iter = childNodes.begin(); iter != childNodes.end(); iter++ ) {
			XMLNode* child = (*iter);
			if(child->getTagName() == "Widget"){
				I_WidgetContainer& container = dynamic_cast<I_WidgetContainer&>(*widget);
				_Widget_XMLNode_IntoContainer(*child,container);
			}
			/*! \todo turn me back on with <Form> handling is done
			else if(child->getTagName() == "Form"){
				I_WidgetContainer& container = dynamic_cast<I_WidgetContainer&>(*widget);
				_Form_XMLNode_IntoContainer(*child,container);
			}
			*/
		}
		//we're done. yay.
	}
	//############################################################################
	//!\todo finish me <Form> and <FormDef>
	/*
	void WidgetManager::_Form_XMLNode_IntoContainer(const XMLNode& formNode, I_WidgetContainer& widgetContainer){
		OG_NYI;
	}
	//############################################################################
	bool WidgetManager::_FormDef_XMLNode_Load( const XMLNode& node, const std::string& nodePath ){
		OG_NYI;
	}
	//############################################################################
	bool WidgetManager::_FormDef_XMLNode_Unload( const XMLNode& node, const std::string& nodePath ){
		OG_NYI;
	}
	//############################################################################
	*/
}//namespace OpenGUI{
