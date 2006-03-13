#ifndef A4CECB60_470E_4091_8B2C_ED4A0D9F1440
#define A4CECB60_470E_4091_8B2C_ED4A0D9F1440

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Singleton.h"


namespace OpenGUI{
	//forward declaration
	namespace Widgets{class Widget;};

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
	/*! 
	*/
	class OPENGUI_API WidgetTemplateManager : public Singleton<WidgetTemplateManager> {
	public:
		WidgetTemplateManager();
		~WidgetTemplateManager();

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static WidgetTemplateManager& getSingleton(void);

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static WidgetTemplateManager* getSingletonPtr(void);

		void createTemplate(std::string templateName, std::string baseGroupName, std::string baseWidgetName);
		void destroyTemplate(std::string templateName);
		void addTemplateProperty(std::string templateName, std::string propertyName, std::string propertyValue);
		void removeTemplateProperty(std::string templateName, std::string propertyName);
		Widgets::Widget* createWidget(std::string templateName);

		//! Loads Templates from an XML document.
		/*! Any conflicting templates will be appended, any non-template related
			XML entities are silently ignored.
		*/
		void LoadTemplatesFromXML(std::string xmlFilename);

	private:
		typedef std::map<std::string,WidgetTemplate*> WidgetTemplateMap;
		WidgetTemplateMap mWidgetTemplateMap;
		void _loadTemplateFromTinyXMLElement(void* tXelementPtr);
	};

};

#endif

