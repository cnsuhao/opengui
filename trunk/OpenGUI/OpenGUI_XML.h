// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef B9F64992_A5F1_41c5_B545_1F73262BF02B
#define B9F64992_A5F1_41c5_B545_1F73262BF02B

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_String.h"
#include "OpenGUI_Types.h"

namespace OpenGUI {
	class XMLParser; //forward declaration
	class XMLNode; //forward declaration

	//! List of XMLNode pointers
	typedef std::list<XMLNode*> XMLNodeList;
	//! Map of attributes
	typedef std::map<std::string, std::string> XMLAttributeMap;

	//! Interface class for classes that contain XMLNode children.
	/*! The memory attached to all children is considered property of this container,
	and is deleted during container destruction. */
	class OPENGUI_API XMLNodeContainer {
	public:
		XMLNodeContainer() {}
		virtual ~XMLNodeContainer();
		//! Returns a complete copy of the list of children
		XMLNodeList getChildren() const;
		//! Returns a list of the children that match the given \c tagName
		XMLNodeList getChildren( const String& tagName ) const;

	protected:
		void _notifyChildDetach( XMLNodeContainer* parent, XMLNode* childPtr ); // issues event
		void _notifyChildAttach( XMLNodeContainer* parent, XMLNode* childPtr ); // issues event
		void _doNotifyChildDetach( XMLNode* childPtr ); // handles event
		void _doNotifyChildAttach( XMLNode* childPtr ); // handles event
		XMLNodeList mChildren; // add/remove is handled entirely by the _notifyX functions. Calling them is responsibility of child
	};

	//! Root level container for XML documents
	class OPENGUI_API XMLDoc: public XMLNodeContainer {
		friend class XMLParser; // XMLParser can reach the protected functions
	public:
		XMLDoc() {}
		virtual ~XMLDoc() {}
		//! clears the contents of this XMLDoc
		void clear();
		//! loads an existing XML file into this XMLDoc using the registered resource manager
		void loadFile( const String& filename );
		//! saves this XMLDoc to a file, bypassing the resource manager (writes directly to disk)
		void saveFile( const String& filename );
		//! returns the last filename this XMLDoc was saved to or loaded from
		const String& getFileName() {
			return mFileName;
		}
	protected:
		String mFileName;
	};

	//! Represents an XML tag
	/*! XMLNode is used to represent a single node in an XML tree. Each node is
	capable of having a single parent node, multiple children nodes, multiple
	attributes, and a contained text string.

	Functions are provided for various operations, such as iterating across all
	children, all children of a particular tag name, and reading attributes and child
	node trees into specific %OpenGUI types.

	This class does also goes out of its way to ensure proper deallocation of memory,
	upon its own destruction it will deallocate child nodes, and notify its parent
	(if it has one) of its destruction so that it can be removed from the parent's list
	of child nodes.

	\note
	You'll notice that this class returns copies of lists and maps under certain conditions.
	While this does impose a speed penalty, XML configuration files aren't meant to be read
	within time critical areas of your application, so it really isn't an issue. On top of
	that, the lists returned tend to be fairly small.

	\attention
	%OpenGUI uses XML in a unique way. Specifically, %OpenGUI does not support inner text for
	nodes in the standard XML fashion. All text strings that are placed in the "text" region
	are placed within a special \c &lt;TEXT&gt; child node. These nodes do not have any parsed
	attributes, and only the first found \c &lt;TEXT&gt; node is ever read by the parent.

	*/
	class OPENGUI_API XMLNode: public XMLNodeContainer {
		friend class XMLParser; // XMLParser can reach the protected functions
		friend class XMLDoc;
	public:
		//! constructor requires the tag name and optional pointer to parent
		XMLNode( const String& tagName, XMLNodeContainer* parentPtr = 0 );
		//! destructor automatically performs safe cleanup
		virtual ~XMLNode();
		//! Returns the containing XMLDoc of this node
		XMLDoc* getDoc() const;
		//! returns the parent of this node
		XMLNodeContainer* getParent() const;
		//! changes the parent of this node
		void setParent( XMLNodeContainer* newParentPtr );
		//! retrieves the tag name of this node
		const String& getTagName() const {
			return mTagName;
		}

		//! Returns the XML DOM path leading up to this node. Ex: /path/to/
		String getPath() const;

		//! returns the value of a single attribute
		const String& getAttribute( const String& name ) const;
		//! sets the value of an attribute, creating it if it does not already exist
		void setAttribute( const String& name, const String& value );
		//! removes the given attribute
		void removeAttribute( const String& name );
		//! Returns \c true if the given attribute exists, \c false otherwise
		bool hasAttribute( const String& name ) const;
		//! returns a copy of all attributes
		XMLAttributeMap getAttributes() const;

		//! return the content of this node's text
		const String& getText() const;
		//! set the text content of this node
		void setText( const String& text );

		//! Dumps the full contents of this node into a human readable format that is XML-like, but not real xml
		String dump() const;

	protected:
		//! \internal build the given tinyXML tree into a node tree
		XMLNode( void* txmle, XMLNodeContainer* parentPtr );
		//! \internal writes the contents of this node tree into a tinyXML tree
		void* _totxml();
		void _buildPath( String& path );

	private:
		String mTagName;
		String mText;
		XMLAttributeMap mAttributes;
		XMLNodeContainer* mParent;

	};
} // namespace OpenGUI{

#endif // B9F64992_A5F1_41c5_B545_1F73262BF02B
