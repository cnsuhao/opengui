// OpenGUI (http://opengui.sourceforge.net)
// This source code is release under the BSD License
// See LICENSE.TXT for details

#include "OpenGUI_RenderOperation.h"

namespace OpenGUI {
	namespace Render {
		//############################################################################
		void AppendRenderOperationList( RenderOperationList& outList, const RenderOperationList& inList ) {
			RenderOperationList::const_iterator roli = inList.begin();
			while ( roli != inList.end() ) {
				outList.push_back(( *roli ) );
				roli++;
			}
		}
		//############################################################################
		void PrependRenderOperationList( RenderOperationList& outList, const RenderOperationList& inList ) {
			if ( inList.size() == 0 ) return;
			RenderOperationList::const_reverse_iterator roli = inList.rbegin();
			while ( roli != inList.rend() ) {
				outList.push_front(( *roli ) );
				roli++;
			}
		}
		//############################################################################




		//############################################################################
		//############################################################################

		//############################################################################
		//############################################################################










		//############################################################################

	}
	;//namespace Render{
};





