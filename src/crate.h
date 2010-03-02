#include <SFML/Graphics.hpp>
#include <string>

class crate
{
    public:
        sf::Sprite sprite;
        sf::Vector2i tomove;
        bool incint;
        bool coll;
        std::string color;
};
