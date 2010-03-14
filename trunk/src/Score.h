#include <string>

struct Score
{
    Score( int newscore, std::string newname) : score(newscore), name(newname) {};
    int score;
    std::string name;
};
