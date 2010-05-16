#ifndef IMAGE_H
#define IMAGE_H

#include <string>

class SDL_Surface;

namespace gdn
{
	class Image
	{
		public:
			Image();
			virtual ~Image();
			bool LoadFromFile( std::string filename, bool useAlpha = false );

			int GetWidth();
			int GetHeight();

			SDL_Surface* GetTexture();

		protected:
		private:
			SDL_Surface* texture;
	};
}

#endif // IMAGE_H
