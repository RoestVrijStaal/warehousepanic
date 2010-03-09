#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <SFML/Graphics.hpp>



class Text : public std::string
{
	public:
		Text();
		virtual ~Text();

		void SetPosition( sf::Vector2f& pos );

	protected:
		sf::Vector2f pos;

	private:
};

#endif // TEXT_H
