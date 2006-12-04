#ifndef F96FFCA7_25E8_4415_989A_C98260D42A40
#define F96FFCA7_25E8_4415_989A_C98260D42A40

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Imagery.h"
#include "OpenGUI_Face.h"

namespace OpenGUI {

	//! Used with FaceDef to define the attributes of a Slice within a Face
	class OPENGUI_API SliceDef {
	public:
		//! Constructor allows you to define increasing detail, or nothing at all
		SliceDef( ImageryPtr imagery = 0, bool tileImage = false,
				  float width = 0.0f, float height = 0.0f,
				  bool growWidth = false, bool growHeight = false,
				  unsigned short colSpan = 0, unsigned short rowSpan = 0 )
				: Width( width ), GrowWidth( growWidth ), Height( height ), GrowHeight( growHeight ),
				Imagery( imagery ), Tile( tileImage ), ColSpan( colSpan ), RowSpan( rowSpan ) {}

		//! The minimum width the slice should cover
		float Width;
		//! Set to \c true if you want this slice to volunteer to widen to fill left over space
		bool GrowWidth;
		//! The minimum height the slice should cover
		float Height;
		//! Set to \c true if you want this slice to volunteer to heighten to fill left over space
		bool GrowHeight;
		//! The imagery this slice will use for display
		ImageryPtr Imagery;
		//! Set to \c true to display imagery using native pixel size with tiling, otherwise it will be stretched to fit the slice area
		bool Tile;
		//! Number of \em additional columns this slice spans across
		unsigned short ColSpan;
		//! Number of \em additional rows this slice spans across
		unsigned short RowSpan;
	};

	//! Represents Face definitions, which are later used to create Face objects
	/*! This class is designed to assist in creation of Face objects. Since the data
	used to construct a Face needs to be in a special format and leaves a lot of opportunities
	for errors and ambiguity, this class must be used to define how a Face should look.

	The SliceDefs themselves allow for row and column spanning, but the actual spanning of
	the resulting Slices is done in later code. So you should not add padding slices
	to this structure to cover the spanned area. Doing so will result in additional (unexpected)
	slices created at later stages.

	Spanning is processed in a style that similar to HTML tables. Slices are processed in left
	to right and top to bottom order. As slices are spanned, they will push conflicting slices
	to the right. This means that a row containing 2 SliceDefs, one with ColSpan=1 and the other
	ColSpan=0, would actually generate a row in the final Face that contained 3 columns. This effect
	occurs when using RowSpan as well, but remember that slices are only pushed right, so when RowSpan
	consumes an cell in a later row, the slice that would normally be in that position is moved to the
	right until it finds an open space. */
	class OPENGUI_API FaceDef {
	public:
		FaceDef() {}
		~FaceDef() {}
		//! The metric the final face will used
		Face::FaceMetric Metric;
		//! vector of SliceDef objects
		typedef std::vector<SliceDef> SliceDefVector;
		//! vector of SliceDefVector objects
		typedef std::vector<SliceDefVector> SliceRowDefVector;
		//! Direct access to the row/slice data
		SliceRowDefVector Rows;

		//! returns a reference to the requested slice definition, lengthening the 2d array if necessary
		SliceDef& getSlice( size_t col, size_t row );

		//! returns a rough guess on the number of rows needed, not always accurate but never over estimates
		size_t getRowSizeEstimate() const;
		//! returns a rough guess on the number of columns needed, not always accurate but never over estimates
		size_t getColSizeEstimate() const;

	private:
	};
} // namespace OpenGUI {

#endif // F96FFCA7_25E8_4415_989A_C98260D42A40
