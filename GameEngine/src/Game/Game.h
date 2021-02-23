#pragma once
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

constexpr auto FRAMERATE = 5;
constexpr auto MS_PER_FRAME = 1000 / FRAMERATE;

class Game
{
private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	bool isRunning;
	int msPreviousFrame;
	double deltaTime;

public:
	Game();
	~Game();
	void Initialize();
	void Run();
	void Setup();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();
};

