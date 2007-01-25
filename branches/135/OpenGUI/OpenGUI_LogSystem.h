// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef C2B66BFD_200F_4347_B858_48C47FDF7003
#define C2B66BFD_200F_4347_B858_48C47FDF7003

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_String.h"
#include "OpenGUI_Singleton.h"

#if OPENGUI_COMPILER == OPENGUI_COMPILER_MSVC
// This warning can be disregarded
#pragma warning (disable : 4251)
#endif

#define OGLL_MSG	10
#define OGLL_ERR	20
#define OGLL_WARN	30
#define OGLL_INFO	40
#define OGLL_INFO2	50
#define OGLL_INFO3	60
#define OGLL_VERB	100
#define OGLL_INSANE 200

namespace OpenGUI {
	class Log; //forward declaration


	//! LogListener interface class for creating custom log output streams.
	class OPENGUI_API LogListener {
	public:
		virtual ~LogListener() {}
		/*!
			\param section Name of the log section the message came from
			\param message The message itself
			\param level The log level of the message
		*/
		virtual void write( const String& section, const String& message, unsigned int level ) = 0;
	};


	class OPENGUI_API LogMessage {
		friend class Log;
	public:
		LogMessage();
		LogMessage& operator<< ( const String& val ) {
			mStream << val;
			return *this;
		}
		LogMessage& operator<< ( bool val ) {
			mStream << val;
			return *this;
		}
		LogMessage& operator<< ( short val ) {
			mStream << val;
			return *this;
		}
		LogMessage& operator<< ( unsigned short val ) {
			mStream << val;
			return *this;
		}
		LogMessage& operator<< ( int val ) {
			mStream << val;
			return *this;
		}
		LogMessage& operator<< ( unsigned int val ) {
			mStream << val;
			return *this;
		}
		LogMessage& operator<< ( long val ) {
			mStream << val;
			return *this;
		}
		LogMessage& operator<< ( unsigned long val ) {
			mStream << val;
			return *this;
		}
		LogMessage& operator<< ( float val ) {
			mStream << val;
			return *this;
		}
		LogMessage& operator<< ( double val ) {
			mStream << val;
			return *this;
		}
		LogMessage& operator<< ( long double val ) {
			mStream << val;
			return *this;
		}
		LogMessage& operator<< ( void* val ) {
			mStream << "0x" << val;
			return *this;
		}
		LogMessage& operator<< ( OpenGUI::LogMessage& ( *pf )( LogMessage& ) );
		LogMessage& operator<< ( std::ios_base& ( *pf )( std::ios_base& ) ) {
			mStream << pf;
			return *this;
		}
		LogMessage& operator<< ( const char* str );
	private:
		Log* m_ParentLog;
		unsigned int tmpLogLevel;
		std::stringstream mStream;
	};




	//! Central log manager. Logging messages can be sent through this object, or a specific Log object
	class OPENGUI_API LogManager : public Singleton<LogManager> {
		friend class Log;
	public:
		LogManager() : mLogListenerPtr( 0 ), mLogLevel( ~0 ) {}
		LogManager( LogListener* listener ) : mLogListenerPtr( listener ), mLogLevel( ~0 ) {}
		~LogManager();

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static LogManager& getSingleton( void );

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static LogManager* getSingletonPtr( void );

		//! Send a message through the given log.
		/*! This is equivalent to getLog(log)->write(message, logLevel); \n
			If \c log does not yet exist, it will be created.
		*/
		void logMsg( const String& log, const String& message, unsigned int logLevel );

		//! A stream like interface for writing to logs
		/*! This should be pretty simple to use for just about everyone. Works just like
			standard C++ stream (since it is based off of them).
			myLogmanagerPtr->logMsg("myLog", 1) << "Here is my log entry, and the number " << 4 << Log::end;
		*/
		LogMessage& logMsg( const String& log, unsigned int logLevel );

		//! Same as logMsg, but implemented as a static function, with automatic singleton dereferencing. Should help make your code a little smaller.
		static LogMessage& SlogMsg( const String& log, unsigned int logLevel ) {
			return LogManager::getSingleton().logMsg( log, logLevel );
		};

		//! Sets the used log listener to the given listener. Only 1 LogListener is used at a time.
		/*! If you want more than 1 output stream, do it in a custom LogListener. */
		void setLogListener( LogListener* listener );

		//! Sets the log level that is applied to all messages. This check occurs after the log specific checks.
		void setLevel( unsigned int logLevel );

		//! Explicitly create a new log. \note Log names are case sensitive
		Log* createLog( const String& name );
		//! Get a log by name
		Log* getLog( const String& name );
		//! Destroy a log by name
		void destroyLog( const String& name );
	protected:
		void _writeLogListener( const String& log, const String& message, unsigned int logLevel );
	private:
		LogListener* mLogListenerPtr;
		typedef std::map<String, Log*> LogMap;
		LogMap mLogMap;
		unsigned int mLogLevel;
	};







	//! A log represents a categorization type for messages. Each log is given its own logLevel setting, in addition to the setLevel of the LogManager.
	class OPENGUI_API Log {
		friend class LogManager;
	public:

		//! Sets the log level. Messages with a higher value than the current logLevel are not logged.
		void setLevel( unsigned int newLogLevel );

		//! Write a message to this log.
		void write( const String& message, unsigned int logLevel );

		//! Used for << notation
		LogMessage& write( unsigned int logLevel );

		//! Writes a LogMessage to the Log. This is also a stream manipulator for LogMessage.
		static LogMessage& endlog( LogMessage& in );

	protected:
		//! Protected constructor. Logs are created only by the LogManager
		Log( LogManager* parent, const String& name );
		~Log();
	private:
		String mName;
		LogManager* mParent;
		unsigned int mLogLevel;
		LogMessage mLogMessage;
	};


	//! Default implementation of a LogListener. This one simply writes to a file, truncating it on open.
	class OPENGUI_API LogListenerToFile : public LogListener {
	public:
		LogListenerToFile( const String& filename );
		virtual ~LogListenerToFile();
		virtual void write( const String& section, const String& message, unsigned int level );
	private:
		std::ofstream mFile;
	};

}
; //namespace OpenGUI{

#endif

