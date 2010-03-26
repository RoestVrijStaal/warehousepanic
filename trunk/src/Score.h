#include <string>

struct Score
{
    Score( int newscore, std::string newname) : score(newscore), name(newname) {};
    int score;
    std::string name;
};

bool ScoreSort(Score* first, Score* second)
{
	return first->score > second->score;
}
