#include "Player.h"
#include <iostream>

Player::Player()
	: position{InitPos},
	  velocityY{InitVelY},
	  texture{ },
	  rotation{InitRot}
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
	DrawTexturePro(
		texture,
		Rectangle(0, 0, texture.width, texture.height),
		Rectangle(position.x, position.y,  texture.width, texture.height),
		Vector2(texture.width / 2, texture.height / 2),
		rotation,
		WHITE
	);
}

void Player::reset()
{
	position = InitPos;
	velocityY = InitVelY;
	rotation = InitRot;
}

void Player::flap()
{
	velocityY = FlapStrength;
}

void Player::rotateClockwise(float deltaTime)
{
	rotation += RotationSpeed * deltaTime;
}

void Player::rotateAntiClockwise(float deltaTime)
{
	rotation -= RotationSpeed * deltaTime;
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