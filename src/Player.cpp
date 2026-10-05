#include "Player.h"
#include <iostream>

Player::Player()
	: position{InitPos},
	  velocityY{InitVelY},
	  texture{ }
{
}

void Player::init()
{
	texture = LoadTexture("assets/bird.png");
}

void Player::update(float deltaTime, float windowHeight)
{
	velocityY += Gravity * deltaTime;
	position.y += velocityY * deltaTime;

	if (windowHeight <= position.y + (texture.height / 2))
	{
		position.y = windowHeight - (texture.height / 2);
		velocityY = 0.0f;
	}

	if (position.y <= texture.height / 2)
	{
		position.y = texture.height / 2;
		velocityY = 0.0f;
	}
}

void Player::draw() const
{
	DrawTexture(
		texture,
		static_cast<int>(position.x - (texture.width / 2)),
		static_cast<int>(position.y - (texture.height / 2)),
		WHITE);
}

void Player::reset()
{
	position = InitPos;
	velocityY = InitVelY;
}

void Player::flap()
{
	velocityY = FlapStrength;
}

Rectangle Player::getCollisionRect() const
{
	return Rectangle{
		position.x - (texture.width / 2),
		position.y - (texture.height / 2),
		static_cast<float>(texture.width),
		static_cast<float>(texture.height),
	};
}

Player::~Player()
{
	UnloadTexture(texture);
}