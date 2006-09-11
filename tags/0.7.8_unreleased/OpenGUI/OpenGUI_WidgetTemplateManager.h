#ifndef A4CECB60_470E_4091_8B2C_ED4A0D9F1440
#define A4CECB60_470E_4091_8B2C_ED4A0D9F1440

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Singleton.h"


namespace OpenGUI{
	//forward declaration
	namespace Widgets{class Widget;};

	//! Represents a single template for widget creation, containing all property definitions, and provides methods for creating widgets based on this template.
	class OPENGUI_API WidgetTemplate{
	public:
		//! Constructor. Arguments specify the base widget that this template if built around
		WidgetTemplate(std::string baseGroup, std::string baseWidget)
			: mBaseGroupName(baseGroup), mBaseWidgetName(baseWidget) {}
		//! destructor
		~WidgetTemplate() {}

		//! create a widget based on this template, returns 0 on failure (which should only occur if the base widget cannot be found)
		Widgets::Widget* createWidget();
		//! Adds a preset property to the template (case insensitive)
		void addProperty(std::string propertyName, std::string propertyValue);
		//! Removes the given preset property from the template (case insensitive)
		void removeProperty(std::string propertyName);

		//! A single item within a PropertyList
		typedef struct _PropertyListItem {
			std::string Property; //!< property name
			std::string Value; //!< property value
			bool operator<(const _PropertyListItem& right){return Property < right.Property;}
		} PropertyListItem;
		//! A list of PropertyListItem's that is used by WidgetTemplate::getProperties()
		typedef std::list<PropertyListItem> PropertyList;
		//! returns a list of the template properties, paired with their current values
		PropertyList getProperties();

	private:
		typedef std::map<std::string, std::string> TemplatePropertyMap;
		std::string mBaseGroupName;
		std::string mBaseWidgetName;
		TemplatePropertyMap mPropertyMap;
	};

	


	//! Provides a template based widget creation system.
	/*! Using this system, applications can create widgets from predefined templates,
		where any or all properties for the widget are already defined.

		\note You currently cannot create Templates based on other Templates.
	*/
	class OPENGUI_API WidgetTemplateManager : public Singleton<WidgetTemplateManager> {
		friend class XMLParser;
	public:
		WidgetTemplateManager();
		~WidgetTemplateManager();

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static WidgetTemplateManager& getSingleton(void);

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static WidgetTemplateManager* getSingletonPtr(void);

		//! Create a new template (\c templateName) based on the widget defined by \c baseGroup and \c baseWidgetName
		void createTemplate(std::string templateName, std::string baseGroupName, std::string baseWidgetName);
		//! Destroy the template named \c templateName
		void destroyTemplate(std::string templateName);
		//! Add a new property preset value to be applied to widgets coming from this template.
		void addTemplateProperty(std::string templateName, std::string propertyName, std::string propertyValue);
		//! Remove an existing property preset from an existing template.
		void removeTemplateProperty(std::string templateName, std::string propertyName);
		//! Create a widget based on the given template
		Widgets::Widget* createWidget(std::string templateName);

		//! Loads Templates from an XML document.
		/*! Any conflicting templates will be appended, any non-template related
			XML entities are silently ignored (only processes \<Template\> and enclosed \<Property\> tags).
		*/
		void LoadTemplatesFromXML(std::string xmlFilename);

		//! returns a pointer to the template that was requested by \c templateName
		const WidgetTemplate* getWidgetTemplate(const std::string& templateName);

		//! List of strings (WidgetTemplate names) used as a return value for WidgetTemplateManager::getWidgetTemplateList()
		typedef std::list<std::string> WidgetTemplateList;

		//! Returns a sorted list of strings of all registered template names. The list items can be fed back to getWidgetTemplate() to retrieve the actual template
		WidgetTemplateList getWidgetTemplateList();

	private:
		typedef std::map<std::string,WidgetTemplate*> WidgetTemplateMap;
		WidgetTemplateMap mWidgetTemplateMap;
		void _loadTemplateFromTinyXMLElement(void* tXelementPtr);
	};

};

#endif

