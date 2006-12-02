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

	//! A single slice within a Face. Can span multiple columns and rows
	class OPENGUI_API Slice {
	public:
		ImageryPtr Imagery; //!< Imagery for this slice
		size_t CellRow; //!< Cell row this Slice starts in
		size_t CellCol; //!< Cell column this Slice starts in
		unsigned short RowSpan; //!< Number of additional cells this slice spans horizontally
		unsigned short ColSpan; //!< Number of additional cells this slice spans vertically
		bool Tiled; //!< true if imagery should be displayed native scale and tiled, otherwise it is stretched to fit
	};


	//! Provides an HTML table like system for controlled stretching and tiling of logical groups of display imagery
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
		
		typedef std::list<Slice> SliceList;
		SliceList mSlices;

		class SliceDim	{
		public:
			SliceDim(): MinSize( 0.0f ), Grow( false ) {}
			~SliceDim() {}
			float MinSize; //!< minimum size of this slice dimension
			bool Grow; //!< true if this slice dimension volunteers for growing
		};
		typedef std::vector<SliceDim> AxisDimArray;
		AxisDimArray mRowDims;
		AxisDimArray mColDims;

		class Cell {
		public:
			Cell(): slicePtr( 0 ) {}
			~Cell() {}
			Slice* slicePtr;
		};
		typedef std::vector<Cell> CellVector;
		typedef std::vector<CellVector> CellRowVector;

	};




} // namespace OpenGUI{

#endif // F93B4D11_706D_4fab_B757_BCEAC2BEA28F
