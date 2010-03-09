#include "Text.h"


#include "Functions.h"


Text::Text( std::string newtext, int x, int y, Size newsize ) :
	text( newtext ),
	pos( x, y ),
	size( newsize )
{
}

Text::~Text()
{
}

void Text::SetText( std::string newtext )
{
	text = newtext;
}

void Text::SetPosition( sf::Vector2f& newpos )
{
	pos = newpos;
}

void Text::Draw()
{
/*	sf::RenderWindow& w = App.GetWindow();

	sf::Sprite sprite;

	for ( std::string::iterator it = text.begin(); it != text.end(); ++it )
	{
		std::string character = std::string( *it );
		sprite.SetImage( ResMgr.GetImage( "" );
	}*/
}
