// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef EE1973FF_45A9_47ea_BBE1_A9DEFA47DF60
#define EE1973FF_45A9_47ea_BBE1_A9DEFA47DF60

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Value.h"
#include "OpenGUI_XML.h"

namespace OpenGUI {

	class System; // forward declaration
	class Widget; // forward declaration
	class FormEntry; // forward declaration
	class WidgetCollection; // forward declaration


	//! The base unit that comprises FormDefinition objects
	class OPENGUI_API FormEntry {
	public:
		FormEntry( const std::string& WidgetName, const std::string& WidgetDef, const ValueList& propertyList );
		FormEntry( const std::string& WidgetName, const std::string& BaseName, const std::string& LibraryName, const ValueList& propertyList );
		~FormEntry();
		//! adds a copy of the given \c child to this FormEntry
		void addChild( FormEntry& child );
		//! adds the child given directly to this FormEntry, assuming ownership of memory
		void addChild( FormEntry* child );
		//! creates a clone of this FormEntry
		FormEntry* clone()const;
		//! copy constructor
		explicit FormEntry( const FormEntry& copy );

		//! Overloaded assignment operator copies all members, but duplicates (clones) the pointer list of children
		FormEntry& operator=( const FormEntry& right );

		//! builds a widget hierarchy from this FormEntry tree
		Widget* buildTree();
	protected:
		std::string mWidgetName;
		std::string mBaseName; // holds DefName when mByWidgetDef == true
		std::string mLibrary;
		bool mByWidgetDef;
		ValueList mProperties;
		typedef std::list<FormEntry*> FormEntryList;
		FormEntryList mChildren;
	};


	//! Manages creating, destroying, and lookup of FormDefinition objects
	class OPENGUI_API FormManager: public Singleton<FormManager> {
		friend class System; // so System can create/destroy
	public:
		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static FormManager& getSingleton( void );

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static FormManager* getSingletonPtr( void );

		//! Defines a Form for later use according to the provided \c formDefinition, which can be recalled by the given \c formName
		void DefineForm( const std::string& formName, FormEntry& formRoot );
		//! Removes a previously defined Form by the given \c formName
		void UndefineForm( const std::string& formName );

		//! Creates a predefined form, signified by \c formName, within the given \c container, assigning the given \c widgetName to the form's root widget
		Widget* CreateForm( const std::string& formName, WidgetCollection* container = 0, const std::string& widgetName = "" );

	protected:
		//! Same as other DefineForm, except that this does not duplicate the given \c formRoot, and instead stored the pointer and assumes ownership
		void DefineForm( const std::string& formName, FormEntry* formRoot );
		FormManager();
		~FormManager();

	private:
		typedef std::map<std::string, FormEntry*> FormDefinitionMap;
		FormDefinitionMap mFormDefinitions;
		void UndefineAllForms();

		static bool _FormDef_XMLNode_Load( const XMLNode& node, const std::string& nodePath );
		static bool _FormDef_XMLNode_Unload( const XMLNode& node, const std::string& nodePath );
		static FormEntry* _FormDef_Load_FormEntry( const XMLNode& node );

	};

}

#endif // EE1973FF_45A9_47ea_BBE1_A9DEFA47DF60
