#ifndef Amethyst_Theme_h__
#define Amethyst_Theme_h__

#include "OpenGUI.h"
#include "Amethyst_Exports.h"

namespace OpenGUI {
	namespace Amethyst {

		class AMETHYST_API StateImage {
		public:
			StateImage() {}
			StateImage( ImageryPtr imagery ): mIsFace( false ), mImagery( imagery ) {}
			StateImage( FacePtr face ): mIsFace( true ), mFace( face ) {}
			~StateImage() {}
			void draw( const FRect& rect, Brush& brush ) const {
				if ( mIsFace )
					brush.Image.drawFace( mFace, rect );
				else
					brush.Image.drawImage( mImagery, rect );
			}
		private:
			bool mIsFace;
			ImageryPtr mImagery;
			FacePtr mFace;
		};

		class AMETHYST_API WidgetTheme {
		public:
			WidgetTheme() {
				/**/
			}
			~WidgetTheme() {
				/**/
			}
			
			void drawStateImage( const std::string& stateName, const FRect& rect, Brush& brush ) const {
				( mStateImageMap.find( stateName ) )->second.draw( rect, brush );
			}
			typedef std::map<std::string, StateImage> StateImageMap;
			StateImageMap mStateImageMap;

			const Value& getValue( const std::string& name, const Value& defaultValue ) const {
				ValueMap::const_iterator iter = mValueMap.find( name );
				if ( iter == mValueMap.end() )
					return defaultValue;
				return iter->second;
			}
			typedef std::map<std::string, Value> ValueMap;
			ValueMap mValueMap;
		};

		class AMETHYST_API Theme {
		public:
			Theme() {}
			~Theme() {}
			void drawWidgetStateImage( const std::string& widgetName, const std::string& stateName, const FRect& rect, Brush& brush ) const {
				( mWidgetThemeMap.find( widgetName ) )->second.drawStateImage( stateName, rect, brush );
			}

			typedef std::map<std::string, WidgetTheme> WidgetThemeMap;
			WidgetThemeMap mWidgetThemeMap;
		};

	} // namespace Amethyst{
} // namespace OpenGUI{

#endif // Amethyst_Theme_h__
