
#include "OpenGUI_String.h"
using namespace OpenGUI;
int main( void ) {

	// UTFString Stability Tests

	// just some lower ascii text
	const char utf8_ascii_text[]     =  "Example ASCII text. All below Unicode value 127, which coincidentally means that it also works as UTF-8 input.";
	const wchar_t utf16_ascii_text[] = L"Example ASCII text. All below Unicode value 127, which coincidentally means that it also works as UTF-8 input.";
	const size_t ascii_text_len = std::string( utf8_ascii_text ).length();

	// these are equivalent to ASCII upper values "ö ä ü ß"
	const char utf8_glyphs[] = {
		( char )0xC3, ( char )0xB6, ' ', ( char )0xC3, ( char )0xA4, ' ', ( char )0xC3, ( char )0xBC, ' ', ( char )0xC3, ( char )0x9F, 0
	};
	const wchar_t utf16_glyphs[] = L"\u00F6 \u00E4 \u00FC \u00DF";
	const size_t glyphs_len = std::wstring( utf16_glyphs ).length();

	// and here are the test victims
	std::string str1, str2;
	std::wstring wstr1, wstr2;
	UTFString ustr1, ustr2;

	//////////////////////////////////////////////////////////////////////////
	// test UTF-16 loading and dumping
	str1 = utf8_ascii_text;
	ustr1 = utf8_ascii_text;
	str2 = ustr1.asUTF8();
	if ( str1 != str2 )
		throw std::exception( "Failed std::string (UTF-8) load/unload 1" );
	str2 = ustr1.asUTF8_c_str();
	if ( str1 != str2 )
		throw std::exception( "Failed std::string (UTF-8) load/unload 2" );
	if ( ustr1.length() != ascii_text_len )
		throw std::exception( "Failed std::string (UTF-8) load/unload 3" );

	str1.clear();
	str2.clear();
	wstr1.clear();
	wstr2.clear();
	ustr1.clear();
	wstr2.clear();

	//////////////////////////////////////////////////////////////////////////
	// test wstring loading and dumping
	wstr1 = utf16_ascii_text;
	ustr1 = utf16_ascii_text;
	wstr2 = ustr1.asWStr();
	if ( wstr1 != wstr2 )
		throw std::exception( "Failed std::wstring (UTF-16/32) load/unload 1" );
	wstr2 = ustr1.asWStr_c_str();
	if ( wstr1 != wstr2 )
		throw std::exception( "Failed std::wstring (UTF-16/32) load/unload 2" );
	if ( ustr1.length() != ascii_text_len )
		throw std::exception( "Failed std::wstring (UTF-16/32) load/unload 3" );

	str1.clear();
	str2.clear();
	wstr1.clear();
	wstr2.clear();
	ustr1.clear();
	wstr2.clear();

	//////////////////////////////////////////////////////////////////////////
	// string shuffle w/ implicit casts
	try {
		wstr1 = utf16_ascii_text;
		wstr1 = L"wstr1: " + wstr1;
		wstr2 = utf16_glyphs;
		wstr2 = L"wstr2: " + wstr2;
		str1 = utf8_ascii_text;
		str1 = "str1: " + str1;
		str2 = utf8_glyphs;
		str2 = "str2: " + str2;
		//
		ustr1 = str1;
		ustr2 = wstr2;
		ustr1.swap( ustr2 );
		str1 = ustr1;
		wstr2 = ustr2;
		//
		ustr1 = wstr1;
		ustr2 = str2;
		ustr1.swap( ustr2 );
		wstr1 = ustr1;
		str2 = ustr2;
	} catch ( std::exception e ) {
		//failed
		throw std::exception(( std::string( "Failed string shuffle w/ implicit casts test: " ) + e.what() ).c_str() );
	}

	str1.clear();
	str2.clear();
	wstr1.clear();
	wstr2.clear();
	ustr1.clear();
	wstr2.clear();

	//////////////////////////////////////////////////////////////////////////
	// forward iterator test (tests const_iterator as well)
	{
		UTFString::iterator iter_ustr1;
		UTFString::const_iterator citer_ustr1;
		std::string::iterator iter_str1;
		std::wstring::iterator iter_wstr1;
		size_t iterCount = 0;
		ustr1 = utf8_ascii_text;
		str1 = utf8_ascii_text;
		wstr1 = utf16_ascii_text;
		iter_ustr1 = ustr1.begin();
		citer_ustr1 = ustr1.begin();
		iter_str1 = str1.begin();
		iter_wstr1 = wstr1.begin();
		// lock step all iterators, testing values along the way
		while ( iter_ustr1 != ustr1.end() ) {
			if ( citer_ustr1 != iter_ustr1 )
				throw std::exception( "Failed forward iterator test: const and regular failed equality check" );

			// character value test
			size_t v0, v1, v2, v3;
			v0 = *citer_ustr1;
			v1 = *iter_ustr1;
			v2 = *iter_str1;
			v3 = *iter_wstr1;
			if ( v0 != v1 || v1 != v2 || v1 != v3 )
				throw std::exception( "Failed forward iterator test: character value mismatch" );

			// iterator distance test
			v0 = citer_ustr1 - ustr1.begin();
			v1 = iter_ustr1 - ustr1.begin();
			v2 = iter_str1 - str1.begin();
			v3 = iter_wstr1 - wstr1.begin();
			if ( v0 != v1 || v1 != v2 || v1 != v3 )
				throw std::exception( "Failed forward iterator test: distance value mismatch" );

			// boolean operator conformance tests
			if (( iter_ustr1 == iter_ustr1 + 1 ) != ( iter_str1 == iter_str1 + 1 ) )
				throw std::exception( "Failed forward iterator test: operator== mismatch" );
			if (( iter_ustr1 != iter_ustr1 + 1 ) != ( iter_str1 != iter_str1 + 1 ) )
				throw std::exception( "Failed forward iterator test: operator!= mismatch" );
			if (( iter_ustr1 < iter_ustr1 + 1 ) != ( iter_str1 < iter_str1 + 1 ) )
				throw std::exception( "Failed forward iterator test: operator< mismatch" );
			if (( iter_ustr1 <= iter_ustr1 + 1 ) != ( iter_str1 <= iter_str1 + 1 ) )
				throw std::exception( "Failed forward iterator test: operator<= mismatch" );
			if (( iter_ustr1 > iter_ustr1 + 1 ) != ( iter_str1 > iter_str1 + 1 ) )
				throw std::exception( "Failed forward iterator test: operator> mismatch" );
			if (( iter_ustr1 >= iter_ustr1 + 1 ) != ( iter_str1 >= iter_str1 + 1 ) )
				throw std::exception( "Failed forward iterator test: operator>= mismatch" );

			++iter_str1;
			++iter_wstr1;
			// alternate our increment styles
			switch ( iterCount % 6 ) {
			case 0:
				iter_ustr1++;
				citer_ustr1++;
				break;
			case 1:
				++iter_ustr1;
				++citer_ustr1;
				break;
			case 2:
				iter_ustr1 = iter_ustr1 + 1;
				citer_ustr1 = citer_ustr1 + 1;
				break;
			case 3:
				iter_ustr1 += 1;
				citer_ustr1 += 1;
				break;
			case 4:
				iter_ustr1 -= -1;
				citer_ustr1 -= -1;
				break;
			case 5:
				iter_ustr1 = iter_ustr1 - -1;
				citer_ustr1 = citer_ustr1 - -1;
				break;
			}
			++iterCount;
		}
		if ( iterCount != ascii_text_len ) // ensure we stepped exactly the correct number, though we should have noticed earlier
			throw std::exception( "Failed forward iterator test: length mismatch" );

		// return trip is the same idea
		while ( iter_ustr1 != ustr1.begin() ) {
			if ( citer_ustr1 != iter_ustr1 )
				throw std::exception( "Failed forward iterator test (return trip): const and regular failed equality check" );

			--iterCount;
			--iter_str1;
			--iter_wstr1;
			// alternate our increment styles
			switch ( iterCount % 6 ) {
			case 0:
				iter_ustr1--;
				citer_ustr1--;
				break;
			case 1:
				--iter_ustr1;
				--citer_ustr1;
				break;
			case 2:
				iter_ustr1 = iter_ustr1 - 1;
				citer_ustr1 = citer_ustr1 - 1;
				break;
			case 3:
				iter_ustr1 -= 1;
				citer_ustr1 -= 1;
				break;
			case 4:
				iter_ustr1 += -1;
				citer_ustr1 += -1;
				break;
			case 5:
				iter_ustr1 = iter_ustr1 + -1;
				citer_ustr1 = citer_ustr1 + -1;
				break;
			}

			// character value test
			size_t v0, v1, v2, v3;
			v0 = *citer_ustr1;
			v1 = *iter_ustr1;
			v2 = *iter_str1;
			v3 = *iter_wstr1;
			if ( v0 != v1 || v1 != v2 || v1 != v3 )
				throw std::exception( "Failed forward iterator test (return trip): character value mismatch" );

			// iterator distance test
			v0 = citer_ustr1 - ustr1.begin();
			v1 = iter_ustr1 - ustr1.begin();
			v2 = iter_str1 - str1.begin();
			v3 = iter_wstr1 - wstr1.begin();
			if ( v0 != v1 || v1 != v2 || v1 != v3 )
				throw std::exception( "Failed forward iterator test (return trip): distance value mismatch" );
		}
		if ( iterCount != 0 ) // we should land on index 0 when we stop. again, should have noticed earlier
			throw std::exception( "Failed forward iterator test: missed 0 crossing on return trip" );
	}

	//////////////////////////////////////////////////////////////////////////
	// reverse iterator test
	{
		UTFString::reverse_iterator iter_ustr1;
		UTFString::const_reverse_iterator citer_ustr1;
		std::string::reverse_iterator iter_str1;
		std::wstring::reverse_iterator iter_wstr1;
		size_t iterCount = 0;
		ustr1 = utf8_ascii_text;
		str1 = utf8_ascii_text;
		wstr1 = utf16_ascii_text;
		iter_ustr1 = ustr1.rbegin();
		citer_ustr1 = ustr1.rbegin();
		iter_str1 = str1.rbegin();
		iter_wstr1 = wstr1.rbegin();
		// lock step all iterators, testing values along the way
		while ( iter_ustr1 != ustr1.rend() ) {
			if ( citer_ustr1 != iter_ustr1 )
				throw std::exception( "Failed reverse iterator test: const and regular failed equality check" );

			// character value test
			size_t v0, v1, v2, v3;
			v0 = *citer_ustr1;
			v1 = *iter_ustr1;
			v2 = *iter_str1;
			v3 = *iter_wstr1;
			if ( v0 != v1 || v1 != v2 || v1 != v3 )
				throw std::exception( "Failed reverse iterator test: character value mismatch" );

			// iterator distance test
			v0 = citer_ustr1 - ustr1.rbegin();
			v1 = iter_ustr1 - ustr1.rbegin();
			v2 = iter_str1 - str1.rbegin();
			v3 = iter_wstr1 - wstr1.rbegin();
			if ( v0 != v1 || v1 != v2 || v1 != v3 )
				throw std::exception( "Failed reverse iterator test: distance value mismatch" );

			// boolean operator conformance tests
			if (( iter_ustr1 == iter_ustr1 + 1 ) != ( iter_str1 == iter_str1 + 1 ) )
				throw std::exception( "Failed reverse iterator test: operator== mismatch" );
			if (( iter_ustr1 != iter_ustr1 + 1 ) != ( iter_str1 != iter_str1 + 1 ) )
				throw std::exception( "Failed reverse iterator test: operator!= mismatch" );
			if (( iter_ustr1 < iter_ustr1 + 1 ) != ( iter_str1 < iter_str1 + 1 ) )
				throw std::exception( "Failed reverse iterator test: operator< mismatch" );
			if (( iter_ustr1 <= iter_ustr1 + 1 ) != ( iter_str1 <= iter_str1 + 1 ) )
				throw std::exception( "Failed reverse iterator test: operator<= mismatch" );
			if (( iter_ustr1 > iter_ustr1 + 1 ) != ( iter_str1 > iter_str1 + 1 ) )
				throw std::exception( "Failed reverse iterator test: operator> mismatch" );
			if (( iter_ustr1 >= iter_ustr1 + 1 ) != ( iter_str1 >= iter_str1 + 1 ) )
				throw std::exception( "Failed reverse iterator test: operator>= mismatch" );

			++iter_str1;
			++iter_wstr1;
			// alternate our increment styles
			switch ( iterCount % 6 ) {
			case 0:
				iter_ustr1++;
				citer_ustr1++;
				break;
			case 1:
				++iter_ustr1;
				++citer_ustr1;
				break;
			case 2:
				iter_ustr1 = iter_ustr1 + 1;
				citer_ustr1 = citer_ustr1 + 1;
				break;
			case 3:
				iter_ustr1 += 1;
				citer_ustr1 += 1;
				break;
			case 4:
				iter_ustr1 -= -1;
				citer_ustr1 -= -1;
				break;
			case 5:
				iter_ustr1 = iter_ustr1 - -1;
				citer_ustr1 = citer_ustr1 - -1;
				break;
			}
			++iterCount;
		}
		if ( iterCount != ascii_text_len ) // ensure we stepped exactly the correct number, though we should have noticed earlier
			throw std::exception( "Failed reverse iterator test: length mismatch" );

		// return trip is the same idea
		while ( iter_ustr1 != ustr1.rbegin() ) {
			if ( citer_ustr1 != iter_ustr1 )
				throw std::exception( "Failed reverse iterator test (return trip): const and regular failed equality check" );

			--iterCount;
			--iter_str1;
			--iter_wstr1;
			// alternate our increment styles
			switch ( iterCount % 6 ) {
			case 0:
				iter_ustr1--;
				citer_ustr1--;
				break;
			case 1:
				--iter_ustr1;
				--citer_ustr1;
				break;
			case 2:
				iter_ustr1 = iter_ustr1 - 1;
				citer_ustr1 = citer_ustr1 - 1;
				break;
			case 3:
				iter_ustr1 -= 1;
				citer_ustr1 -= 1;
				break;
			case 4:
				iter_ustr1 += -1;
				citer_ustr1 += -1;
				break;
			case 5:
				iter_ustr1 = iter_ustr1 + -1;
				citer_ustr1 = citer_ustr1 + -1;
				break;
			}

			// character value test
			size_t v0, v1, v2, v3;
			v0 = *citer_ustr1;
			v1 = *iter_ustr1;
			v2 = *iter_str1;
			v3 = *iter_wstr1;
			if ( v0 != v1 || v1 != v2 || v1 != v3 )
				throw std::exception( "Failed reverse iterator test (return trip): character value mismatch" );

			// iterator distance test
			v0 = citer_ustr1 - ustr1.rbegin();
			v1 = iter_ustr1 - ustr1.rbegin();
			v2 = iter_str1 - str1.rbegin();
			v3 = iter_wstr1 - wstr1.rbegin();
			if ( v0 != v1 || v1 != v2 || v1 != v3 )
				throw std::exception( "Failed reverse iterator test (return trip): distance value mismatch" );
		}
		if ( iterCount != 0 ) // we should land on index 0 when we stop. again, should have noticed earlier
			throw std::exception( "Failed reverse iterator test: missed 0 crossing on return trip" );
	}

	//////////////////////////////////////////////////////////////////////////
	// Unicode character iteration test
	{
		ustr1.clear();
		ustr1.push_back( 0x20500 ); // push 5 glyphs from the extended Chinese set
		ustr1.push_back( 0x20510 ); // (I hope this doens't translate into anything vulgar)
		ustr1.push_back( 0x20520 );
		ustr1.push_back( 0x20530 );
		ustr1.push_back( 0x20540 ); // ustr1 is now 10 code points long
		ustr2 = "12345"; // a 5 character ASCII string
		ustr1.append( ustr2 ); // ustr1 is now 10 characters long (15 code points)
		ustr1 = ustr1 + ustr1; // ustr1 is now 20 characters, 30 code points
		size_t iterCount = 0;
		UTFString::iterator iter_ustr1 = ustr1.begin();
		UTFString::const_iterator citer_ustr1 = iter_ustr1;
		// walk forward per character
		while ( iter_ustr1 != ustr1.end() ) {
			if ( citer_ustr1 != iter_ustr1 )
				throw std::exception( "Failed Unicode character iteration test: const/normal iterators not equal" );

			if ( citer_ustr1.getCharacter() != iter_ustr1.getCharacter() )
				throw std::exception( "Failed Unicode character iteration test: const/normal iterator character values not equal" );

			iterCount++;
			iter_ustr1.moveNext();
			citer_ustr1.moveNext();
		}
		if ( iterCount != 20 )
			throw std::exception( "Failed Unicode character iteration test: length mismatch" );
		// walk backwards per character
		while ( iter_ustr1 != ustr1.begin() ) {
			if ( citer_ustr1 != iter_ustr1 )
				throw std::exception( "Failed Unicode character iteration test: const/normal iterators not equal" );
			if ( citer_ustr1.getCharacter() != iter_ustr1.getCharacter() )
				throw std::exception( "Failed Unicode character iteration test: const/normal iterator character values not equal" );
			iterCount--;
			iter_ustr1.movePrev();
			citer_ustr1.movePrev();
		}
		if ( iterCount != 0 )
			throw std::exception( "Failed Unicode character iteration test: missed 0 crossing on return trip" );
	}


	// everything passed
	return 0;
}
