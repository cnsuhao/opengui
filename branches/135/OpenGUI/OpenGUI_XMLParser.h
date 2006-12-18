// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef BE0F3698_B136_43b6_993F_F93035AB500C
#define BE0F3698_B136_43b6_993F_F93035AB500C

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_HandledObject.h"
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
	typedef bool XMLNodeHandler( const XMLNode& node, const std::string& nodePath );

	//! Provides XML tag registration and processing callback services
	/*! XML is processed by %OpenGUI using a mixed DOM/SAX system. XML documents are fully loaded
		into a DOM tree comprised of XMLNode objects and is then walked in the appropriate direction
		for the current operation. Callbacks register to handle a particular tag signature, for
		a given operation (load/unload). For each XML tag processed, the registered callbacks
		are called in the reverse order of registration (last registered goes first). The callbacks
		signify their successful processing of a tag by returning \c true. The first callback to
		signal successful processing of the tag will end the callback invokes for that particular tag
		instance, and the next tag is read and the callback process starts over. Any tag that is
		processed that does not result in a success signal from a registered callback will be logged
		with an unprocessed tag warning, but is otherwise ignored.

		During XML tree walking, the XMLParser will \b not automatically step deeper into the XML
		DOM tree. However, if a particular tag (such as the \c \<%OpenGUI\> tag) is used to group
		together XML tags that are specific to a particular system (in this case, %OpenGUI specific)
		then the XMLParser can be told to process the subtags of that tag by calling ProcessXML_Load()
		or ProcessXML_Unload() as the particular situation requires.

		\see \ref XMLDOC "The XML Documentation" for a complete reference of the XML structure that
		%OpenGUI processes by default

	*/
	class OPENGUI_API XMLParser: public Singleton<XMLParser>, public HandledObject {
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

		//! Registers an XML Load handler for the given \c tagName
		void RegisterLoadHandler( const std::string& tagName, XMLNodeHandler* handler_callback );
		//! Unregisters an XML Load handler for the given \c tagName
		void UnregisterLoadHandler( const std::string& tagName, XMLNodeHandler* handler_callback );

		//! Registers an XML Unload handler for the given \c tagName
		void RegisterUnloadHandler( const std::string& tagName, XMLNodeHandler* handler_callback );
		//! Unregisters an XML Unload handler for the given \c tagName
		void UnregisterUnloadHandler( const std::string& tagName, XMLNodeHandler* handler_callback );

		//! Processes the given \c container with XMLLoad handlers, using the given \c nodePath (Calls ProcessXML_LoadNode() for all container children)
		void ProcessXML_Load( const XMLNodeContainer& container, const std::string& nodePath );
		//! Processes the given node with XMLLoad handlers, using the given \c nodePath
		void ProcessXML_LoadNode( const XMLNode& node, const std::string& nodePath );
		//! Processes the given \c container with XMLUnload handlers, using the given \c nodePath (Calls ProcessXML_UnloadNode() for all container children)
		void ProcessXML_Unload( const XMLNodeContainer& container, const std::string& nodePath );
		//! Processes the given node with XMLUnload handlers, using the given \c nodePath
		void ProcessXML_UnloadNode( const XMLNode& node, const std::string& nodePath );

	private:
		static bool _IncludeLoadHandler( const XMLNode& node, const std::string& nodePath );
		static bool _IncludeUnloadHandler( const XMLNode& node, const std::string& nodePath );
		static bool _Included( const std::string& filename );
		typedef std::list<std::string> IncludeList;
		static IncludeList mIncludeList;

		typedef std::list<XMLNodeHandler*> HandlerList;
		typedef std::map<std::string, HandlerList> XMLHandlerMap;
		XMLHandlerMap mLoadMap;
		XMLHandlerMap mUnloadMap;
		bool fireCallback( XMLHandlerMap& handlerMap, const XMLNode& node, const std::string& nodePath );
	};
};

#endif // BE0F3698_B136_43b6_993F_F93035AB500C

