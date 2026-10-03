#include "Score.h"

Score::Score()
	: position{0.0f, 10.0f},
	  totalPoints{0},
	  fontSize{30.0f}
{
}

void Score::init(float windowWidth)
{
	position.x = (windowWidth / 2) - 65.0f;
}

void Score::draw() const
{
	std::string scoreText = "SCORE: " + std::to_string(totalPoints);

	DrawText(
		scoreText.c_str(),
		position.x,
		position.y,
		fontSize,
		BLACK);
}

void Score::addPoint()
{
	totalPoints++;
}

void Score::reset()
{
	totalPoints = 0;
}