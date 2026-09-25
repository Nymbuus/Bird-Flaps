#include "Pipe.h"
#include <iostream>

Pipe::Pipe()
	: position{0.0f, 0.0f},
	  gapPosition{0.0f}
{
}

void Pipe::init(int windowWidth, int windowHeight)
{
	position.x = windowWidth;
	gapPosition = static_cast<float>(GetRandomValue(gapBorderOffset, windowHeight - gapBorderOffset - Gap));
}

void Pipe::draw() const
{
	float screenHeight = GetScreenHeight();

	DrawRectangle(
		static_cast<int>(position.x),
		static_cast<int>(position.y - screenHeight + gapPosition),
		Width,
		screenHeight,
		GREEN);

	DrawRectangle(
		static_cast<int>(position.x),
		static_cast<int>(position.y + gapPosition + Gap),
		Width,
		screenHeight,
		GREEN);
}

void Pipe::update(float deltaTime)
{
	position.x += VelocityX * deltaTime;
}

Rectangle Pipe::getUpperCollisionRect() const
{
	return Rectangle{
		position.x,
		0.0f,
		Width,
		gapPosition
	};
}

Rectangle Pipe::getLowerCollisionRect(int windowHeight) const
{
	return Rectangle{
		position.x,
		gapPosition + Gap,
		Width,
		static_cast<float>(windowHeight)
	};
}

bool Pipe::isOffScreen()
{
	if (position.x <= -Width)
		return true;
	else
		return false;
}