#ifndef A13D1E9F_9387_4014_8FDC_196E0F682766
#define A13D1E9F_9387_4014_8FDC_196E0F682766

#include "OpenGUI_Exports.h"
#include "OpenGUI_ResourceProvider.h"
namespace OpenGUI {
	//! This is the defailt generic implementation of the resource provider
	/*! If no specialized resource provider is given during creation of the
		System() object, then this resource provider is automatically loaded
		used. It is a completely unglorified provider. It reads from files
		directly off the disk, and requires proper relative or full paths
		to these files. It literally does nothing more than act as a
		passthrough to fstream. Most applications will want to create their
		own resource provider, as this one is very low on features.
	*/
	class OPENGUI_API GenericResourceProvider : public ResourceProvider {
	public:
		GenericResourceProvider() { }
		~GenericResourceProvider() { }

		void loadResource( const std::string& filename, Resource& output );

		void unloadResource( Resource& resource );
	};
}
;//namespace OpenGUI{
#endif

