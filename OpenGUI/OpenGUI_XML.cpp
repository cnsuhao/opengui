#include "tinyxml.h"
#include "OpenGUI_XML.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_Resource.h"
#include "OpenGUI_ResourceProvider.h"
#include "OpenGUI_System.h"
namespace OpenGUI {
	//############################################################################
	void XMLDoc::clear() {
		while ( mChildren.size() > 0 ) {
			delete mChildren.front();
		}
	}
	//############################################################################
	void XMLDoc::loadFile( const std::string& filename ) {
		TiXmlDocument doc;
		Resource_CStr res;
		ResourceProvider* resProvider = System::getSingleton()._getResourceProvider();
		resProvider->loadResource( filename, res );
		doc.Parse( res.getString() );
		TiXmlElement* root = doc.RootElement();
		if ( root ) {
			do {
				XMLNode* node = new XMLNode( root, this );
			} while (( root = root->NextSiblingElement() ) );
		}
	}
	//############################################################################
	void XMLDoc::saveFile( const std::string& filename ) {
		TiXmlDocument doc;
		TiXmlDeclaration decl( "1.0", "", "" );
		doc.InsertEndChild( decl );
		for ( XMLNodeList::iterator iter = mChildren.begin(); iter != mChildren.end(); iter++ ) {
			XMLNode* node = ( *iter );
			void* out = node->_totxml();
			TiXmlElement* element = ( TiXmlElement* )out;
			doc.LinkEndChild( element );
		}
		doc.SaveFile( filename );
	}
	//############################################################################
	//############################################################################
	//############################################################################
	XMLNodeContainer::~XMLNodeContainer() {
		while ( mChildren.size() > 0 ) {
			delete mChildren.front();
		}
	}
	//############################################################################
	XMLNodeList XMLNodeContainer::getChildren()const {
		return mChildren;
	}
	//############################################################################
	XMLNodeList XMLNodeContainer::getChildren( const std::string& tagName )const {
		XMLNodeList ret;
		for ( XMLNodeList::const_iterator iter = mChildren.begin(); iter != mChildren.end(); iter++ ) {
			XMLNode* child = ( *iter );
			if ( tagName == child->getTagName() ) {
				ret.push_back( child );
			}
		}
		return ret;
	}
	//############################################################################
	void XMLNodeContainer::_doNotifyChildDetach( XMLNode* childPtr ) {
		mChildren.remove( childPtr );
	}
	//############################################################################
	void XMLNodeContainer::_doNotifyChildAttach( XMLNode* childPtr ) {
		mChildren.push_back( childPtr );
	}
	//############################################################################
	void XMLNodeContainer::_notifyChildDetach( XMLNodeContainer* parent, XMLNode* childPtr ) {
		parent->_doNotifyChildDetach( childPtr );
	}
	//############################################################################
	void XMLNodeContainer::_notifyChildAttach( XMLNodeContainer* parent, XMLNode* childPtr ) {
		parent->_doNotifyChildAttach( childPtr );
	}
	//############################################################################
	//############################################################################
	//############################################################################
	XMLNode::XMLNode( const std::string& tagName, XMLNodeContainer* parentPtr )
			: mTagName( tagName ), mParent( parentPtr ) {
		if ( mParent )
			_notifyChildAttach( mParent, this );
	}
	//############################################################################
	XMLNode::~XMLNode() {
		if ( mParent )
			_notifyChildDetach( mParent, this );
	}
	//############################################################################
	XMLNodeContainer* XMLNode::getParent()const {
		return mParent;
	}
	//############################################################################
	void XMLNode::setParent( XMLNodeContainer* newParentPtr ) {
		if ( mParent )
			_notifyChildDetach( mParent, this );
		mParent = newParentPtr;
		if ( mParent )
			_notifyChildAttach( mParent, this );
	}
	//############################################################################
	const std::string& XMLNode::getAttribute( const std::string& name ) const {
		XMLAttributeMap::const_iterator iter = mAttributes.find( name );
		if ( iter == mAttributes.end() )
			OG_THROW( Exception::ERR_ITEM_NOT_FOUND,
					  "Attribute not found:" + getTagName() + " - " + name,
					  __FUNCTION__ );
		return iter->second;
	}
	//############################################################################
	XMLAttributeMap XMLNode::getAttributes() const {
		XMLAttributeMap attribs = mAttributes;
		return attribs;
	}
	//############################################################################
	void XMLNode::setAttribute( const std::string& name, const std::string& value ) {
		mAttributes[name] = value;
	}
	//############################################################################
	void XMLNode::removeAttribute( const std::string& name ) {
		mAttributes.erase( name );
	}
	//############################################################################
	const std::string& XMLNode::getText() const {
		return mText;
	}
	//############################################################################
	void XMLNode::setText( const std::string& text ) {
		mText = text;
	}
	//############################################################################
	XMLNode::XMLNode( void* txmle, XMLNodeContainer* parentPtr ): mParent( parentPtr ) {
		TiXmlElement* mytxml = ( TiXmlElement* ) txmle;
		mTagName = mytxml->Value();
		if ( mParent )
			_notifyChildAttach( mParent, this );
		TiXmlAttribute* attrib = mytxml->FirstAttribute();
		if ( attrib ) {
			do {
				setAttribute( attrib->Name(), attrib->Value() );
			} while (( attrib = attrib->Next() ) );
		}
		const TiXmlNode* child_node = mytxml->FirstChild();
		if ( child_node ) {
			bool hasText = false;
			do {
				const TiXmlElement* child_element = child_node->ToElement();
				if ( child_element ) {
					if ( child_element->Value() == "TEXT" && !hasText ) {
						hasText = true;
						setText( child_element->GetText() );
					} else {
						void* c = ( void* ) child_element;
						new XMLNode( c, this );
					}
				}
			} while ( child_node = mytxml->IterateChildren( child_node ) );
		}
	}
	//############################################################################
	void* XMLNode::_totxml() {
		TiXmlElement* mytxml = new TiXmlElement( getTagName() );
		XMLAttributeMap::iterator iter = mAttributes.begin();
		while ( iter != mAttributes.end() ) {
			const std::string& aName = iter->first;
			const std::string& aValue = iter->second;
			mytxml->SetAttribute( aName, aValue );
			iter++;
		}
		if ( getText() != "" ) {
			TiXmlElement* texttxml = new TiXmlElement( "TEXT" );
			TiXmlText* thetext = new TiXmlText( getText() );
			texttxml->LinkEndChild( thetext );
			mytxml->LinkEndChild( texttxml );
		}

		XMLNodeList::iterator child_iter = mChildren.begin();
		while ( child_iter != mChildren.end() ) {
			XMLNode* child = ( *child_iter );
			TiXmlElement* childtxml = ( TiXmlElement* )child->_totxml();
			mytxml->LinkEndChild( childtxml );
			child_iter++;
		}
		return ( void* )mytxml;
	}
	//############################################################################
	/*! For example, if the tag were \c thisTag in the following code:
	\code
	<level1>
	<level2>
		<thisTag />
	</level2>
	</level1>
	\endcode
	Then the returned path would be "/level1/level2/".
	The path is always comprised of a leading "/", following by \c tagName + "/" for each proceeding
	node before the current node.
	*/
	std::string XMLNode::getPath() const {
		std::string path = "/";
		XMLNode* parentNode = dynamic_cast<XMLNode*>( mParent );
		if ( parentNode ) {
			parentNode->_buildPath( path );
		}
		return path;
	}
	//############################################################################
	void XMLNode::_buildPath( std::string& path ) {
		XMLNode* parentNode = dynamic_cast<XMLNode*>( mParent );
		if ( parentNode ) {
			parentNode->_buildPath( path );
		}
		path = path + mTagName + "/";
	}
}//namespace OpenGUI{
