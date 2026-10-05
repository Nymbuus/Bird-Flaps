#include "Pipe.h"
#include <iostream>

Pipe::Pipe(Texture2D* texture)
	: position{0.0f, 0.0f},
	  gapPosition{0.0f},
	  passed{false},
	  texture{texture}
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

	// Upper pipe:
	DrawTexturePro(
		*texture,
		Rectangle{0, 0, static_cast<float>(texture->width), -static_cast<float>(texture->height)},
		Rectangle{position.x, position.y - screenHeight + gapPosition, Width, screenHeight},
		Vector2{0, 0},
		0.0f,
		WHITE);

	// Lower pipe:
	DrawTexturePro(
		*texture,
		Rectangle{0, 0, static_cast<float>(texture->width), static_cast<float>(texture->height)},
		Rectangle{position.x, position.y + gapPosition + Gap, Width, static_cast<float>(texture->height)},
		Vector2{0, 0},
		0.0f,
		WHITE);
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

bool Pipe::isOffScreen() const
{
	return position.x <= -Width;
}

bool Pipe::hasBeenPassed() const
{
	return passed;
}

void Pipe::markAsPassed()
{
	passed = true;
}