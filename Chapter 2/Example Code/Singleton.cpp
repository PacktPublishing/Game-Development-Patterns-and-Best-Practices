#include "Singleton.h"
#include <string>

void HighScoreManager::CheckHighScore(int score)
{
	std::string toDisplay;

	if (highScore < score)
	{
		highScore = score;
		toDisplay = "\nNew High Score: " + std::to_string(score);
		printf(toDisplay.c_str());
	}
	else
	{
		toDisplay = "\nCurrent High Score: " + std::to_string(highScore);
		printf(toDisplay.c_str());
	}
}

