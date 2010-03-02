#include <SFML/Graphics.hpp>

class conveyor
{
    public:
        sf::Sprite sprite;
        sf::Sprite arrow_0;
        sf::Sprite arrow_1;
        sf::Sprite arrow_2;
        short dir_amo;
        short dir;
        bool change;
        short speed;
};
