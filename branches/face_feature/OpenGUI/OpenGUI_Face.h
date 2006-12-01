#ifndef F93B4D11_706D_4fab_B757_BCEAC2BEA28F
#define F93B4D11_706D_4fab_B757_BCEAC2BEA28F

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Imagery.h"

namespace OpenGUI {
	class FaceDef; // forward declaration
	class Face; // forward declaration
	//! Reference counted, auto deleting Face pointer
	typedef RefPtr<Face> FacePtr;

	class OPENGUI_API Slice {
		ImageryPtr Imagery;
		size_t CellRow;
		size_t CellCol;
		unsigned short RowSpan;
		unsigned short ColSpan;
		bool Tiled;
	};

	class OPENGUI_API SliceDim	{
		float MinSize;
		bool Grow;
	};

	class OPENGUI_API Cell {
		Slice* slicePtr;
	};

	//! Provides an HTML table like system for controlled stretching and tiling of logical groups of display imagery
	/*!
	*/
	class OPENGUI_API Face {
	public:
		//! Used to dictate the metric of measurement used in Face related objects
		enum FaceMetric{
			FM_UNITS = 0, //!< The size is in Screen units
			FM_PIXELS = 1 //!< The size is in pixels of the native display
		};
		static FacePtr Create( const FaceDef& faceDefinition );
		~Face() {}
		const FaceMetric Metric;
	private:
		Face( const FaceDef& faceDefinition );
		typedef std::vector<SliceDim> AxisDimArray;
		AxisDimArray mRowDims;
		AxisDimArray mColDims;
	};




} // namespace OpenGUI{

#endif // F93B4D11_706D_4fab_B757_BCEAC2BEA28F
