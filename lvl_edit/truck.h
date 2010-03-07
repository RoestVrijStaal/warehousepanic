#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class truck : public random_class
{
    public:
        int intervalmax;
        int interval;
        int delay;
        std::vector<std::string> colors;
        bool active;

};
