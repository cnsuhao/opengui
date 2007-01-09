// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_LogSystem.h"

/* Mmmm... date formatting. Yay. */
std::string formatDateTime( const std::tm& t, const char* fmt ) {
	std::stringstream out;
	const std::time_put<char>& writer = std::use_facet< std::time_put<char> > ( out.getloc() );
	writer.put( out, out, ' ', &t, fmt, fmt + strlen( fmt ) );
	return out.str();
}

namespace OpenGUI {
	//############################################################################
	template<> LogManager* Singleton<LogManager>::mptr_Singleton = 0;
	//############################################################################
	LogManager& LogManager::getSingleton( void ) {
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	LogManager* LogManager::getSingletonPtr( void ) {
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	LogManager::~LogManager() {
		LogMap::iterator iter = mLogMap.begin();
		while ( iter != mLogMap.end() ) {
			delete( *iter ).second;
			iter++;
		}
		mLogMap.clear();
	}
	//############################################################################
	void LogManager::logMsg( const String& log, const String& message, unsigned int logLevel ) {
		createLog( log )->write( message, logLevel );
	}
	//############################################################################
	LogMessage& LogManager::logMsg( const String& log, unsigned int logLevel ) {
		return createLog( log )->write( logLevel );
	}
	//############################################################################
	void LogManager::setLogListener( LogListener* listener ) {
		mLogListenerPtr = listener;
	}
	//############################################################################
	void LogManager::setLevel( unsigned int logLevel ) {
		mLogLevel = logLevel;
	}
	//############################################################################
	Log* LogManager::createLog( const String& name ) {
		LogMap::iterator iter = mLogMap.find( name );
		if ( iter != mLogMap.end() )
			return ( *iter ).second;
		Log* lp = new Log( this, name );
		mLogMap[name] = lp;
		return lp;
	}
	//############################################################################
	Log* LogManager::getLog( const String& name ) {
		LogMap::iterator iter = mLogMap.find( name );
		if ( iter == mLogMap.end() )
			return 0;
		return ( *iter ).second;
	}
	//############################################################################
	void LogManager::destroyLog( const String& name ) {
		LogMap::iterator iter = mLogMap.find( name );
		if ( iter == mLogMap.end() )
			return;
		delete( *iter ).second;
		mLogMap.erase( iter );
	}
	//############################################################################
	void LogManager::_writeLogListener( const String& log, const String& message, unsigned int logLevel ) {
		//
		if ( mLogListenerPtr ) {
			if ( logLevel <= mLogLevel ) {
				mLogListenerPtr->write( log, message, logLevel );
			}
		}
	}


	//############################################################################
	//############################################################################
	//############################################################################


	Log::Log( LogManager* parent, const String& name )
			: mName( name ), mParent( parent ), mLogLevel( ~0 ) {
#ifdef OPENGUI_DEBUG
		//write(0) << "**Log Type Created**" << Log::endlog;
#endif
	}
	//############################################################################
	Log::~Log() {
#ifdef OPENGUI_DEBUG
		//write(0) << "**Log Type Destroyed**" << Log::endlog;
#endif
	}
	//############################################################################
	void Log::setLevel( unsigned int newLogLevel ) {
		mLogLevel = newLogLevel;
#ifdef OPENGUI_DEBUG
		//write(newLogLevel) << " ]LOG LEVEL CHANGED[ = " << newLogLevel << Log::endlog;
#endif
	}
	//############################################################################
	void Log::write( const String& message, unsigned int logLevel ) {
		if ( logLevel <= mLogLevel ) {
			mParent->_writeLogListener( mName, message, logLevel );
		}
	}
	//############################################################################
	LogMessage& Log::write( unsigned int logLevel ) {
		mLogMessage.tmpLogLevel = logLevel;
		mLogMessage.m_ParentLog = this;
		return mLogMessage;
	}
	//############################################################################
	LogMessage& Log::endlog( LogMessage& in ) {

		if ( in.m_ParentLog ) {
			in.m_ParentLog->write( in.mStream.str(), in.tmpLogLevel );
			in.mStream.str( "" ); //clear the stream
			in.mStream.clear();
		}
		return in;
	}
	//############################################################################





	//############################################################################
	//############################################################################
	//############################################################################




	LogListenerToFile::LogListenerToFile( const String& filename ) {
		mFile.open( filename.c_str(), std::ios_base::trunc | std::ios_base::out );
		write( "", "*** Log Started ***", 0 );
	}
	//############################################################################
	LogListenerToFile::~LogListenerToFile() {
		write( "", "*** Log Ended ***", 0 );
		mFile.close();
	}
	//############################################################################
	void LogListenerToFile::write( const String& section, const String& message, unsigned int level ) {
		static unsigned int sSectionWidth = 0;

		using namespace std;
		time_t now = time( 0 );
		tm* local = localtime( &now );
		mFile << formatDateTime( *local, "%H:%M:%S" ) << ") ";

		if ( section.length() > 0 ) {
			if ( section.length() > sSectionWidth ) sSectionWidth = section.length();
			mFile << setw( sSectionWidth ) << left << section << setw( 0 ) << " ";
			mFile << "[" << setw( 3 ) << right << level << setw( 0 ) << left << "]";
			mFile << " : ";
		} else {
			mFile << "     ";
		}

		mFile << message;
		mFile << endl;
	}
	//############################################################################


	//############################################################################
	//############################################################################
	//############################################################################


	//############################################################################
	LogMessage::LogMessage() {
		m_ParentLog = 0;
	}
	//############################################################################
	LogMessage& LogMessage::operator<< ( OpenGUI::LogMessage& ( *pf )( LogMessage& ) ) {
		return ( pf )( *this );
	}
	//############################################################################
	LogMessage& LogMessage::operator<< ( const char* str ) {
		this->mStream << str;
		return *this;
	}
	//############################################################################

}
;//namespace OpenGUI{

