// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#ifndef C08D1F7D_73BD_44f5_BBEA_5926A6C6E676
#define C08D1F7D_73BD_44f5_BBEA_5926A6C6E676

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_String.h"

#if OPENGUI_COMPILER == OPENGUI_COMPILER_MSVC
// This warning can be disregarded
#pragma warning (disable : 4251)
#endif

namespace OpenGUI {
#define OG_THROW(code, description, source) \
	throw ( OpenGUI::Exception( code, description, source,  __FILE__, __LINE__ ) )

#define OG_NYI \
	OG_THROW( OpenGUI::Exception::ERR_NOT_IMPLEMENTED, "Not Yet Implemented", __FUNCTION__ )



	//! The only Exception class OpenGUI currently uses.
	class OPENGUI_API Exception {
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


		Exception( int code, const String& desc, const String& srcArea );
		/*!
			\param code The ExceptionID that most closely matches the problem
			\param desc A string describing the problem
			\param srcArea The name of the module or subsystem that initially threw the exception
			\param file The filename in which the exception occurred
			\param line The line number where the exception occurred
		*/
		Exception( int code, const String& desc, const String& srcArea, char* file, long line );
		~Exception() {}
		Exception( const Exception& rhs );
		void operator = ( const Exception& rhs );

		//! Returns a fully formatted string comprised of all available information
		String getFullMessage() const;

		int getCode() {
			return mCode;
		}
		String getSource() {
			return mSrc;
		}
		String getMessage() {
			return mMsg;
		}
		char* getFile() {
			return mFile;
		}
		int getLine() {
			return mLine;
		}
	private:
		int mCode;
		int mLine;
		String mMsg;
		String mSrc;
		char* mFile;
		static String getCodeStr( int code );
	};
};
#endif

