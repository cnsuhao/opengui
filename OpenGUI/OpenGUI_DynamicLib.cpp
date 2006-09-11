
#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_LogSystem.h"
#include "OpenGUI_Exception.h"
#include "OpenGUI_DynamicLib.h"

#include "OpenGUI_CONFIG.h"

#define NEVER 0
#define ALWAYS 1
#define AS_NEEDED 2
#if(DYNAMICLIB_FILENAME_MANGLING == 1)
#define MANGLE_FIX_EXT ALWAYS
#define MANGLE_ADD_D ALWAYS

#elif(DYNAMICLIB_FILENAME_MANGLING == 2)
#define MANGLE_FIX_EXT AS_NEEDED
#define MANGLE_ADD_D AS_NEEDED

#elif(DYNAMICLIB_FILENAME_MANGLING == 3)
#define MANGLE_FIX_EXT AS_NEEDED
#define MANGLE_ADD_D ALWAYS

#else //DYNAMICLIB_FILENAME_MANGLING == 0 || DYNAMICLIB_FILENAME_MANGLING undefined
#define MANGLE_FIX_EXT NEVER
#define MANGLE_ADD_D NEVER
#endif

#if OPENGUI_PLATFORM == OPENGUI_PLATFORM_WIN32
#define DYNLIB_EXT "dll"
#elif OPENGUI_PLATFORM == OPENGUI_PLATFORM_LINUX
#define DYNLIB_EXT "so"
#endif

namespace OpenGUI {
	//############################################################################
	//! \internal splits a given full path into separate path and filename components.
	/*! Always succeeds, even if the path portion is blank. Tests for / only  */
	void _splitFileFromPath( const std::string& fullPath, std::string& pathHalf, std::string& fileHalf ) {
		size_t pathSize;
		pathSize = fullPath.rfind( "/" );
		if ( pathSize == std::string::npos ) {
			pathHalf = "";
			fileHalf = fullPath;
		} else {
			pathHalf = fullPath.substr( 0, pathSize + 1 );
			fileHalf = fullPath.substr( pathSize + 1 );
		}
	}
	//############################################################################
	//! \internal extracts the extension from a filename/filename+path.
	/*! Returns false if no extension was found */
	bool _getFileExt( const std::string& filename, std::string& ext ) {
		size_t prefixLen;
		prefixLen = filename.rfind( "." );
		if ( prefixLen == std::string::npos )
			return false;
		ext = filename.substr( prefixLen + 1 );
		return true;
	}
	//############################################################################
	//! \internal Tests the existence of a file
	/*! Returns true if file exists, false otherwise */
	bool _fileExists( const std::string& filename ) {
		std::ifstream inputFile( filename.c_str(), std::ios::binary | std::ios::ate );
		if ( inputFile.fail() ) {
			return false; //file not found
		}
		return true; //file found
	}
	//############################################################################
	DynamicLib::DynamicLib( const std::string& filename ) {
		//Depending on configuration, we may need to perform file mangling,
		//so this is the best place to do it.
#if !( MANGLE_FIX_EXT || MANGLE_ADD_D )
		//if mangling is completely off, just store the filename as is and return
		mName = filename;
		return;
#else
		//otherwise, let the mangling begin
		std::string path = "", file = "", ext = "";
		std::stringstream finalName;

		_splitFileFromPath( filename, path, file );
		if ( _getFileExt( file, ext ) )
			file = file.substr( 0, file.length() - ( ext.length() + 1 ) ); //drop the "." at the end

		if ( MANGLE_FIX_EXT == ALWAYS )
			ext = DYNLIB_EXT;
#ifdef OPENGUI_DEBUG
		if ( MANGLE_ADD_D == ALWAYS )
			file.append( "_d" );
#endif
		//set up finalName in case we don't enter any of the following insanity
		finalName << path << file;
		if ( ext != "" ) finalName << "." << ext;

		if ( MANGLE_ADD_D == AS_NEEDED && MANGLE_FIX_EXT == AS_NEEDED ) {
			//original
			finalName.str( "" );
			finalName << path << file;
			if ( ext != "" ) finalName << "." << ext;
			if ( !_fileExists( finalName.str() ) ) {
				//original + _d
#ifdef OPENGUI_DEBUG
				finalName.str( "" );
				finalName << path << file << "_d";
				if ( ext != "" ) finalName << "." << ext;
#endif
				if ( !_fileExists( finalName.str() ) ) {
					//original + fixed ext
					finalName.str( "" );
					finalName << path << file << "." << DYNLIB_EXT;
					if ( !_fileExists( finalName.str() ) ) {
						//original + _d + fixed ext
#ifdef OPENGUI_DEBUG
						finalName.str( "" );
						finalName << path << file << "_d" << "." << DYNLIB_EXT;
#endif
						if ( !_fileExists( finalName.str() ) ) {
							//file doesn't exist!
							finalName.str( filename );
							OG_THROW( Exception::OP_FAILED, "Could not mangle library file name into a valid file: " + finalName.str(), "DynamicLib::DynamicLib" );
						}
					}
				}
			}
		} else if ( MANGLE_ADD_D == AS_NEEDED ) {
			//original
			finalName.str( "" );
			finalName << path << file;
			if ( ext != "" ) finalName << "." << ext;
			if ( !_fileExists( finalName.str() ) ) {
				//original + _d
#ifdef OPENGUI_DEBUG
				finalName.str( "" );
				finalName << path << file << "_d";
				if ( ext != "" ) finalName << "." << ext;
#endif
				if ( !_fileExists( finalName.str() ) ) {
					//file doesn't exist!
					finalName.str( filename );
					OG_THROW( Exception::OP_FAILED, "Could not mangle library file name into a valid file: " + finalName.str(), "DynamicLib::DynamicLib" );
				}
			}
		} else if ( MANGLE_FIX_EXT == AS_NEEDED ) {
			//original
			finalName.str( "" );
			finalName << path << file;
			if ( ext != "" ) finalName << "." << ext;
			if ( !_fileExists( finalName.str() ) ) {
				//original + fixed ext
				finalName.str( "" );
				finalName << path << file << "." << DYNLIB_EXT;
				if ( !_fileExists( finalName.str() ) ) {
					//file doesn't exist!
					finalName.str( filename );
					OG_THROW( Exception::OP_FAILED, "Could not mangle library file name into a valid file: " + finalName.str(), "DynamicLib::DynamicLib" );
				}
			}
		}

		LogManager::SlogMsg( "DynamicLib", OGLL_INFO )
		<< "Dynamic library file name mangling result: " << filename << " -> " << finalName.str()
		<< Log::endlog;
		mName = finalName.str();
#endif
	}
	//############################################################################
	DynamicLib::~DynamicLib() {}
	//############################################################################
	void DynamicLib::load() {
		mHandle = DYNAMICLIB_LOAD( mName.c_str() );
		if ( !mHandle ) {
			OG_THROW( Exception::OP_FAILED, "Could not load library " + mName, "DynamicLib::load" );
		}
	}
	//############################################################################
	void DynamicLib::unload() {
		if ( !DYNAMICLIB_UNLOAD( mHandle ) ) {
			OG_THROW( Exception::OP_FAILED, "Could not unload library " + mName, "DynamicLib::unload" );
		}
	}
	//############################################################################
	void* DynamicLib::getSymbol( const std::string& symbolName ) const {
		return ( void* ) DYNAMICLIB_GETSYMBOL( mHandle, symbolName.c_str() );
	}
	//############################################################################
}
;//namespace OpenGUI{


