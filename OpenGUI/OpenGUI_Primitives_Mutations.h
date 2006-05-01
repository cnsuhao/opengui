#ifndef F8231B62_E0D5_40ed_BB48_857C27A0E30E
#define F8231B62_E0D5_40ed_BB48_857C27A0E30E

#include "OpenGUI_PreRequisites.h"
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_RenderOperation.h"

namespace OpenGUI{
	
	namespace Render{

		/*! \brief
		This primitive performs a rotation operation on the provided render
		operations according to a given rotation angle and a given origin.

		Positive angles create clockwise rotation, negative angles create counter
		clockwise rotation.

		If no angle is given, the default rotation is 0. If no origin is given,
		the default origin is (0.0f x 0.0f).

		\note This operation does not account for the unbalanced Width/Height ratio
		that is common in widget coordinate space. You'll need to work around that
		issue yourself if it matters to you.

		*/
		class OPENGUI_API PrimitiveRotation : public Primitive
		{
		public:
			PrimitiveRotation() : mRadians(0), mOrigin(FVector2(0.0f,0.0f)) {}
			virtual ~PrimitiveRotation() {}

			//! Returns the RenderOperationList that is the result of this primitive
			RenderOperationList getRenderOperationList();

			//! Sets the origin of the rotation to the given location
			void setOrigin(const FVector2& newOrigin){ mOrigin = newOrigin; }
			//! Sets the rotation angle in radians
			void setAngleRadians(float newAngle){ mRadians = newAngle; }
			//! Sets the rotation angle in degrees
			void setAngleDegrees(float newAngle);

			//! Adds a single RenderOperation to the input RenderOperationList
			void addRenderOperation(const RenderOperation& renderOp);
			//! Adds an entire RenderOperationList to the input RenderOperationList
			void addRenderOperation(const RenderOperationList& renderOpList);
		private:
			float mRadians;
			FVector2 mOrigin;
			RenderOperationList mInputRenderOps;

			inline void _rotateFV2(FVector2& point);
			inline void _rotateRenderOp(RenderOperation& renderOp);
		};

		/*! \brief
		This primitive performs an axis aligned scissor rect operation
		on provided render operations.

		For compatibility reasons, %OpenGUI cannot perform scissor rects
		in hardware, so as a replacement it provides this object to perform
		geometrical	scissor rect functionality.

		The clipping performed will automatically adjust all render operation
		data to properly preserve the intended look of the original render
		operation. This includes vertex color, texture UV, and mask UV.

		Do not expect every render operation you put into this object
		to make it back out. Render operations that are completely outside
		of the specified rect are culled.

		Also, do not expect to get less render operations out than you put
		in. A side effect of geometric clipping is the potential for 3 sided
		polygons to become 4 sided polygons. Since RenderOperation objects
		only support 3 sided polygons, any 4 sided polygons that are produced
		by this object are automatically converted into 2 separate 3 sided
		polygons.

		\note The order in which render operations are received is preserved,
		so this Primitive can be trusted with RenderOperations that have
		a specific draw order.
		*/
		class OPENGUI_API PrimitiveScissorRect : public Primitive
		{
		public:
			PrimitiveScissorRect() : mRect(FRect(0.0f,0.0f,1.0f,1.0f)) {}
			virtual ~PrimitiveScissorRect() {}
			//! Returns the RenderOperationList that is the result of this primitive
			RenderOperationList getRenderOperationList();
			//! Get the current position and size of the ScissorRect 
			FRect getRect(){return mRect;}
			//! Sets the size and position of the ScissorRect to the given FRect
			void setRect(FRect rect){mRect=rect;}

			//! Adds a single RenderOperation to the input RenderOperationList
			void addRenderOperation(const RenderOperation& renderOp);
			//! Adds an entire RenderOperationList to the input RenderOperationList
			void addRenderOperation(const RenderOperationList& renderOpList);
			//! Clears the input RenderOperationList
			void clear();
		private:
			FRect mRect; //size and position of this ScissorRect
			RenderOperationList mInputRenderOps;

			void _SliceRenderOp_Vert_SaveLeft(RenderOperation& input, RenderOperationList& output, float cutPosition);
			void _SliceRenderOp_Vert_SaveRight(RenderOperation& input, RenderOperationList& output, float cutPosition);
			void _SliceRenderOp_Horiz_SaveTop(RenderOperation& input, RenderOperationList& output, float cutPosition);
			void _SliceRenderOp_Horiz_SaveBottom(RenderOperation& input, RenderOperationList& output, float cutPosition);
			static void sliceLineSegment(Vertex& vert1, Vertex& vert2, Vertex& resultVert, float cutPosition, bool cutHorizontal);
		};
	};//namespace Render{
};

#endif
