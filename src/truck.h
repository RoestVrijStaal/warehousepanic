#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class truck
{
    public:
        sf::Sprite sprite;
        int intervalmax;
        int interval;
        int delay;
        std::vector<std::string> colors;
        bool active;
};
