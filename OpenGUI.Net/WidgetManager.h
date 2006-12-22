// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef WidgetManager_h__
#define WidgetManager_h__

using namespace System;

namespace OpenGUI_Net {

	ref class Widget;

	public ref class WidgetManager sealed {
	public:
		static WidgetManager ^ getHandle();

		// Create a Widget that was registered under the given \c Name and optionally \c Library
		Widget ^ CreateRawWidget( String ^ Name );
		Widget ^ CreateRawWidget( String ^ Name, String ^ Library );

		// Creates and initializes a Widget that was previously defined by DefineWidget()
		Widget ^ CreateDefinedWidget( String ^ Name );

		// Defines a new Widget under the given \c Name with the given \c propertyList, using \c BaseName and \c BaseLibrary as the source
		//void DefineWidget( String^ Name, const ValueList& propertyList, String^ BaseName, String^ BaseLibrary );
		// Undefines an existing Widget definition by \c Name
		void UndefineWidget( String ^ Name );

		// inner type of WidgetRegPairList
		//typedef std::pair<std::string, std::string> WidgetRegPair;
		// return type of GetRegisteredWidgets()
		//typedef std::list<WidgetRegPair> WidgetRegPairList;
		// returns a pair list of all registered widgets
		//WidgetRegPairList GetRegisteredWidgets();

		// return type of GetDefinedWidgets()
		//typedef std::list<std::string> WidgetDefList;
		// returns a list of all defined widgets
		//WidgetDefList GetDefinedWidgets();

		// returns the number of registered widgets across the number of libraries, as well as the number of widget definitions
		unsigned int getStat_RegWidgets();
		unsigned int getStat_RegLibs();
		unsigned int getStat_DefWidgets();


		WidgetManager( OpenGUI::WidgetManager* widgetManagerPtr );

	private:
		OpenGUI::WidgetManager* mWidgetManager;
		void sanityTest();
		static WidgetManager ^ gHandle;
	};

} // namespace OpenGUI_Net {


#endif // WidgetManager_h__
