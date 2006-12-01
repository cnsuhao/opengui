#ifndef F96FFCA7_25E8_4415_989A_C98260D42A40
#define F96FFCA7_25E8_4415_989A_C98260D42A40

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Imagery.h"
#include "OpenGUI_Face.h"

namespace OpenGUI {

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


	class OPENGUI_API FaceDef {
	public:
		FaceDef() {}
		~FaceDef() {}
		Face::FaceMetric Metric;
		typedef std::vector<SliceDef> SliceDefVector;
		typedef std::vector<SliceDefVector> SliceRowDefVector;
		SliceRowDefVector Rows;

		//! returns a reference to the requested slice definition, lengthening the 2d array if necessary
		SliceDef& getSlice( size_t row, size_t col );

		size_t getRequiredRows() const;
		size_t getRequiredCols() const;
	private:
	};
} // namespace OpenGUI {

#endif // F96FFCA7_25E8_4415_989A_C98260D42A40
