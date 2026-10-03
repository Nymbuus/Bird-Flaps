#include "Game.h"
#include "raylib.h"
#include <iostream>

Game::Game()
	: gameState{GameState::Playing},
	  pipeSpawner{0.0f},
	  playerPosX{player.getCollisionRect().x}
{
	InitWindow(width, height, "Bird Flaps");
	SetTargetFPS(60);

	pipes.emplace_back();
	pipes.back().init(width, height);

	score.init(width);
}

void Game::run()
{
	while (!WindowShouldClose())
	{
		processInput();
		update();
		render();
	}

	CloseWindow();
}

void Game::processInput()
{
	if (gameState == GameState::GameOver)
		if (IsKeyPressed(KEY_SPACE))
		{
			std::cout << "Restart!!" << std::endl;

			player.reset();
			pipes.clear();
			pipes.emplace_back();
			pipes.back().init(width, height);
			pipeSpawner = 0.0f;
			score.reset();

			gameState = GameState::Playing;
		}

	if (gameState != GameState::Playing)
		return;

	if (IsKeyPressed(KEY_SPACE))
		player.flap();
}

void Game::update()
{
	if (gameState != GameState::Playing)
		return;

	float deltaTime = GetFrameTime();

	updatePlayer(deltaTime);
	updatePipes(deltaTime);
	checkPositionInteractions();
}

void Game::render()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	player.draw();
	for (Pipe& pipe : pipes)
	{
		pipe.draw();
	}

	score.draw();

	if (gameState == GameState::GameOver)
	{
		DrawText("FLAP OVER", (width / 2) - 100.0f, height / 2, fontSize, RED);
		DrawText("PRESS SPACE TO RESTART", (width / 2) - 155.0f, (height / 2) + fontSize, fontSize - 10, BLACK);
	}

	EndDrawing();
}

void Game::updatePlayer(float deltaTime)
{
	player.update(deltaTime, height);
	for (Pipe& pipe : pipes)
	{
		pipe.update(deltaTime);
	}
}

void Game::updatePipes(float deltaTime)
{
	if (!pipes.empty())
	{
		if (pipes.front().isOffScreen())
		{
			pipes.erase(pipes.begin());
		}
	}

	pipeSpawner += deltaTime;
	if (pipeSpawner >= 1.3f)
	{
		pipes.emplace_back();
		pipes.back().init(width, height);
		pipeSpawner = 0.0f;
	}
}

void Game::checkPositionInteractions()
{
	if (!pipes.empty())
	{
		if (CheckCollisionRecs(player.getCollisionRect(), pipes.front().getUpperCollisionRect()) ||
			CheckCollisionRecs(player.getCollisionRect(), pipes.front().getLowerCollisionRect(height)))
			gameState = GameState::GameOver;

		if (playerPosX >= pipes.front().getUpperCollisionRect().x &&
			!pipes.front().hasBeenPassed())
		{
			score.addPoint();
			pipes.front().markAsPassed();
		}
	}
}