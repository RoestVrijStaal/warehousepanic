#include <SFML/Graphics.hpp>

class conveyor : public random_class
{
    public:
        sf::Sprite arrow_0;
        sf::Sprite arrow_1;
        sf::Sprite arrow_2;
        short dir_amo;
        short speed;
        bool change;
        short dir;
};
