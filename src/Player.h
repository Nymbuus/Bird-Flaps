#pragma once

#include "raylib.h"

class Player
{
public:
	Player();

	void update(float deltaTime, float windowHeight);
	void draw() const;
	void reset();

	void flap();
	Rectangle getCollisionRect() const;

private:
	Vector2 position;
	float velocityY;

	static constexpr Vector2 InitPos = { 100.0f, 300.0f };
	static constexpr float FlapStrength = -500.0f;
	static constexpr float Gravity = 1000.0f;
	static constexpr float BirdRadius = 20.0f;
};