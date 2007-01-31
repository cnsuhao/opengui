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
		if ( native->getType() == OpenGUI::XMLNodeContainer::NT_XMLDOC ) {
			return gcnew XMLDoc( static_cast<OpenGUI::XMLDoc*>( native ) );
		} else if ( native->getType() == OpenGUI::XMLNodeContainer::NT_XMLNODE ) {
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

} // namespace OpenGUI_Net {

