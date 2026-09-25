#pragma once

#include "raylib.h"

class Pipe
{
public:
	Pipe();

	void init(int windowWidth, int windowHeight);
	void draw() const;
	void update(float deltaTime);

	Rectangle getUpperCollisionRect() const;
	Rectangle getLowerCollisionRect(int windowHeight) const;

	bool isOffScreen();

private:
	Vector2 position;
	float gapPosition;

	static constexpr float Gap = 200.0f;
	static constexpr int gapBorderOffset = 50;
	static constexpr float Width = 60.0f;
	static constexpr float VelocityX = -300.0f;
};