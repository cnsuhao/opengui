#ifndef C86B2804_DD3E_4376_A531_214DAA9AB8FB
#define C86B2804_DD3E_4376_A531_214DAA9AB8FB

#include "OpenGUI_PreRequisites.h"

#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"

#include "OpenGUI_RenderOperation.h"

namespace OpenGUI {
	class Element; //forward declaration

	/*
	A smarter version that only maintains a cache when it is actively used
	and not constantly being marked dirty would probably speed things up even more.
	The analysis required to determine if a cache is needed would be fairly simple
	to implement. The necessity detection could work off a threshold system that
	would monitor the markDirty() per frame ratio, as well as the cache requests
	per frame ratio. A low cache request per frame ratio would indicate lack of
	need for caching, and a high dirty per frame ratio would indicate that the
	contents are changing too often to be worth caching. Some clever design
	could ensure that these values are not evaluated every frame, as that could
	create a counter-productive result of too much wasted time on complex GUIs.
	*/

	//! \internal This class provides render operation caching services
	/*! The render cache works by holding a complete list of all render operations
		for an element/widget and all of that element's children.

		The current implementation will mindlessly hold a copy of the contents,
		regardless of how often they become dirty.
	*/
	class RenderCache {
	public:
		RenderCache( Element* parent ): mDirty( true ), mParent( parent ) {}
		virtual ~RenderCache() {}
		//! Marks the contents of this cache dirty
		void markDirty();
		//! Returns true if the contents of this cache are dirty
		bool isDirty();
		//! Returns the current size of this cache in bytes
		size_t statCacheSize();

		//! writes the contents of the render cache to the beginning of the given RenderOperationList
		void getCache( Render::RenderOperationList& renderOpList );
		//! Returns a reference to the actual cache, which is faster than \c getCache(), but not as flexible.
		/*! \warning This is provided for high speed read-only purposes \b only. Do not, alter the returned
			RenderOperationList or you will quite likely break something.
		*/
		Render::RenderOperationList& getCacheLiteral();
	private:
		void buildCache();

		bool mDirty;
		Element* mParent;

		Render::RenderOperationList mMyCache;
	};
}
#endif

