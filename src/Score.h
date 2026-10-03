#pragma once

#include "raylib.h"
#include <string>

class Score
{
public:
	Score();

	void draw() const;

	void init(float windowWidth);

	void addPoint();
	void reset();

private:
	Vector2 position;
	int totalPoints;
	float fontSize;
};