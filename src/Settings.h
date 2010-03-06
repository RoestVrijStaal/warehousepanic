#ifndef SETTTINGS_H
#define SETTTINGS_H



#include <string>

namespace Dir
{
	enum Direction { RIGHT = 0, UP, LEFT, DOWN }; // Directions corrispond to unit circle
};

namespace GameColor
{
	enum ColorType { BLUE = 0, GREEN, ORANGE, PURPLE, RED, YELLOW, count }; // Don't use colorCount
	std::string name[] = { "blue", "green", "orange", "purple", "red", "yellow" };
}

// "Perspective" point, i.e. the point to which we measure distance for sorting drawing order
const sf::Vector2f SORT_POINT(18,0);


#endif // SETTTINGS_H
