#pragma once

#include "raylib.h"

class Player
{
public:
	Player();
	~Player();

	void init();

	void update(float deltaTime, float windowHeight);
	void draw() const;
	void reset();

	void flap();
	Rectangle getCollisionRect() const;

private:
	Vector2 position;
	float velocityY;

	Texture2D texture;

	static constexpr Vector2 InitPos = { 100.0f, 300.0f };
	static constexpr float InitVelY = 0.0f;
	static constexpr float FlapStrength = -500.0f;
	static constexpr float Gravity = 1000.0f;
};