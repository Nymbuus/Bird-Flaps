#include "Player.h"
#include <iostream>

Player::Player()
	: position{InitPos},
	  velocityY{0.0f}
{
}

void Player::update(float deltaTime, float windowHeight)
{
	velocityY += Gravity * deltaTime;
	position.y += velocityY * deltaTime;

	if (windowHeight - BirdRadius <= position.y)
	{
		position.y = windowHeight - BirdRadius;
		velocityY = 0.0f;
	}

	if (position.y <= BirdRadius)
	{
		position.y = BirdRadius;
		velocityY = 0.0f;
	}
}

void Player::draw() const
{
	DrawCircle(
		static_cast<int>(position.x),
		static_cast<int>(position.y),
		static_cast<int>(BirdRadius),
		YELLOW);
}

void Player::reset()
{
	position = InitPos;
}

void Player::flap()
{
	velocityY = FlapStrength;
}

Rectangle Player::getCollisionRect() const
{
	return Rectangle{
		position.x - BirdRadius,
		position.y - BirdRadius,
		BirdRadius * 2.0f,
		BirdRadius * 2.0f,
	};
}