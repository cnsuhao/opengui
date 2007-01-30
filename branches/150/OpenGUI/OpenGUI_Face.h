// OpenGUI (http://opengui.sourceforge.net)
// This source code is released under the BSD License
// See LICENSE.TXT for details

#ifndef F93B4D11_706D_4fab_B757_BCEAC2BEA28F
#define F93B4D11_706D_4fab_B757_BCEAC2BEA28F

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_String.h"
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

	//! list of Slices from a Face
	typedef std::list<Slice> SliceList;
	//! Array of float dimensions representing column or row size in a Face
	typedef std::vector<float> FaceDimArray;

	//! Provides an HTML table like system for controlled stretching and tiling of logical groups of display imagery
	/*!	Faces are used to join several previously defined Imagery together in an HTML table-like fashion,
	providing minimum widths and heights, selective growth, and column/row spanning. They are drawn as a
	single unit, automatically scaling as necessary to fit the desired coverage area, while doing their
	best to scale only in designated directions.

	\see BrushImagery::drawFace()
	*/
	class OPENGUI_API Face {
	public:
		//! Used to dictate the metric of measurement used in Face related objects
		enum FaceMetric{
			FM_UNITS = 0, //!< The size is in Screen units
			FM_PIXELS = 1 //!< The size is in pixels of the native display
		};
		//! Takes a FaceDef (Face definition) and generates a Face which is returned in a reference counted pointer
		static FacePtr Create( const String& faceName, const FaceDef& faceDefinition );
		~Face() {}
		//! Indicates the metric that should be used when rendering this Face
		const FaceMetric Metric;

		//! Returns the name of this Face
		const String& getName() {
			return mName;
		}

		//! fills the \c columnArray_out with column widths to fit the \c totalWidth
		void getColumnWidths( float totalWidth, FaceDimArray& columnArray_out );
		//! fills the \c rowArray_out with row heights to fit the \c totalHeight
		void getRowHeights( float totalHeight, FaceDimArray& rowArray_out );
		//! returns a reference to the list of Slices used in this Face
		const SliceList& getSlices();

	private:
		String mName;
		Face( const String& faceName, const FaceDef& faceDefinition );
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

		// a few cache objects to save a bit of time later
		float m_CacheRowSize; // minimum possible height of the entire face
		float m_CacheColSize; // minimum possible width of the entire face
		size_t m_CacheRowGrowing; // the number of rows that volunteer growth
		size_t m_CacheColGrowing; // the number of columns that volunteer growth

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
