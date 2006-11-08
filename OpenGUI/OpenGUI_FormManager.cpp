#include "OpenGUI_FormManager.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_XMLParser.h"
#include "OpenGUI_Widget.h"
#include "OpenGUI_I_WidgetContainer.h"
#include "OpenGUI_WidgetManager.h"
#include "OpenGUI_Value.h"

namespace OpenGUI {
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
	FormManager::FormManager() {
		LogManager::SlogMsg( "INIT", OGLL_INFO2 ) << "Creating FormManager" << Log::endlog;
		XMLParser::getSingleton().RegisterLoadHandler( "FormDef", &FormManager::_FormDef_XMLNode_Load );
		XMLParser::getSingleton().RegisterUnloadHandler( "FormDef", &FormManager::_FormDef_XMLNode_Unload );
	}
	//############################################################################
	FormManager::~FormManager() {
		LogManager::SlogMsg( "SHUTDOWN", OGLL_INFO2 ) << "Destroying FormManager" << Log::endlog;
		XMLParser::getSingleton().UnregisterLoadHandler( "FormDef", &FormManager::_FormDef_XMLNode_Load );
		XMLParser::getSingleton().UnregisterUnloadHandler( "FormDef", &FormManager::_FormDef_XMLNode_Unload );

		LogManager::SlogMsg( "FormManager", OGLL_INFO )
		<< "Stagnant FormDefinitions: " << mFormDefinitions.size() << Log::endlog;
		UndefineAllForms();
	}
	//############################################################################
	void FormManager::DefineForm( const std::string& formName, FormEntry& formRoot ) {
		FormEntry* root = new FormEntry( formRoot );
		try {
			DefineForm( formName, root );
		} catch ( Exception& ) {
			if ( root )
				delete root;
			throw;
		}
	}
	//############################################################################
	void FormManager::DefineForm( const std::string& formName, FormEntry* formRoot ) {
		if ( formName == "" )
			OG_THROW( Exception::ERR_INVALIDPARAMS, "FormDefinition name cannot be empty", __FUNCTION__ );
		FormDefinitionMap::iterator iter = mFormDefinitions.find( formName );
		if ( iter != mFormDefinitions.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "FormDefinition already exists with given name: " + formName, __FUNCTION__ );
		mFormDefinitions[formName] = formRoot;
	}
	//############################################################################
	void FormManager::UndefineForm( const std::string& formName ) {
		FormDefinitionMap::iterator iter = mFormDefinitions.find( formName );
		if ( iter == mFormDefinitions.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "FormDefinition with given name not found: " + formName, __FUNCTION__ );
		FormEntry* root = iter->second;
		if ( root )
			delete root;
		iter->second = 0;
		mFormDefinitions.erase( iter );
	}
	//############################################################################
	void FormManager::UndefineAllForms() {
		for ( FormDefinitionMap::iterator iter = mFormDefinitions.begin(); iter != mFormDefinitions.end();iter++ ) {
			FormEntry* root = iter->second;
			if ( root )
				delete root;
			iter->second = 0;
		}
		mFormDefinitions.clear();
	}
	//############################################################################
	void FormManager::CreateForm( const std::string& formName, I_WidgetContainer& container, const std::string& widgetName ) {
		FormDefinitionMap::iterator iter = mFormDefinitions.find( formName );
		if ( iter == mFormDefinitions.end() )
			OG_THROW( Exception::ERR_DUPLICATE_ITEM, "FormDefinition with given name not found: " + formName, __FUNCTION__ );
		FormEntry* root = iter->second;

		//create widget tree
		Widget* rootWidget = 0;
		rootWidget = root->buildTree();
		if ( !rootWidget )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Failed to create Form: " + formName, __FUNCTION__ );
		//change the name and attach it
		if ( rootWidget ) {
			try {
				rootWidget->setName( widgetName );
				container.Children.add_back( rootWidget, true );
			} catch ( Exception& ) {
				delete rootWidget;
				throw;
			}
		}
	}
	//############################################################################
	bool FormManager::_FormDef_XMLNode_Load( const XMLNode& node, const std::string& nodePath ) {
		FormManager& manager = FormManager::getSingleton();

		// we only handle these tags within <OpenGUI>
		if ( nodePath != "/OpenGUI/" )
			return false;

		const std::string Name = node.getAttribute( "Name" );

		FormEntry* root = 0;
		try {
			root = _FormDef_Load_FormEntry( node );
			manager.DefineForm( Name, root );
		} catch ( Exception& ) {
			if ( root )
				delete root;
			throw;
		}
		return true;
	}
	//############################################################################
	bool FormManager::_FormDef_XMLNode_Unload( const XMLNode& node, const std::string& nodePath ) {
		FormManager& manager = FormManager::getSingleton();

		// we only handle these tags within <OpenGUI>
		if ( nodePath != "/OpenGUI/" )
			return false;

		const std::string Name = node.getAttribute( "Name" );
		manager.UndefineForm( Name );
		return true;
	}
	//############################################################################
	FormEntry* FormManager::_FormDef_Load_FormEntry( const XMLNode& node ) {
		/**/
		if ( node.hasAttribute( "DefName" )
				&& ( node.hasAttribute( "BaseName" ) || node.hasAttribute( "BaseLibrary" ) ) ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "<Widget> attribute 'DefName' is mutually exclusive with 'BaseName' and 'BaseLibrary': " + node.dump(), __FUNCTION__ );
		}

		const std::string Name = node.getAttribute( "Name" );
		std::string defName;
		std::string baseName;
		std::string baseLibrary;
		bool hasDef;

		if ( node.hasAttribute( "DefName" ) ) {
			defName = node.getAttribute( "DefName" );
			hasDef = true;
		} else {
			baseName = node.getAttribute( "BaseName" );
			baseLibrary = node.getAttribute( "BaseLibrary" );
			hasDef = false;
		}

		//handle all properties
		ValueList valueList;
		XMLNodeList xmlProps = node.getChildren( "Property" );
		for ( XMLNodeList::iterator iter = xmlProps.begin(); iter != xmlProps.end(); iter++ ) {
			XMLNode* prop = ( *iter );
			Value value;
			value.LoadFromXMLNode( *prop );
			valueList.push_back( value );
		}

		FormEntry* thisEntry = 0;
		try {
			if ( hasDef ) {
				thisEntry = new FormEntry( Name, defName, valueList );
			} else {
				thisEntry = new FormEntry( Name, baseName, baseLibrary, valueList );
			}

			// now process all tags and only handle the <Widget> tags
			XMLNodeList childNodes = node.getChildren();
			for ( XMLNodeList::iterator iter = childNodes.begin(); iter != childNodes.end(); iter++ ) {
				XMLNode* child = ( *iter );
				if ( child->getTagName() == "Widget" ) {
					FormEntry* childEntry = 0;
					childEntry = _FormDef_Load_FormEntry( *child );
					thisEntry->addChild( childEntry );
				}
			}
		} catch ( Exception& ) {
			// catch any reasonable exception, clean up, then rethrow
			if ( thisEntry )
				delete thisEntry;
			throw;
		}
		return thisEntry;
	}
	//############################################################################
// 	void FormManager::_Form_XMLNode_IntoContainer( const XMLNode& formNode, I_WidgetContainer& widgetContainer ) {
// 		OG_NYI;
// 	}
	//############################################################################


	//############################################################################
	//############################################################################
	//#########################  I STILL LIKE FENCING  ###########################
	//############################################################################
	//############################################################################


	//############################################################################
	FormEntry::FormEntry( const std::string& WidgetName, const std::string& WidgetDef, const ValueList& propertyList )
			: mWidgetName( WidgetName ), mBaseName( WidgetDef ), mLibrary( "" ), mByWidgetDef( true ), mProperties( propertyList ) {
		/* nothing special */
	}
	//############################################################################
	FormEntry::FormEntry( const std::string& WidgetName, const std::string& BaseName, const std::string& LibraryName, const ValueList& propertyList )
			: mWidgetName( WidgetName ), mBaseName( BaseName ), mLibrary( LibraryName ), mByWidgetDef( false ), mProperties( propertyList ) {
		/* nothing special */
	}
	//############################################################################
	FormEntry::~FormEntry() {
		// clean up by destroying all children
		for ( FormEntryList::iterator iter = mChildren.begin(); iter != mChildren.end();iter++ ) {
			FormEntry* child = ( *iter );
			delete child;
		}
		mChildren.clear();
	}
	//############################################################################
	FormEntry* FormEntry::clone()const {
		FormEntry* out = new FormEntry( *this );
		return out;
	}
	//############################################################################
	FormEntry::FormEntry( const FormEntry& copy ) {
		mWidgetName = copy.mWidgetName;
		mBaseName = copy.mBaseName;
		mLibrary = copy.mLibrary;
		mByWidgetDef = copy.mByWidgetDef;
		mProperties = copy.mProperties;
		typedef std::list<FormEntry*> FormEntryList;
		for ( FormEntryList::const_iterator iter = copy.mChildren.begin(); iter != copy.mChildren.end();iter++ ) {
			FormEntry* child = ( *iter );
			mChildren.push_back( new FormEntry( *child ) );
		}
	}
	//############################################################################
	void FormEntry::addChild( FormEntry& child ) {
		mChildren.push_back( new FormEntry( child ) );
	}
	//############################################################################
	void FormEntry::addChild( FormEntry* child ) {
		mChildren.push_back( child );
	}
	//############################################################################
	Widget* FormEntry::buildTree() {
		Widget* widget = 0;
		if ( mByWidgetDef )
			widget = WidgetManager::getSingleton().CreateDefinedWidget( mBaseName );
		else
			widget = WidgetManager::getSingleton().CreateRawWidget( mBaseName, mLibrary );

		try {
			// process stored properties
			ValueList propList = mProperties;
			while ( propList.size() > 0 ) {
				Value val = propList.pop_front();
				std::string name = val.getName();
				if ( name.length() > 0 ) {
					widget->setProperty( name, val );
				}
			}

			widget->setName( mWidgetName );

			//if we're supposed to have children, this is where we create and attach them
			if ( mChildren.size() > 0 ) {
				I_WidgetContainer* container = dynamic_cast<I_WidgetContainer*>( widget );
				if ( !container )
					OG_THROW( Exception::OP_FAILED, "Failed to cast widget into a container, as required to bare children", __FUNCTION__ );
				else {
					for ( FormEntryList::iterator iter = mChildren.begin(); iter != mChildren.end();iter++ ) {
						Widget* child = 0;
						try {
							FormEntry* childEntry = ( *iter );
							child = childEntry->buildTree();
							if ( child ) {
								container->Children.add_back( child, true );
							}
						} catch ( Exception& ) {
							if ( child )//if something broke, free child memory and rethrow
								delete child;
							child = 0;
							throw;
						}
					}
				}
			}
		} catch ( Exception& ) {
			if ( widget ) // if something broke, we need to free the memory and rethrow
				delete widget;
			widget = 0;
			throw;
		}

		return widget;
	}
	//############################################################################


}
