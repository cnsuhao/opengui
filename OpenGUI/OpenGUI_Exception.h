#ifndef C08D1F7D_73BD_44f5_BBEA_5926A6C6E676
#define C08D1F7D_73BD_44f5_BBEA_5926A6C6E676

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"

#if OPENGUI_COMPILER == OPENGUI_COMPILER_MSVC
	// This warning can be disregarded
	#pragma warning (disable : 4251)
#endif

namespace OpenGUI{
#define OG_THROW(code, description, source) \
	throw ( OpenGUI::Exception( code, description, source,  __FILE__, __LINE__ ) )




	//! The only Exception class OpenGUI currently uses.
	class OPENGUI_API Exception
	{
	public:
		enum ExceptionID {
			OP_FAILED,

			ERR_INVALIDPARAMS,

			ERR_DUPLICATE_ITEM,
			ERR_ITEM_NOT_FOUND,

			ERR_FILE_NOT_FOUND,
			ERR_FILE_NOT_READABLE,
			ERR_FILE_NOT_WRITABLE,
			ERR_INTERNAL_ERROR,

			ERR_NOT_IMPLEMENTED
		};
		

		Exception( int code, const std::string& desc, const std::string& srcArea );
		/*! \param code The ExceptionID that most closely matches the problem
			\param desc A string describing the problem
			\param scrArea The name of the module or subsystem that initially threw the exception
			\param file The filename in which the exception occurred
			\param line The line number where the exception occurred
		*/
		Exception( int code, const std::string& desc, const std::string& srcArea, char* file, long line );
		~Exception() {}
		Exception(const Exception& rhs);
		void operator = (const Exception& rhs);
		
		//! Returns a fully formatted string comprised of all available information
		std::string getFullMessage() const;

		int getCode(){return mCode;}
		std::string getSource(){return mSrc;}
		std::string getMessage(){return mMsg;}
		char* getFile(){return mFile;}
		int getLine(){return mLine;}
	private:
		int mCode;
		std::string mSrc;
		std::string mMsg;
		char* mFile;
		int mLine;
		static std::string getCodeStr(int code);
	};
};
#endif
