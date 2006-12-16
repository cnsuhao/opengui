// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "ft2build.h"
#include FT_FREETYPE_H

#include "OpenGUI_Font.h"

#include "OpenGUI_LogSystem.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_FontManager.h"
#include "OpenGUI_FontSet.h"


namespace OpenGUI {
	//############################################################################
	/*! This will attempt to bind, but will fall back to delayed binding if the
	bind fails. */
	Font::Font( const std::string& fontName, float fontSize ) {
		m_Bound = false;
		m_FontName = fontName;
		m_FontSize = fontSize;
		_tryBind();
	}
	//############################################################################
	/*! This will force an immediate binding to the given FontSet at the given size.
	If the given \c fontSet is an empty pointer, the default font will be used. */
	Font::Font( FontSetPtr fontSet, float fontSize ) {
		m_Bound = false;
		m_FontSize = fontSize;
		m_FontSetPtr = fontSet;
		bind();
	}
	//############################################################################
	/*! This constructor forces delayed binding to the default Font */
	Font::Font() {
		m_Bound = false;
	}
	//############################################################################
	/*! If the Font is already bound, this function will exit immediately with no ill effect. */
	void Font::bind() {
		if ( isBound() )
			return;
		if ( !_tryBind() )
			OG_THROW( Exception::ERR_INTERNAL_ERROR, "Failed to bind Font", __FUNCTION__ );
	}
	//############################################################################
	bool Font::_tryBind() {
		// try to bind to the FontSet by name
		if ( m_FontSetPtr.isNull() && m_FontName != "" ) {
			FontSetPtr fset = FontManager::getSingleton().GetFontSet( m_FontName );
			if ( fset.isNull() )
				return false;
			m_FontSetPtr = fset;
			m_FontName = m_FontSetPtr->getName();
		}

		// try to bind to the default FontSet
		if ( m_FontSetPtr.isNull() && m_FontName == "" ) {
			Font fnt = FontManager::getSingleton().GetDefaultFont();
			if ( !fnt.isBound() )
				return false;
			FontSetPtr fset = fnt.getFontSetPtr();
			if ( fset.isNull() )
				return false;
			m_FontSetPtr = fset;
			m_FontName = m_FontSetPtr->getName();
		}

		//if we already have a valid FontSet, then just copy the name
		if (( !m_FontSetPtr.isNull() ) && m_FontName == "" )
			m_FontName = m_FontSetPtr->getName();

		// if size is 0.0f or less and we have a valid FontSet binding, copy the default Font size
		if (( !m_FontSetPtr.isNull() ) && m_FontSize <= 0.0f ) {
			Font dFont = FontManager::getSingleton().GetDefaultFont();
			if ( !dFont.isBound() )
				return false;
			m_FontSize = dFont.m_FontSize;
		}

		//this should never happen, but we'll test anyhow
		if ( m_FontSetPtr.isNull() || m_FontSize <= 0.0f )
			return false;

		m_Bound = true;
		return true;
	}
	//############################################################################
	/*! Equality for Font handles comes in two stages. If both of the handles are
	bound, then they are only equal if the two Fonts are bound to the same FontSet
	at the same size. If either of the Fonts is not bound, then copies of the
	compared Fonts are created, and a bind on the copies is attempted. The result
	is then determined by comparison of the fully bound copies. If one of the Fonts
	binds while the other fails, they are obviously not equal and are returned as such.

	In extreme cases, where both of the Fonts cannot be bound, they are compared by
	their stored FontSet name and point size.
	*/
	bool Font::operator ==( const Font& right ) {
		if ( isBound() && right.isBound() ) {
			return ( m_FontSetPtr == right.m_FontSetPtr ) && ( m_FontSize == right.m_FontSize );
		} else {
			bool freeLeft = false;
			bool freeRight = false;
			Font* leftPtr = this;
			Font* rightPtr = const_cast<Font*>( &right );
			// get a bound leftPtr if we can
			if ( !isBound() ) {
				leftPtr = new Font( m_FontName, m_FontSize );
				if ( leftPtr->_tryBind() ) {
					freeLeft = true;
				} else {
					delete leftPtr;
					leftPtr = this;
					freeLeft = false;
				}
			}

			//get a bound rightPtr if we can
			if ( !right.isBound() ) {
				rightPtr = new Font( right.m_FontName, right.m_FontSize );
				if ( rightPtr->_tryBind() ) {
					freeRight = true;
				} else {
					delete rightPtr;
					rightPtr = const_cast<Font*>( &right );
					freeRight = false;
				}
			}

			// now we can do some evaluations to determine equality
			bool retval;
			if ( leftPtr->isBound() != rightPtr->isBound() ) {
				// if one bound and the other didn't, they can't possibly be equal
				retval = false;
			} else if ( leftPtr->isBound() ) { // they're equal, so we can test just one
				// both are bound, so we can just test pointers
				retval = ( leftPtr->m_FontSetPtr == rightPtr->m_FontSetPtr ) && ( leftPtr->m_FontSize == rightPtr->m_FontSize );
			} else {
				// fall back if neither bound
				retval = ( leftPtr->m_FontName == rightPtr->m_FontName ) && ( leftPtr->m_FontSize == rightPtr->m_FontSize );
			}

			//once we have our result, we need to do some cleanup
			if ( freeRight ) delete rightPtr;
			if ( freeLeft ) delete leftPtr;

			// and finally return the fruits of our labor
			return retval;
		}
	}
	//############################################################################
};
