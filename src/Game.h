#pragma once

#include "Player.h"
#include "Pipe.h"
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

	Player player;

	GameState gameState;

	std::vector<Pipe> pipes;
	float pipeSpawner;

	static constexpr int width = 800;
	static constexpr int height = 600;
	static constexpr int fontSize = 30;
};