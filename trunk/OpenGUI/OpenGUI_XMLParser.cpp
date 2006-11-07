#include "tinyxml.h"
#include "OpenGUI_XMLParser.h"
#include "OpenGUI_XML.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_StrConv.h"

namespace OpenGUI {
	//############################################################################
	template<> XMLParser* Singleton<XMLParser>::mptr_Singleton = 0;
	//############################################################################
	XMLParser& XMLParser::getSingleton( void ) {
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	XMLParser* XMLParser::getSingletonPtr( void ) {
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	XMLParser::XMLParser() {
		/**/
		LogManager::SlogMsg( "INIT", OGLL_INFO2 ) << "Creating XMLParser" << Log::endlog;
		RegisterLoadHandler( "Include", &XMLParser::_IncludeLoadHandler );
		RegisterUnloadHandler( "Include", &XMLParser::_IncludeUnloadHandler );
	}
	//############################################################################
	XMLParser::~XMLParser() {
		/**/
		LogManager::SlogMsg( "SHUTDOWN", OGLL_INFO2 ) << "Destroying XMLParser" << Log::endlog;
		UnregisterLoadHandler( "Include", &XMLParser::_IncludeLoadHandler );
		UnregisterUnloadHandler( "Include", &XMLParser::_IncludeUnloadHandler );
	}
	//############################################################################
	void XMLParser::LoadFromFile( const std::string& xmlFilename ) {
		LogManager::SlogMsg( "XMLParser", OGLL_INFO ) << "BEGIN LoadFromFile: " << xmlFilename << Log::endlog;
		XMLDoc doc;
		doc.loadFile( xmlFilename );
		ProcessXML_Load( doc, "/" );
		LogManager::SlogMsg( "XMLParser", OGLL_INFO ) << "END LoadFromFile: " << xmlFilename << Log::endlog;
	}
	//############################################################################
	void XMLParser::UnloadFromFile( const std::string& xmlFilename ) {
		LogManager::SlogMsg( "XMLParser", OGLL_INFO ) << "BEGIN UnloadFromFile: " << xmlFilename << Log::endlog;
		XMLDoc doc;
		doc.loadFile( xmlFilename );
		ProcessXML_Unload( doc, "/" );
		LogManager::SlogMsg( "XMLParser", OGLL_INFO ) << "END UnloadFromFile: " << xmlFilename << Log::endlog;
	}
	//############################################################################
	/*! Registering for a path that is already registered is legal, and will override the
	existing registration. Unregistering your override will restore the previously registered
	handler. */
	void XMLParser::RegisterLoadHandler( const std::string& tagName, XMLNodeHandler* handler_callback ) {
		HandlerList& handlers = mLoadMap[tagName];
		for ( HandlerList::iterator iter = handlers.begin(); iter != handlers.end(); iter++ ) {
			XMLNodeHandler* handler = ( *iter );
			if ( handler == handler_callback ) {
				std::stringstream ss;
				ss << "XMLLoad: ";
				ss << tagName;
				ss << " @ ";
				ss << "0x" << (( size_t ) handler_callback );
				ss << " Already registered";
				OG_THROW( Exception::ERR_DUPLICATE_ITEM, ss.str(), __FUNCTION__ );
			}
		}
		LogManager::SlogMsg( "XMLParser", OGLL_INFO2 )
		<< "Register XMLLoad: " << tagName << " @ " << ( handler_callback ) << Log::endlog;
		handlers.push_front( handler_callback );
	}
	//############################################################################
	/*! \see RegisterLoadHandler() */
	void XMLParser::UnregisterLoadHandler( const std::string& tagName, XMLNodeHandler* handler_callback ) {
		HandlerList& handlers = mLoadMap[tagName];
		for ( HandlerList::iterator iter = handlers.begin(); iter != handlers.end(); iter++ ) {
			XMLNodeHandler* handler = ( *iter );
			if ( handler == handler_callback ) {
				LogManager::SlogMsg( "XMLParser", OGLL_INFO2 )
				<< "Unregister XMLLoad: " << tagName << " @ " << ( handler_callback ) << Log::endlog;
				handlers.erase( iter );
				return;
			}
		}
		std::stringstream ss;
		ss << "XMLLoad: ";
		ss << tagName;
		ss << " @ ";
		ss << "0x" << (( size_t ) handler_callback );
		ss << " Not Found!";
		OG_THROW( Exception::ERR_ITEM_NOT_FOUND, ss.str(), __FUNCTION__ );
	}
	//############################################################################
	void XMLParser::RegisterUnloadHandler( const std::string& tagName, XMLNodeHandler* handler_callback ) {
		HandlerList& handlers = mUnloadMap[tagName];
		for ( HandlerList::iterator iter = handlers.begin(); iter != handlers.end(); iter++ ) {
			XMLNodeHandler* handler = ( *iter );
			if ( handler == handler_callback ) {
				std::stringstream ss;
				ss << "XMLUnload: ";
				ss << tagName;
				ss << " @ ";
				ss << "0x" << (( size_t ) handler_callback );
				ss << " Already registered";
				OG_THROW( Exception::ERR_DUPLICATE_ITEM, ss.str(), __FUNCTION__ );
			}
		}
		LogManager::SlogMsg( "XMLParser", OGLL_INFO2 )
		<< "Register XMLUnload: " << tagName << " @ " << ( handler_callback ) << Log::endlog;
		handlers.push_front( handler_callback );
	}
	//############################################################################
	void XMLParser::UnregisterUnloadHandler( const std::string& tagName, XMLNodeHandler* handler_callback ) {
		HandlerList& handlers = mUnloadMap[tagName];
		for ( HandlerList::iterator iter = handlers.begin(); iter != handlers.end(); iter++ ) {
			XMLNodeHandler* handler = ( *iter );
			if ( handler == handler_callback ) {
				LogManager::SlogMsg( "XMLParser", OGLL_INFO2 )
				<< "Unregister XMLUnload: " << tagName << " @ " << ( handler_callback ) << Log::endlog;
				handlers.erase( iter );
				return;
			}
		}
		std::stringstream ss;
		ss << "XMLUnload: ";
		ss << tagName;
		ss << " @ ";
		ss << "0x" << (( size_t ) handler_callback );
		ss << " Not Found!";
		OG_THROW( Exception::ERR_ITEM_NOT_FOUND, ss.str(), __FUNCTION__ );
	}
	//############################################################################
	void XMLParser::ProcessXML_LoadNode( const XMLNode& node, const std::string& nodePath ) {
		if ( !fireCallback( mLoadMap, node, nodePath ) ) {
			LogManager::SlogMsg( "XMLParser", OGLL_WARN )
			<< "No XMLLoad handler processed tag: " << node.getTagName() << Log::endlog;
		}
	}
	//############################################################################
	void XMLParser::ProcessXML_UnloadNode( const XMLNode& node, const std::string& nodePath ) {
		if ( !fireCallback( mUnloadMap, node, nodePath ) ) {
			LogManager::SlogMsg( "XMLParser", OGLL_WARN )
			<< "No XMLUnload handler processed tag: " << node.getTagName() << Log::endlog;
		}
	}
	//############################################################################
	void XMLParser::ProcessXML_Load( const XMLNodeContainer& container, const std::string& nodePath ) {
		XMLNodeList list = container.getChildren();
		for ( XMLNodeList::iterator iter = list.begin(); list.end() != iter; iter++ ) {
			XMLNode& node = *( *iter );
			ProcessXML_LoadNode( node, nodePath );
		}
	}
	//############################################################################
	void XMLParser::ProcessXML_Unload( const XMLNodeContainer& container, const std::string& nodePath ) {
		XMLNodeList list = container.getChildren();
		for ( XMLNodeList::reverse_iterator iter = list.rbegin(); list.rend() != iter; iter++ ) {
			XMLNode& node = *( *iter );
			ProcessXML_UnloadNode( node, nodePath );
		}
	}
	//############################################################################
	bool XMLParser::fireCallback( XMLHandlerMap& handlerMap, const XMLNode& node, const std::string& nodePath ) {
		XMLHandlerMap::iterator mapIter = handlerMap.find( node.getTagName() );
		if ( mapIter != handlerMap.end() && mapIter->second.size() > 0 ) {
			HandlerList& handleList = mapIter->second;
			for ( HandlerList::iterator iter = handleList.begin(); iter != handleList.end(); iter++ ) {
				XMLNodeHandler* handler_callback = ( *iter );
				bool retval;
				try {
					retval = ( *handler_callback )( node, nodePath );
				} catch ( ... ) {
					XMLDoc* doc = node.getDoc();
					std::string file;
					if ( doc ) file = doc->getFileName();
					OG_THROW( Exception::ERR_INTERNAL_ERROR,
							  "Unhandled exception in XML handler callback! @" + file + ":"
							  + nodePath + node.dump(), __FUNCTION__ );
				}
				if ( retval )
					return true;
			}
		} else {
			LogManager::SlogMsg( "XMLParser", OGLL_WARN )
			<< "No handler registered for tag: " << node.getTagName() << Log::endlog;
		}
		return false;
	}
	//############################################################################
	bool XMLParser::_IncludeLoadHandler( const XMLNode& node, const std::string& nodePath ) {
		std::string filename = node.getAttribute( "File" );
		if ( filename.length() <= 0 ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "<Include> tag missing 'File' attribute.", __FUNCTION__ );
		}
		// test include list for recursion
		if ( _Included( filename ) ) {
			// if failed, warn and skip
			LogManager::SlogMsg( "XMLParser", OGLL_WARN )
			<< "XML Include loop detected, breaking include: " << filename << Log::endlog;
			return true;
		}

		// otherwise store it and do it
		LogManager::SlogMsg( "XMLParser", OGLL_INFO2 ) << "XML <Include> >>>: " << filename << Log::endlog;
		mIncludeList.push_front( filename );
		XMLDoc doc;
		doc.loadFile( filename );
		XMLNodeList children = doc.getChildren();
		for ( XMLNodeList::iterator iter = children.begin(); children.end() != iter; iter++ ) {
			XMLNode& child = *( *iter );
			child.setParent( node.getParent() );
			XMLParser::getSingleton().ProcessXML_LoadNode( child, nodePath );
			child.setParent( &doc );
		}
		LogManager::SlogMsg( "XMLParser", OGLL_INFO2 ) << "XML <Include> <<<: " << filename << Log::endlog;

		// pop our recursion from the list
		mIncludeList.pop_front();
		return true;
	}
	//############################################################################
	bool XMLParser::_IncludeUnloadHandler( const XMLNode& node, const std::string& nodePath ) {
		std::string filename = node.getAttribute( "File" );
		if ( filename.length() <= 0 ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "<Include> tag missing 'File' attribute.", __FUNCTION__ );
		}
		// test include list for recursion
		if ( _Included( filename ) ) {
			// if failed, warn and skip
			LogManager::SlogMsg( "XMLParser", OGLL_WARN )
			<< "XML Include loop detected, breaking include: " << filename << Log::endlog;
			return true;
		}

		// otherwise store it and do it
		LogManager::SlogMsg( "XMLParser", OGLL_INFO2 ) << "XML <Include> >>>: " << filename << Log::endlog;
		mIncludeList.push_front( filename );
		XMLDoc doc;
		doc.loadFile( filename );
		XMLNodeList children = doc.getChildren();
		for ( XMLNodeList::reverse_iterator iter = children.rbegin(); children.rend() != iter; iter++ ) {
			XMLNode& child = *( *iter );
			child.setParent( node.getParent() );
			XMLParser::getSingleton().ProcessXML_UnloadNode( child, nodePath );
			child.setParent( &doc );
		}
		LogManager::SlogMsg( "XMLParser", OGLL_INFO2 ) << "XML <Include> <<<: " << filename << Log::endlog;

		// pop our recursion from the list
		mIncludeList.pop_front();
		return true;
	}
	//############################################################################
	XMLParser::IncludeList XMLParser::mIncludeList;
	//############################################################################
	bool XMLParser::_Included( const std::string& filename ) {
		std::string file = filename;
		StrConv::toLower( file );
		for ( IncludeList::iterator iter = mIncludeList.begin(); iter != mIncludeList.end();iter++ ) {
			std::string item = ( *iter );
			StrConv::toLower( item );
			if ( item == file )
				return true;
		}
		return false;
	}
}//namespace OpenGUI {
