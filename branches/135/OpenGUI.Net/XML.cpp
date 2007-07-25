// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "Stdafx.h"
#include "XML.h"

using namespace System;

namespace OpenGUI_Net {

	//############################################################################
	XMLNodeList ^ XMLNodeContainer::getChildren() {
		OpenGUI::XMLNodeList nodelist = mNative->getChildren();
		return makeXMLNodeList( nodelist );
	}
	//############################################################################
	XMLNodeList ^ XMLNodeContainer::getChildren( const String ^ tagName ) {
		OpenGUI::String str = Marshal::STRING( tagName );
		OpenGUI::XMLNodeList nodelist = mNative->getChildren( str );
		return makeXMLNodeList( nodelist );
	}
	//############################################################################
	XMLNodeContainer ^ XMLNodeContainer::makeManaged( OpenGUI::XMLNodeContainer* native ) {
		if ( native->getType() == OpenGUI::XMLNodeContainer::T_XMLDOC ) {
			return gcnew XMLDoc( static_cast<OpenGUI::XMLDoc*>( native ) );
		} else if ( native->getType() == OpenGUI::XMLNodeContainer::T_XMLNODE ) {
			return gcnew XMLNode( static_cast<OpenGUI::XMLNode*>( native ) );
		}
		throw gcnew ::System::Exception( "Unknown XMLNodeContainer type" );
	}
	//############################################################################
	XMLNodeList ^ XMLNodeContainer::makeXMLNodeList( const OpenGUI::XMLNodeList& l ) {
		XMLNodeList ^ retval = gcnew XMLNodeList;
		OpenGUI::XMLNodeList::const_iterator i, ie = l.end();
		for ( i = l.begin(); i != ie; ++i ) {
			XMLNodeContainer ^ cont = makeManaged(( *i ) );
			XMLNode ^ node = dynamic_cast < XMLNode ^ >( cont );
			if ( node != nullptr )
				retval->Add( node );
		}
		return retval;
	}
	//############################################################################
	//############################################################################
	//############################################################################
	void XMLDoc::clear() {
		THRU_THROW_BEGIN
		static_cast<OpenGUI::XMLDoc*>( mNative )->clear();
		THRU_THROW_END
	}
	//############################################################################
	void XMLDoc::loadFile( const String ^ filename ) {
		OpenGUI::String str = Marshal::STRING( filename );
		THRU_THROW_BEGIN
		static_cast<OpenGUI::XMLDoc*>( mNative )->loadFile( str );
		THRU_THROW_END
	}
	//############################################################################
	void XMLDoc::saveFile( const String ^ filename ) {
		OpenGUI::String str = Marshal::STRING( filename );
		THRU_THROW_BEGIN
		static_cast<OpenGUI::XMLDoc*>( mNative )->saveFile( str );
		THRU_THROW_END
	}
	//############################################################################
	String ^ XMLDoc::getFileName() {
		OpenGUI::String str;
		THRU_THROW_BEGIN
		str = static_cast<OpenGUI::XMLDoc*>( mNative )->getFileName();
		THRU_THROW_END
		String ^ name = Marshal::STRING( str );
		return name;
	}
	//############################################################################

} // namespace OpenGUI_Net {

