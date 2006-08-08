#ifndef A4CECB60_470E_4091_8B2C_ED4A0D9F1440
#define A4CECB60_470E_4091_8B2C_ED4A0D9F1440

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Singleton.h"


namespace OpenGUI{
	//forward declaration
	namespace Widgets{class Widget;};

	//! \internal this is an internal component of the WidgetTemplateManager, and should not be used directly by applications
	class WidgetTemplate{
	public:
		WidgetTemplate(std::string baseGroup, std::string baseWidget)
			: mBaseGroupName(baseGroup), mBaseWidgetName(baseWidget) {}
		~WidgetTemplate() {}

		Widgets::Widget* createWidget();
		void addProperty(std::string propertyName, std::string propertyValue);
		void removeProperty(std::string propertyName);

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

	private:
		typedef std::map<std::string,WidgetTemplate*> WidgetTemplateMap;
		WidgetTemplateMap mWidgetTemplateMap;
		void _loadTemplateFromTinyXMLElement(void* tXelementPtr);
	};

};

#endif

