#ifndef BE0F3698_B136_43b6_993F_F93035AB500C
#define BE0F3698_B136_43b6_993F_F93035AB500C

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_XML.h"

namespace OpenGUI {
	class System; // forward declaration


	//! Callback signature for XML load/unload handlers
	/*!
	The handler callback is called for each tag that matches its registered
	tag name. The \c nodePath is sent to the handler so that it can determine if
	it is interested in handling each particular tag. If a handler does not process
	a tag when asked (signified by returning \c false), the next previously registered
	handler for that tag is called. This process continues until either the tag was
	handled, or XMLParser runs out of registered handlers for the tag (in which case
	it will log a warning about the unhandled tag and continue processing).
	\param node Reference to the node that spawned the handler callback.
	\param nodePath The current nodePath leading up to this node, but not including it.
	\return \c true if you handled the tag, \c false if you didn't (in which case the
	next registered handler for that tag will have the opportunity to handle it)
	*/
	typedef bool XMLNodeHandler(const XMLNode& node, const std::string& nodePath );

	//! Provides complete loading of xml files containing data for all different subsystems.
	/*! This class provides complete parsing of XML files. It will delegate top level tags
		to the necessary subsystem as it sees them, so you can load data into several
		subsystems with a single function call.

		It also supports use of the '\<include file="somefile.xml"\>' tag, which allows
		you to split your XML files into smaller and more specific pieces, while allowing
		them to automatically load their dependents.

		All tags are immediately evaluated in the order they are read, so watch your
		dependencies. This also means that include files are evaluated at the time they
		are discovered. If you need your includes to happen first, put them at the top of the
		XML file. For any single execution of this function, an include file will only be
		evaluated the first time it is requested. Subsequent requests for an include file are
		logged as warnings, but otherwise ignored. <i>(The multiple include testing is performed
		using a simple case-insensitive string comparison. Minor path tricks will fool it, but
		are generally discouraged.)</i>

		\see \ref XMLDOC "The XML Documentation" for a complete reference to using XML with %OpenGUI.

		XML is processed by %OpenGUI using a mixed DOM/SAX system. XML documents are fully loaded
		into a DOM tree comprised of XMLNode objects and is then walked in the appropriate direction
		for the current operation. Callbacks register to handle a particular tag signature, for
		a given operation (load/unload). When a matching signature is found, the registered 

	*/
	class OPENGUI_API XMLParser: public Singleton<XMLParser> {
		friend class System;
	private:
		XMLParser();
		~XMLParser();
	public:
		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static XMLParser& getSingleton( void );

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static XMLParser* getSingletonPtr( void );

		//! Reads the given XML file from the registered resource manager and parses the file according to the \ref XMLDOC "XML specifications"
		void LoadFromFile( const std::string& xmlFilename );

		//! Reads the given XML file from the registered resource manager and parses it in reverse, performing unloads instead of loads
		void UnloadFromFile( const std::string& xmlFilename );

		//! Registers an XML Load handler for the given \x xmlPath
		void RegisterLoadHandler( const std::string& tagName, XMLNodeHandler* handler_callback );
		//! Unregisters an XML Load handler for the given \x xmlPath
		void UnregisterLoadHandler( const std::string& tagName, XMLNodeHandler* handler_callback );

		//! Registers an XML Unload handler for the given \x xmlPath
		void RegisterUnloadHandler( const std::string& tagName, XMLNodeHandler* handler_callback );
		//! Unregisters an XML Unload handler for the given \x xmlPath
		void UnregisterUnloadHandler( const std::string& tagName, XMLNodeHandler* handler_callback );

		//! Processes the given \c container with XMLLoad handlers, using the given \c nodePath
		void ProcessXML_Load(XMLNodeContainer& container, const std::string& nodePath);
		//! Processes the given node with XMLLoad handlers, using the given \c nodePath
		void ProcessXML_Load(XMLNode& node, const std::string& nodePath);
		//! Processes the given \c container with XMLUnload handlers, using the given \c nodePath
		void ProcessXML_Unload(XMLNodeContainer& container, const std::string& nodePath);
		//! Processes the given node with XMLUnload handlers, using the given \c nodePath
		void ProcessXML_Unload(XMLNode& node, const std::string& nodePath);

	private:
		static bool _IncludeLoadHandler(const XMLNode& node, const std::string& nodePath );
		static bool _IncludeUnloadHandler(const XMLNode& node, const std::string& nodePath );
		static bool _Included(const std::string& filename);
		typedef std::list<std::string> IncludeList;
		static IncludeList mIncludeList;

		//static void ParseXMLFile( const std::string& xmlFilename, IncludeSet& includesToIgnore, unsigned int depth );
		typedef std::list<XMLNodeHandler*> HandlerList;
		typedef std::map<std::string, HandlerList> XMLHandlerMap;
		XMLHandlerMap mLoadMap;
		XMLHandlerMap mUnloadMap;
		bool fireCallback(XMLHandlerMap& handlerMap, const XMLNode& node, const std::string& nodePath);
	};
};

#endif // BE0F3698_B136_43b6_993F_F93035AB500C

