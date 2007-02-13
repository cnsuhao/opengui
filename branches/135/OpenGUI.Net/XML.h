// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef XML_h__
#define XML_h__

using namespace System;
using namespace System::Collections::Generic;

namespace OpenGUI_Net {

	ref class XMLDoc;
	ref class XMLNode;
	typedef List < XMLNode ^ > XMLNodeList;
	typedef Dictionary<String^,String^> XMLAttributeMap;

	public ref class XMLNodeContainer {
	public:
		XMLNodeContainer() {}
		~XMLNodeContainer() {}
		//! Returns a complete copy of the list of children
		XMLNodeList ^ getChildren();
		//! Returns a list of the children that match the given \c tagName
		XMLNodeList ^ getChildren( const String ^ tagName );

		static bool operator==( XMLNodeContainer ^ left, XMLNodeContainer ^ right ) {
			return left->mNative == right->mNative;
		}

	protected:
		OpenGUI::XMLNodeContainer* mNative;

		static XMLNodeList ^ makeXMLNodeList( const OpenGUI::XMLNodeList& l );
		static XMLNodeContainer ^ makeManaged( OpenGUI::XMLNodeContainer* native );
	};

	public ref class XMLDoc: public XMLNodeContainer {
	public:
		XMLDoc( OpenGUI::XMLDoc* nativeDoc ) {
			mNative = nativeDoc;
		}
		XMLDoc() {}
		~XMLDoc() {}
		//! clears the contents of this XMLDoc
		void clear();
		//! loads an existing XML file into this XMLDoc using the registered resource manager
		void loadFile( const String ^ filename );
		//! saves this XMLDoc to a file, bypassing the resource manager (writes directly to disk)
		void saveFile( const String ^ filename );
		//! returns the last filename this XMLDoc was saved to or loaded from
		String ^ getFileName();
	};

	public ref class XMLNode: public XMLNodeContainer {
	public:
		XMLNode( OpenGUI::XMLNode* nativeNode ) {
			mNative = nativeNode;
		}
		//! constructor requires the tag name and optional pointer to parent
		XMLNode( const String ^ tagName, XMLNodeContainer ^ parentPtr );
		//XMLNode( const String^ tagName, XMLNodeContainer* parentPtr = 0 );
		//! destructor automatically performs safe cleanup
		~XMLNode() {}
		//! Returns the containing XMLDoc of this node
		XMLDoc ^ getDoc();
		//! returns the parent of this node
		XMLNodeContainer ^ getParent();
		//! changes the parent of this node
		//void setParent( XMLNodeContainer* newParentPtr );
		//! retrieves the tag name of this node
		String ^ getTagName();

		//! Returns the XML DOM path leading up to this node. Ex: /path/to/
		String ^ getPath();

		//! returns the value of a single attribute
		String ^ getAttribute( const String ^ name );
		//! sets the value of an attribute, creating it if it does not already exist
		void setAttribute( const String ^ name, const String ^ value );
		//! removes the given attribute
		void removeAttribute( const String ^ name );
		//! Returns \c true if the given attribute exists, \c false otherwise
		bool hasAttribute( const String ^ name );
		//! returns a copy of all attributes
		//XMLAttributeMap getAttributes() const;

		//! return the content of this node's text
		String ^ getText();
		//! set the text content of this node
		void setText( const String ^ text );

		//! Dumps the full contents of this node into a human readable format that is XML-like, but not real XML
		String ^ dump();
	};
} // namespace OpenGUI_Net {

#endif

