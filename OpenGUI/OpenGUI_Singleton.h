// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef A8610A28_E6EA_4818_A265_FE8970EA50DC
#define A8610A28_E6EA_4818_A265_FE8970EA50DC




#if defined(_WINDOWS) && defined(_MSC_VER) //thanks for the warning Bill
#   pragma warning (disable : 4311)
#   pragma warning (disable : 4312)
#   pragma warning (disable : 4661)
#   pragma warning (disable : 4267)
#endif


//Reference to author of this singleton's base:
/* "Portions Copyright (C) Scott Bilas, 2000" */

namespace OpenGUI {
	template <typename T> class Singleton {
	protected:
		static T* mptr_Singleton;
	public:
		Singleton() {
			assert( !mptr_Singleton );
			mptr_Singleton = static_cast<T*>( this );
		}

		~Singleton() {
			assert( mptr_Singleton );
			mptr_Singleton = 0;
		}

		static T& getSingleton( void ) {
			assert( mptr_Singleton );
			return ( *mptr_Singleton );
		}
		static T* getSingletonPtr( void ) {
			assert( mptr_Singleton );
			return mptr_Singleton;
		}
	};
};
#endif

