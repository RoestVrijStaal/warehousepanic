#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "WCEngine/GDN.h"


class Text
{
	public:
		enum Size { SMALL = 0, MEDIUM, LARGE, count };

		Text( std::string newtext = " ", float x = 0, float y = 0, Size newsize = SMALL );
		virtual ~Text();

		void SetText( std::string newtext );
		void SetPosition( gdn::Vector2f& newpos );
		void SetPosition( float x, float y );
		const gdn::Vector2f& GetPosition();
		void SetSize( Size newsize );
		int GetWidth();

		void Draw();

	protected:
		std::string text;
		gdn::Vector2f pos;
		Size size;

	private:
};

#endif // TEXT_H
