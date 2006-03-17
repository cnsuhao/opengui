
#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_LogSystem.h"

/* Mmmm... date formatting. Yay. */
std::string formatDateTime(const std::tm& t, const char* fmt)
{
	std::stringstream out;
	const std::time_put<char>& writer = std::use_facet< std::time_put<char> >(out.getloc());
	writer.put(out, out, ' ', &t, fmt, fmt + strlen(fmt));
	return out.str();
}

namespace OpenGUI{
	//############################################################################
	template<> LogManager* Singleton<LogManager>::mptr_Singleton = 0;
	//############################################################################
	LogManager& LogManager::getSingleton(void)
	{
		assert( mptr_Singleton );
		return ( *mptr_Singleton );
	}
	//############################################################################
	LogManager* LogManager::getSingletonPtr(void)
	{
		return mptr_Singleton;
	}
	//############################################################################
	//############################################################################
	LogManager::~LogManager()
	{
		LogMap::iterator iter = mLogMap.begin();
		while(iter != mLogMap.end()){
			delete (*iter).second;
			iter++;
		}
		mLogMap.clear();
	}
	//############################################################################
	void LogManager::logMsg(std::string log, std::string message, unsigned int logLevel)
	{
		createLog(log)->write(message, logLevel);
	}
	//############################################################################
	LogMessage& LogManager::logMsg(std::string log, unsigned int logLevel)
	{
		return createLog(log)->write(logLevel);
	}
	//############################################################################
	void LogManager::setLogListener(LogListener* listener)
	{
		mLogListenerPtr = listener;
	}
	//############################################################################
	void LogManager::setLevel(unsigned int logLevel)
	{
		mLogLevel = logLevel;
	}
	//############################################################################
	Log* LogManager::createLog(std::string name)
	{
		LogMap::iterator iter = mLogMap.find(name);
		if(iter != mLogMap.end())
			return (*iter).second;
		Log* lp = new Log(this, name);
		mLogMap[name] = lp;
		return lp;
	}
	//############################################################################
	Log* LogManager::getLog(std::string name)
	{
		LogMap::iterator iter = mLogMap.find(name);
		if(iter == mLogMap.end())
			return 0;
		return (*iter).second;
	}
	//############################################################################	
	void LogManager::destroyLog(std::string name)
	{
		LogMap::iterator iter = mLogMap.find(name);
		if(iter == mLogMap.end())
			return;
		delete (*iter).second;
		mLogMap.erase(iter);
	}
	//############################################################################
	void LogManager::_writeLogListener(std::string log, std::string message, unsigned int logLevel)
	{
		//
		if(mLogListenerPtr){
			if(logLevel <= mLogLevel){
				mLogListenerPtr->write(log, message, logLevel);
			}
		}
	}


	//############################################################################
	//############################################################################
	//############################################################################
	

	Log::Log(LogManager* parent, std::string name) 
		: mName(name), mParent(parent), mLogLevel(-1)
	{
#ifdef OPENGUI_DEBUG
		write(0) << "**Log Type Created**" << Log::endlog;
#endif
	}
	//############################################################################
	Log::~Log()
	{
#ifdef OPENGUI_DEBUG
		write(0) << "**Log Type Destroyed**" << Log::endlog;
#endif
	}
	//############################################################################
	void Log::setLevel(unsigned int newLogLevel)
	{
		mLogLevel = newLogLevel;
#ifdef OPENGUI_DEBUG
		write(newLogLevel) << " ]LOG LEVEL CHANGED[ = " << newLogLevel << Log::endlog;
#endif
	}
	//############################################################################
	void Log::write(std::string message, unsigned int logLevel)
	{
		if(logLevel <= mLogLevel){
			mParent->_writeLogListener(mName, message, logLevel);
		}
	}
	//############################################################################
	LogMessage& Log::write(unsigned int logLevel)
	{
		mLogMessage.tmpLogLevel = logLevel;
		mLogMessage.m_ParentLog=this;
		return mLogMessage;
	}
	//############################################################################
	LogMessage& Log::endlog(LogMessage& in){

		if(in.m_ParentLog){
			in.m_ParentLog->write(in.mStream.str(), in.tmpLogLevel);
			in.mStream.str(""); //clear the stream
			in.mStream.clear();
		}
		return in;
	}
	//############################################################################





	//############################################################################
	//############################################################################
	//############################################################################




	LogListenerToFile::LogListenerToFile(std::string filename)
	{
		mFile.open(filename.c_str(), std::ios_base::trunc | std::ios_base::out);
		write("","*** Log Started ***",0);
	}
	//############################################################################
	LogListenerToFile::~LogListenerToFile()
	{
		write("","*** Log Ended ***",0);
		mFile.close();
	}
	//############################################################################
	void LogListenerToFile::write(std::string section, std::string message, unsigned int level)
	{
		using namespace std;
		time_t now = time(0);
		tm* local = localtime(&now);
		mFile << formatDateTime(*local, "%H:%M:%S") << ") ";

		if(section.length() > 0){
			mFile << setw(8) << section << setw(0) << " ";
			mFile << "[" << setw(3) << right << level << setw(0) << left << "]";
			mFile << " -:- ";
		}else{
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
	LogMessage::LogMessage()
	{
		 m_ParentLog = 0;
	}
	//############################################################################
	LogMessage& LogMessage::operator<< (OpenGUI::LogMessage& ( *pf ) (LogMessage&))
	{
		return (pf)(*this);
	}
	//############################################################################
	LogMessage& LogMessage::operator<< (const char* str )
	{
		this->mStream << str; return *this;
	}
	//############################################################################

};//namespace OpenGUI{