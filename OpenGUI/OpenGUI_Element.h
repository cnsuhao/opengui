#ifndef FD413C40_A7DC_403f_AC1F_C64C2A26DC05
#define FD413C40_A7DC_403f_AC1F_C64C2A26DC05
#include <list>
#include <string>
#include "OpenGUI_Exports.h"
#include "OpenGUI_Types.h"
#include "OpenGUI_Event.h"
#include "OpenGUI_Subscriber.h"

namespace OpenGUI{
	typedef Element* ChildElementListItem;
	typedef std::list<ChildElementListItem> ChildElementList;
	typedef Element* ElementAncestryItem;
	typedef std::list<ElementAncestryItem> ElementAncestryList;
	typedef Element* ElementListItem;
	typedef std::list<ElementListItem> ElementList;

	//! This is the base class for all GUI elements. It provides a very basic functionality set.
	/*! The Element class should be inherited by all classes that need to exist within a GUI.
	*/
	class OPENGUI_API Element
	{
		friend class System;
		friend class GUISheet;
	public:
		Element();
		virtual ~Element();

		//! returns the name of this object
		std::string getName();

		/*! Attaches the given Subscriber to this element so that it will receive event
			notifications from this object.

			This is a design element to allow an application to monitor actions
			taking place within the gui so that it can react to them.

			\see Subscriber
		*/
		void attachEventSubscriber(Subscriber sub);
		/*! Detaches the given Subscriber from this element so that it will no longer
			receive event notifications from this object.

			\see Subscriber
		*/
		void detachEventSubscriber(Subscriber sub);

		//! Adds the given Element as a child of this parent
		/*! Any element, customized or not, is added to the GUI by attaching it as a child of
			another GUI Element, or as a child of a GUISheet.
		\param child The pointer to the created Element inheriting object that you wish to add.
		\param name (Optional) The unique name for this Element. This can be used to
				retrieve the object pointer, so you don't have to keep track of it yourself.
				If you do not provide a name for this object, one will be created for you.
		\note OpenGUI assumes responsibility for Element pointers when passed in via this function.
				It will automatically delete the object when it is no longer needed unless you go out
				of your way to ensure the object survives. \see removeChildElement
		*/
		void addChildElement(Element* child, std::string name="");

		//! Retrieves a pointer to a child Element by its name.
		/*!
			\param name The name of the Element that was given during addChildElement().
			\return A pointer to the Element of the given name on success, 0 otherwise.

			\todo make protected
		*/
		Element* getChildElement(const std::string& name);

		//! As getChildElement() except that this version will search recursively down the hierarchy for the Element.
		/*! \see getChildElement() \todo make protected */
		Element* getChildElementRecursive(const std::string& name);

		//! Removes an Element from this Parent's list of children and deletes the child object.
		/*! This is the usual way that child Elements are removed, as there is usually no need
			to remove an Element and reattach somewhere else.
		\param child The pointer to the child Element you wish to remove.
		\throw Exception If child cannot be found in the list of immediate children (descendants are not checked)
				this will throw an Exception.
		*/
		void destroyChildElement(Element* child);
		//! Removes an Element from this Parent's list of children and deletes the child object.
		/*!
		\param name The name of the child Element you wish to remove.
		\throw Exception If child cannot be found in the list of immediate children (descendants are not checked)
				this will throw an Exception.
		*/
		void destroyChildElement(std::string name);
		
		//! Removes an Element from this Parent's list of children, \b without deleting the object.
		/*! This is a similar function to destroyChildElement, with the key exception that the
			child object itself is not deleted after it is removed from the parent. Because of the
			obvious opportunity for memory leaks in this situation, you must provide the pointer
			to the object that you wish to remove. This will at least prove that you had it at some
			point, and now it is your fault that you leaked memory.
		\param child The pointer to the child Element you wish to remove.
		\throw Exception If child cannot be found in the list of immediate children (descendants are not checked)
				this will throw an Exception. This can be avoided easily enough by ensuring that
				child->getElementParent() returns a pointer to the parent from which you are calling removeChildElement().
		*/
		void removeChildElement(Element* child);
		
		//! Same as destroyChildElement(), but is called on all children automatically.
		/*! This is also implicitly called by the object destructor to ensure that slicing off
			a large hierarchy of Elements by deleting a parent does not result in memory leaks.
		*/
		void destroyAllChildElements();

		//! Performs a sort on all child elements based on ZOrder and AlwaysOnTop state.
		/*!
			This is normally only called as a result of Element::notifyElementParentZChange().
			The child elements should normally alway be held in the correct draw order,
			this is only necessary if one of the children changes its z order on it's own.
		*/
		void sortChildElements();

		//! Returns a copy of the current list of child Elements.
		/*! The returned list is only a copy of the current ChildElementList, thus any changes to the
			returned list will not affect the true child list of this Element. Also, any changes
			to the true list that occur after the call to this function will not be reflected on the
			copy list. You are effectively getting a snap shot of the child list, so be aware that
			as you make function calls that affect the hierarchy, your snapshot can become out of
			date quite quickly.
			\warning While the contents of the returned list are a snapshot of the current ChildElementList,
			the Element pointers within that list are real. Making changes to those objects will
		*/
		ChildElementList getChildElementList();

		//! Retrieves the Z extents of this Element's child elements.
		/*!
			If the Element has no children, then both upperZ and lowerZ
			will be set to 0.
			\param upperZ Will be set to the ZOrder of the highest child
			\param lowerZ Will be set to the ZOrder of the lowest child
			\note This is normally only used by Element::sendToBack() and Element::bringToFront().
				Because of this, I may make it a private member function and give it an underscore.
		*/
		void getChildElementZOrderExtents(int& upperZ, int& lowerZ);

		//! Updates the URect that represents size and position with an entirely new value.
		void setRect(FRect& newRect);
		//! Returns a copy of the Element's URect (size and position)
		FRect getRect();
		//! Sets the position of the Element
		void setPos(FVector2& newPosition);
		void setPos(const float& xPos, const float& yPos);
		//! Sets the size of the Element
		void setSize(FVector2& newSize);
		void setSize(const float& width, const float& height);
		bool isActive(){return !mDisabled;}
		bool isDisabled(){return mDisabled;}
		void setDisabled(bool disabled){mDisabled=disabled;}

		//! Returns the ZOrder index of this Element
		int getZOrder();
		//! Sets the ZOrder index of this Element
		void setZOrder(int newZOrder);
		//! Sets the ZOrder index of this Element to one less than the lowest of its siblings \todo implement
		void sendToBack();
		//! Sets the ZOrder index of this Element to one higher than the highest of its siblings \todo implement
		void bringToFront();
		//! Returns if this Element is set to be Always On Top
		bool getAlwaysOnTop() const;

		//! Sets the Always On Top state of this Element
		/*!
			Always On Top is a state that provides an additional level
			of draw order preference within a ParentElement. What this
			means is that if only one Element within a ParentElement is
			set to be Always On Top, then it actually always will be on top.
			However if more than one Element within the same ParentElement
			are set to be Always On Top, then their ZOrder will determine
			which one actually \b is on top. Regardless, Elements that are
			set Always On Top, will always be on top of Elements that are not
			set Always On Top.
		*/
		void setAlwaysOnTop(bool newAlwaysOnTop);

		
		//! Returns an FVector2 in world coords that represents the given FVector2 in local coords. (Local coords are just outside this Element's rect)
		FVector2 convCoordLocalToWorld(FVector2 localCoord);
		//! Returns an FVector2 in world coords that represents the given FVector2 in inner coords. (Inner coords are inside this Element's rect)
		FVector2 convCoordInnerToWorld(FVector2 innerCoord);

		//! Returns an FVector2 in local coords that represents the given FVector2 in world coords. (Local coords are just outside this Element's rect)
		FVector2 convCoordWorldToLocal(FVector2 worldCoord);
		//! Returns an FVector2 in inner coords that represents the given FVector2 in world coords. (Inner coords are inside this Element's rect)
		FVector2 convCoordWorldToInner(FVector2 worldCoord);


	protected:

		//! The default event handler for all events reaching this Element.
		/*!
			This function is intended to be overridden by subclasses to provide
			built in Widget functionality. If a user would like to mute the
			defaultEventHandler of any Widget for any event type for any reason,
			then that user should subclass that widget type and provide the
			necessary logic to mute the desired events.

			\note It is the responsibility of all subclasses to explicitly call the
				defaultEventHandler() of their immediate superclass if they wish to
				preserve existing functionality of that class. The event types that
				are passed back the class tree can, of course, be filtered by the
				subclass if such resulting functionality is desired.
		*/
		virtual bool defaultMessageHandler(const Msg::Message& message);

		//! This function will be called by the system whenever it needs the widget to redraw itself. Returned list should be depth ordered using a painters algorithm (back to front)
		/*! This function should be overridden by custom widgets. The default implementation within
			the Element class draws nothing.
		*/
		virtual Render::RenderOperationList buildWidgetRenderOpList();

		//! This function will be called whenever an Element is attached to a hierarchy with a GUISheet root. \todo implement functionality guarantee
		virtual void handleAttach() {};
		//! This function will be called whenever an Element is detached from a hierarchy with a GUISheet root. \todo implement functionality guarantee
		virtual void handleDetach() {};

	

		//! Notifies the parent object (if there is one) that the Z order of this Element has somehow changed (either ZOrder is different, or AlwaysOnTop has been changed)
		void notifyElementParentZChange();

		//! Returns true is the point (in local coord space) is inside this Element.
		/*!
			The default operation simply checks the the point is greater than or equal to mElementRect.min
			and less than mElementRect.max. This is fine for Widgets that are axis aligned, rectangular shaped,
			and take up the entire space defined by mElementRect. Any Widget that supports rotation or is
			irregularly shaped should override this function and perform a more accurate point test.

			It is strongly recommended that (for the sake of speed) subclass Widgets perform a generic
			bounding box test before embarking on a more rigorous mathematical hit test. The likelihood
			that this function will be called often is quite high.
		*/
		virtual bool pointIsInside(const FVector2& localPoint);

		//! returns true if the given elementPtr identifies a descendant of this Element
		bool isDescendant(Element* elementPtr);
		//! returns true if the given elementName identifies a descendant of this Element
		bool isDescendant(std::string elementName);
		
		FRect mElementRect;
		int mZOrder;
		float mAlpha;
		bool mVisible;
		bool mDisabled;
		bool mAlwaysOnTop;

	private:
		//! \internal adds the current widget's renderoplist and all of its children's renderoplists to the given renderOpList
		void __buildRenderOperationList(Render::RenderOperationList& renderOpList);

		//! Returns the first lowest descendant Element that is under the given point in inner coord space of this Element.
		/*!
			This function recursively tests child Elements for the most accurate (lowest descendant)
			Element that contains the given point. The point is defined in inner coord space to \b this Element.

			\param innerPoint the point being tested
			\param activeOnly if true then only child elements that are not disabled will considered for the hit test
			\return a pointer to the descendant Element that most accurately holds the point, or 0 if none found.
			
			\note Before recursion into a child for more accuracy, the parent is responsible for
			converting the current value of the point into the inner coordinate space of the child
			about to be called.
		*/
		Element* _getDecendantElementAt(FVector2 innerPoint, const bool& activeOnly=true);

		//! Propagates an event using an event propagation list.
		/*!
			An event propagation lists is an ElementAncestryList.
			It is the responsibility of each receiver of this function call
			to remove itself from the top of the propagation list.
			If the result of _fireEventSubscribers() and the result
			of defaultEventHandler() are both true, then if the list is not
			yet empty, call the _propogateEvent() function
			of the next Element in the propagation list.

			\see buildElementAncestry()
		*/
		void _propogateEvent(Msg::Message& message, ElementAncestryList& propagationList);
		//! Propagates a global event by sending the event to all children.
		/*! This function should only be used if the Event has no destination,
			signifying that it is a global event.
		*/
		void _propogateGlobalEvent(const Msg::Message& message);

		//! Fires the event subscribers and returns true only if they all returned true, otherwise returns false.
		bool _fireMessageSubscribers(const Msg::Message& message);

		//! Builds an ancestry list starting with this Element.
		/*!
			An ElementAncestryList is a list of all Elements in a hierarchy
			that lead directly to the Element from which the ancestry was built.
			The list is specifically ordered, beginning with the root of the
			hierarchy, and ending with the Element from which this function
			was called.

			\note This is the primary method of building the path that
					events walk as they work toward their goal Element.

		*/
		void buildElementAncestry(ElementAncestryList& ancestryList);

		/*!
			This is a list of all children elements. Elements are guaranteed to be sorted by ZOrder
			in descending order. Items with a higher ZOrder are drawn on top, covering up lower ZOrder
			siblings. This will help ensure that mouse cursor position checking runs as quickly as
			possible, as the first good hit can be assumed to be the only important one, since other
			potential hits are visually covered by the first hit anyhow, and thus don't count.

			\warning Classes that extend OpenGUI by inheriting
			Elements that also inherit this class should never directly access this member variable
			if they are working across DLL boundaries. Doing so can cause problems. You've been warned.
			\see http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
		*/
		ChildElementList mChildrenElements;

		typedef std::list<Subscriber> SubscriberList;
		SubscriberList mSubscriberList;

		void _setElementName(std::string newName); //!< Sets the name of this Element. Users should never have a reason to use this function. \see mName \note This is implemented and used via function to ensure proper DLL linking
		void _setElementParent(Element* newParent); //!< Sets the parent of this Element. Users should never have a reason to use this function.  \note This is implemented and used via function for consistency with _setName()
		Element* mParentElement; //!< Pointer to the parent of this Element. \note This is not necessarily another Element! Do not assume that it is! \warning Modifying this is very dangerous. In a word: Don't.
		std::string mObjectName; //!< Holds the name of this object
	};
};
#endif
