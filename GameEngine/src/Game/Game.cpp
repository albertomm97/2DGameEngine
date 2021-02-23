#include "Game.h"
#include "../Logger/Logger.h"

#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>

Game::Game()
{
	msPreviousFrame = 0;
	Logger::Warn("Some class members not initialized\n");
}

Game::~Game()
{
}

void Game::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Logger::Error("Error Initializing SDL\n");
		return;
	}
	
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280,
		720,
		0
	);
	if (!window)
	{
		Logger::Error("Error creating SDL Window\n");
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		Logger::Error("Error creating SDL Renderer\n");
		return;
	}

	isRunning = true;

	Logger::Log("SDL Initialized correctly\n");
}

void Game::Run()
{
	Setup();
	while (isRunning)
	{
		ProcessInput();
		Update();
		Render();
	}
}

glm::vec2 playerPos;
glm::vec2 playerVel;

void Game::Setup()
{
	playerPos = glm::vec2(10.0f, 20.0f);
	playerVel = glm::vec2(50.0f, 30.0f);
	Logger::Log("Game Setup complete\n");
}

void Game::ProcessInput()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
				{
					isRunning = false;
				}
				break;
		}
	}
}

void Game::Update()
{
	int timeToWait = MS_PER_FRAME - (SDL_GetTicks() - msPreviousFrame);
	if (timeToWait > 0 && timeToWait <= MS_PER_FRAME)
		SDL_Delay(timeToWait);
	
	deltaTime = (SDL_GetTicks() - msPreviousFrame) / 1000.0f;
	
	msPreviousFrame = SDL_GetTicks();

	playerPos.x += playerVel.x * deltaTime;
	playerPos.y += playerVel.y * deltaTime;
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0);
	SDL_RenderClear(renderer);

	// Draw things
	SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_Rect destRect = { playerPos.x, playerPos.y, 32, 32 };
	
	SDL_RenderCopy(renderer, texture, NULL, &destRect);
	SDL_DestroyTexture(texture);

	SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
