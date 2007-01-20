// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

// -----------------------------------------------------------------------------
// Renderer_Ogre_ResourceProvider.h
// -----------------------------------------------------------------------------

#ifndef	_H_OGR_OGRE_RESOURCEPROVIDER
#define _H_OGR_OGRE_RESOURCEPROVIDER

#include "Renderer_Ogre_Exports.h"

#include "OpenGUI.h"

namespace OpenGUI {
	//! An implementation of OpenGUI::ResourceProvider that pulls resources from Ogre's built in resource system.
	class OGR_OGRE_API OgreResourceProvider: public ResourceProvider {
	public:
		OgreResourceProvider();
		virtual ~OgreResourceProvider();
		//! Sets the ResourceGroup that is to be used when loading non-texture assets.
		/*!  Default is Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME */
		void setResourceGroup( const String& groupName );
		//! Returns the ResourceGroup that is currently being used.
		const String& getResourceGroup() const;
		//! Loads a given filename into the given OpenGUI::Resource object
		virtual void loadResource( const String& filename, Resource& output );
		//! Unloads the given OpenGUI::Resource object
		virtual void unloadResource( Resource& resource );
	protected:
		String mResourceGroup;
	};
}
;//namespace OpenGUI{



#endif // _H_OGR_OGRE_RESOURCEPROVIDER
