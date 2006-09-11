#ifndef BE0F3698_B136_43b6_993F_F93035AB500C
#define BE0F3698_B136_43b6_993F_F93035AB500C

namespace OpenGUI {
	//! Provides complete loading of xml files containing data for all different subsystems.
	/*! This class provides complete parsing of XML files. It will delegate top level tags
		to the necessary subsystem as it sees them, so you can load data into several
		subsystems with a single function call.

		It also supports use of the '\<include file="somefile.xml"\>' tag, which allows
		you to split your XML files into smaller and more specific pieces, while allowing
		them to automatically load their dependants.

		All tags are immediately evaluated in the order they are read, so watch your
		dependancies. This also means that include files are evaluated at the time they
		are discovered. If you need your includes to happen first, put them at the top of the
		XML file. For any single execution of this function, an include file will only be
		evaluated the first time it is requested. Subsequent requests for an include file are
		logged as warnings, but otherwise ignored. <i>(The multiple include testing is performed
		using a simple case-insensitive string comparison. Minor path tricks will fool it, but
		are generally discouraged.)</i>

		\see \ref XMLDOC "The XML Documentation" for a complete reference to using XML with %OpenGUI.
	*/
	class OPENGUI_API XMLParser {
	public:
		//! Reads the given XML file from the registered resource manager and parses the file according to the \ref XMLDOC "XML specifications"
		static void LoadFromFile( const std::string& xmlFilename );
	private:
		typedef std::set<std::string> IncludeSet;
		static void ParseXMLFile( const std::string& xmlFilename, IncludeSet& includesToIgnore, unsigned int depth );
	};
};

#endif

