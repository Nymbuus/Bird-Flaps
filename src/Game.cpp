#include "Game.h"
#include "raylib.h"
#include <iostream>

Game::Game()
	: gameState{GameState::Playing},
	  pipeSpawner{0.0f}
{
	InitWindow(width, height, "Bird Flaps");
	SetTargetFPS(60);

	pipes.emplace_back();
	pipes.back().init(width, height);
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

	if (!pipes.empty())
	{
		if (pipes.front().isOffScreen())
		{
			pipes.erase(pipes.begin());
		}
	}

	float deltaTime = GetFrameTime();

	pipeSpawner += deltaTime;
	if (pipeSpawner >= 1.3f)
	{
		pipes.emplace_back();
		pipes.back().init(width, height);
		pipeSpawner = 0.0f;
	}

	player.update(deltaTime, height);
	for (Pipe& pipe : pipes)
	{
		pipe.update(deltaTime);
	}

	if (CheckCollisionRecs(player.getCollisionRect(), pipes.front().getUpperCollisionRect()) ||
		CheckCollisionRecs(player.getCollisionRect(), pipes.front().getLowerCollisionRect(height)))
		gameState = GameState::GameOver;
}

void Game::render()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	DrawText(
		"Bird Flaps",
		(GetScreenWidth() / 2) - 100,
		10,
		fontSize,
		BLACK);

	player.draw();
	for (Pipe& pipe : pipes)
	{
		pipe.draw();
	}


	if (gameState == GameState::GameOver)
	{
		DrawText("FLAP OVER", (width / 2) - 100.0f, height / 2, fontSize, RED);
		DrawText("PRESS SPACE TO RESTART", (width / 2) - 155.0f, (height / 2) + fontSize, fontSize - 10, BLACK);
	}

	EndDrawing();
}