class random_class
{
    public:
        random_class() : change(false), active(false), dir(0), dir_amo(0) {}
        sf::Sprite sprite;
        sf::Sprite arrow_0;
        sf::Sprite arrow_1;
        sf::Sprite arrow_2;
        bool change;
        bool active;
        short dir;
        short dir_amo;
        short speed;
        int value;
        int intervalmax;
        int interval;
        int delay;
        std::vector<std::string> colors;
        std::string color;
};
