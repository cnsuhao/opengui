// -----------------------------------------------------------------------------
// OgreFusion_ResourceProvider.h
// -----------------------------------------------------------------------------

#ifndef	_H_OGREFUSION_RESOURCEPROVIDER
#define _H_OGREFUSION_RESOURCEPROVIDER

#include "OgreFusion_Exports.h"

#include "OpenGUI.h"

namespace OpenGUI {
	//! An implementation of OpenGUI::ResourceProvider that pulls resources from Ogre's built in resource system.
	class OGREFUSION_API OgreResourceProvider: public ResourceProvider {
	public:
		OgreResourceProvider();
		virtual ~OgreResourceProvider();
		//! Sets the ResourceGroup that is to be used when loading non-texture assets.
		/*!  Default is Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME */
		void setResourceGroup( const std::string& groupName );
		//! Returns the ResourceGroup that is currently being used.
		std::string getResourceGroup() const;
		//! Loads a given filename into the given OpenGUI::Resource object
		virtual void loadResource( const std::string& filename, Resource& output );
		//! Unloads the given OpenGUI::Resource object
		virtual void unloadResource( Resource& resource );
	protected:
		std::string mResourceGroup;
	};
}
;//namespace OpenGUI{



#endif // _H_OGREFUSION_RESOURCEPROVIDER
