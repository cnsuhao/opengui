#ifndef AFC43FEB_2F65_43c8_B46B_3B027C686EFC
#define AFC43FEB_2F65_43c8_B46B_3B027C686EFC

#include "OpenGUI_Singleton.h"
#include "OpenGUI_Exports.h"

namespace OpenGUI{

	//Forward declaration
	namespace Widgets{class Widget;};

	//! Callback function pattern used for factories
	/*! Uses a C pointer because it is a lot faster to write one function and register
	it's address than it is to write an entire factory class just to create objects.
	Some design patterns are just plain wasteful. */
	typedef Widgets::Widget* (*WidgetFactoryCallback)();

	
	//! Provides an object registration and creation factory service for Widgets.
	/*! In order for custom Widget objects to be created at runtime, their class type
		must be known at compile time. Obviously it is impossible for OpenGUI to know
		about all custom Widget types when
	*/
	class OPENGUI_API WidgetFactoryManager: public Singleton<WidgetFactoryManager>{
	public:
		WidgetFactoryManager();

		~WidgetFactoryManager();

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static WidgetFactoryManager& getSingleton(void);

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static WidgetFactoryManager* getSingletonPtr(void);

		//! Allows registration of a widget factory to create widgets based on the given name.
		void registerWidgetFactory(std::string groupName, std::string widgetName, WidgetFactoryCallback factoryCallback);
		//! Removes widget factory registration of the given widget name.
		void unregisterWidgetFactory(std::string groupName, std::string widgetName);
		//! Creates a widget of the requested type name and returns a pointer. Returns 0 if none found.
		Widgets::Widget* createWidget(std::string groupName, std::string widgetName);

		//! Individual item in a WidgetFactoryList
		typedef struct _WidgetFactoryListItem {
			std::string WidgetGroup; //!< The group name that the widget is registered under
			std::string WidgetName; //!< The name of the widget
		} WidgetFactoryListItem;

		//! Used by WidgetFactoryManager::getWidgetFactoryList() to return the list of registered widgets
		typedef std::list<WidgetFactoryListItem> WidgetFactoryList;

		//! Returns a WidgetFactoryList containing all currently registered widgets
		WidgetFactoryList getWidgetFactoryList();
	private:
		std::string _buildGroupNameComposite(const std::string& groupName, const std::string& widgetName);
		typedef struct {
			std::string groupName;
			std::string widgetName;
			WidgetFactoryCallback callBack;
		} CallbackMapItem;
		typedef std::map<std::string,CallbackMapItem> CallbackMap;
		CallbackMap mCallbackmap;
	};
};//using namespace OpenGUI{

#endif


