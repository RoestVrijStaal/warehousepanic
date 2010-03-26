#ifndef VECTOR2F_H
#define VECTOR2F_H


namespace gdn
{
	class Vector2f
	{
		public:
			Vector2f();
			Vector2f( float newx, float newy );
			virtual ~Vector2f();

			float x;
			float y;

		protected:
		private:
	};
}

#endif // VECTOR2F_H
