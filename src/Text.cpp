#include "Text.h"

#include "Functions.h"

Text::Text( std::string newtext, float x, float y, Size newsize ) :
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

void Text::SetPosition( gdn::Vector2f& newpos )
{
	pos = newpos;
}

void Text::SetPosition( float x, float y )
{
	pos.x = x;
	pos.y = y;
}

const gdn::Vector2f& Text::GetPosition()
{
	return pos;
}

void Text::SetSize( Size newsize )
{
    if ( newsize == SMALL or newsize == MEDIUM or newsize == LARGE )
    {
        size = newsize;
    }
}

int Text::GetWidth()
{
	int width = 0;

	// Prepare string
	std::string character = "A ";
	switch ( size )
	{
		case SMALL: character.append( "small" ); break;
		case MEDIUM: character.append( "medium" ); break;
		case LARGE: character.append( "large" ); break;
		default: break;
	}

	for ( std::string::iterator it = text.begin(); it != text.end(); ++it )
	{
		// Replace first character and get image
		character[0] = *it;
		gdn::Image& img = ResMgr.GetImage( character );

		switch ( size )
		{
			case SMALL: width += img.GetWidth() - 1; break;
			case MEDIUM: width += img.GetWidth() - 2; break;
			case LARGE: width += img.GetWidth() - 3; break;
			default: break;
		}
	}
	return width;
}

void Text::Draw()
{
	gdn::RenderWindow& window = App.GetWindow();

	gdn::Sprite sprite;
	int charOffset = 0;

	// Prepare string
	std::string character = "A ";
	switch ( size )
	{
		case SMALL: character.append( "small" ); break;
		case MEDIUM: character.append( "medium" ); break;
		case LARGE: character.append( "large" ); break;
		default: break;
	}

	for ( std::string::iterator it = text.begin(); it != text.end(); ++it )
	{
		// Replace first character and get image
		character[0] = *it;

		// Fix for lack of lower case chars (at the moment)
		if ( character[0] >= 97 and character[0] <= 122 )
			character[0] -= 32; // Make upper case
		gdn::Image& img = ResMgr.GetImage( character );

		sprite = gdn::Sprite( img );
		sprite.SetPosition( pos.x + charOffset, pos.y );
		window.Draw( sprite );

		switch ( size )
		{
			case SMALL: charOffset += img.GetWidth() - 1; break;
			case MEDIUM: charOffset += img.GetWidth() - 2; break;
			case LARGE: charOffset += img.GetWidth() - 3; break;
			default: break;

		}
	}
}
