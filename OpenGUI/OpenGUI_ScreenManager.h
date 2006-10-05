#ifndef A0225006_7C8D_45CC_9C07_5328679AD103
#define A0225006_7C8D_45CC_9C07_5328679AD103

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Singleton.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"

#include "OpenGUI_Iterators.h"

namespace OpenGUI {
	class System;
	class Screen;

	//! Manages creating, destroying, and lookup of Screen objects
	class OPENGUI_API ScreenManager: public Singleton<ScreenManager> {
		friend class System;
	public:
		typedef std::map<std::string, Screen*> ScreenMap;
		typedef MapIterator<ScreenMap, ScreenMap::iterator> iterator;
		typedef MapIterator<ScreenMap, ScreenMap::const_iterator> const_iterator;

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve the current singleton, if one exists. If none exists, this will cause an error.
		static ScreenManager& getSingleton( void );

		//Reimplementation required for this style of singleton implementation to work across DLLs
		//! Retrieve a pointer to the current singleton, if one exists. If none exists, this will return 0.
		static ScreenManager* getSingletonPtr( void );

		//! Creates a new screen with the given name at the given initial size
		Screen* createScreen( const std::string& screenName, const FVector2& initialSize );
		//! destroys the given screen
		void destroyScreen( Screen* screenPtr );
		//! returns the requested screen by name, or 0 on failure
		Screen* getScreen( const std::string& screenName );

		//! performs an update on all screens that are auto updating
		void updateScreens();

		//! returns an iterator to walk the current list of screens
		iterator getIterator() {
			return iterator( mScreenMap.begin(), mScreenMap.end() );
		}

		/*! \internal Notifies each Screen that the main viewport just changed size,
		so it can take the appropriate action */
		void _notifyViewportDimensionsChanged();
	protected:
		void destroyAllScreens();
	private:
		ScreenManager();
		~ScreenManager();

		ScreenMap mScreenMap;
	};
} //namespace OpenGUI {

#endif // A0225006_7C8D_45CC_9C07_5328679AD103
