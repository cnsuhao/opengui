#ifndef C2BAA2EC_6763_411d_8E50_19614B119573
#define C2BAA2EC_6763_411d_8E50_19614B119573
#include <string>
#include "OpenGUI_Exports.h"
#include "OpenGUI_Resource.h"
namespace OpenGUI{
	//! Abstract class. Used as a base class for custom resource providers.
	class OPENGUI_API ResourceProvider
	{
	public:
		ResourceProvider() { }
		virtual ~ResourceProvider() { }

		virtual void loadResource(const std::string& filename, Resource& output)=0;

		virtual void unloadResource(Resource& resource)=0;
	};
};//namespace OpenGUI{
#endif
