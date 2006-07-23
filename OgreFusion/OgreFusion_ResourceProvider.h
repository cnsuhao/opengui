// -----------------------------------------------------------------------------
// OgreFusion_ResourceProvider.h
// -----------------------------------------------------------------------------

#ifndef	_H_OGREFUSION_RESOURCEPROVIDER
#define _H_OGREFUSION_RESOURCEPROVIDER

#include "OgreFusion_Exports.h"

#include "OpenGUI.h"

namespace OpenGUI{
	class OGREFUSION_API OgreResourceProvider: public ResourceProvider
	{
	public:
		OgreResourceProvider();
		virtual ~OgreResourceProvider();
		void setResourceGroup(const std::string& groupName);
		std::string getResourceGroup() const;
		virtual void loadResource(const std::string& filename, Resource& output);
		virtual void unloadResource(Resource& resource);
	protected:
		std::string mResourceGroup;
	};
};//namespace OpenGUI{



#endif // _H_OGREFUSION_RESOURCEPROVIDER
