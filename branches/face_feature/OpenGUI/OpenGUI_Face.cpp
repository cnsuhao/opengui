#include "OpenGUI_Face.h"
#include "OpenGUI_FaceDef.h"
#include "OpenGUI_Exception.h"

namespace OpenGUI {
	//############################################################################
	// We're doing this to ensure that memory destroyed within OpenGUI is also created within OpenGUI
	FacePtr Face::Create( const FaceDef& faceDefinition ) {
		return new Face( faceDefinition );
	}
	//############################################################################
	Face::Face( const FaceDef& faceDefinition ): Metric( faceDefinition.Metric ) {
		mColDims.resize( faceDefinition.getRequiredCols() );
		mRowDims.resize( faceDefinition.getRequiredRows() );
	}
	//############################################################################
} // namespace OpenGUI {