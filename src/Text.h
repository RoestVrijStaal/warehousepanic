#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <SFML/Graphics.hpp>



class Text
{
	public:
		enum Size { SMALL = 0, MEDIUM, LARGE, count };

		Text( std::string newtext = " ", float x = 0, float y = 0, Size newsize = SMALL );
		virtual ~Text();

		void SetText( std::string newtext );
		void SetPosition( sf::Vector2f& newpos );
		void SetPosition( float x, float y );
		void SetSize( Size newsize );
		sf::Rect<float> GetRect();

		void Draw();

	protected:
		std::string text;
		sf::Vector2f pos;
		Size size;

	private:
};

#endif // TEXT_H
