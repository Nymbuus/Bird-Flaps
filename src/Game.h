#pragma once

#include "Player.h"
#include "Pipe.h"
#include "Score.h"
#include <vector>

enum class GameState
{
	Playing,
	GameOver
};

class Game
{
public:
	Game();

	void run();

private:
	void processInput();
	void update();
	void render();

	void updatePlayer(float deltaTime);
	void updatePipes(float deltaTime);
	void checkPositionInteractions();

	Player player;
	Score score;

	GameState gameState;

	std::vector<Pipe> pipes;
	float pipeSpawner;
	float playerPosX;

	static constexpr int width = 800;
	static constexpr int height = 600;
	static constexpr int fontSize = 30;
};