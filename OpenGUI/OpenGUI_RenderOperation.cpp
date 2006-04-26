
#include "OpenGUI.h"

namespace OpenGUI{
	namespace Render{
		//############################################################################
		void AppendRenderOperationList(RenderOperationList& outList, RenderOperationList& inList)
		{
			RenderOperationList::iterator roli = inList.begin();
			while(roli != inList.end()){
				outList.push_back((*roli));
				roli++;
			}
		}
		//############################################################################
		void PrependRenderOperationList(RenderOperationList& outList, RenderOperationList& inList)
		{
			if(inList.size() == 0) return;
			RenderOperationList::reverse_iterator roli = inList.rbegin();
			while(roli != inList.rend()){
				outList.push_front((*roli));
				roli++;
			}			
		}
		//############################################################################




		//############################################################################
		//############################################################################
		
		//############################################################################
		//############################################################################










		//############################################################################
		
	};//namespace Render{
};





