// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_GenericResourceProvider.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//#####################################################################
	void GenericResourceProvider::loadResource( const String& filename, Resource& output ) {
		if ( filename.empty() || filename == "" ) {
			OG_THROW( Exception::ERR_INVALIDPARAMS, "No filename provided", "GenericResourceProvider::loadResource" );
		}
		std::ifstream inputFile( filename.c_str(), std::ios::binary | std::ios::ate );

		if ( inputFile.fail() ) {
			OG_THROW( Exception::ERR_FILE_NOT_FOUND, "File not found: '" + filename + "'", "GenericResourceProvider::loadResource" );
		}
		std::streampos size = inputFile.tellg();
		inputFile.seekg( 0, std::ios::beg );

		unsigned char* buffer = new unsigned char[size];

		try {
			inputFile.read(( char* )buffer, size );
		} catch ( std::ifstream::failure ex ) {
			delete[] buffer;
			OG_THROW( Exception::ERR_FILE_NOT_READABLE, "Error reading file: '" + filename + "'", "GenericResourceProvider::loadResource" );
		}
		inputFile.close();
		output.setData( buffer, size );
	}
	//#####################################################################
	void GenericResourceProvider::unloadResource( Resource& resource ) {
		/*
			Not that we have to do this, since Resource can take care of itself,
			but we might as well pretend to be good neighbors
		*/
		resource.release();
	}
	//#####################################################################
}
;//namespace OpenGUI{

