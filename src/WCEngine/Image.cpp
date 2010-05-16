#include "Image.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


namespace gdn
{
	Image::Image() : texture( NULL )
	{
	}

	Image::~Image()
	{
		if ( texture )
		{
			SDL_FreeSurface( texture );
		}
	}

	bool Image::LoadFromFile( std::string filename, bool useAlpha )
	{
		if ( texture )
		{
			SDL_FreeSurface( texture );
			texture = NULL;
		}

		SDL_Surface* loadedImage = IMG_Load( filename.c_str() );
		if ( useAlpha )
		{
			texture = loadedImage;
		}
		else if ( loadedImage )
		{
			// Optimize image for display surface
			texture = SDL_DisplayFormat( loadedImage );
			SDL_FreeSurface( loadedImage );
			if ( texture )
			{
				// Set all pixels of color R 0xFF, G 0, B 0xFF to be transparent
				SDL_SetColorKey( texture, SDL_SRCCOLORKEY, SDL_MapRGB( texture->format, 0xFF, 0, 0xFF ) );
			}
		}
		return texture != NULL;
	}

	int Image::GetWidth()
	{
		if ( texture )
			return texture->w;
		return 0;
	}

	int Image::GetHeight()
	{
		if ( texture )
			return texture->h;
		return 0;
	}

	SDL_Surface* Image::GetTexture()
	{
		return texture;
	}
}
