
#include "SDL.h"
#include "StackAllocator.h"
#include <vector>

class EngineManager
{
private:
	bool isRunning = false;

	SDL_Window* window;
	SDL_Renderer* renderer;

public:	
	EngineManager()
	{}

	~EngineManager()
	{}

	void Init(const char* title, int width, int height, bool fullscreen)
	{
		int flags = 0;

		if (fullscreen)
			flags = SDL_WINDOW_FULLSCREEN;
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{
			window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer)
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

			isRunning = true;
		}
	}

	void HandleEvents()
	{
	}

	void Update()
	{
	}

	void Render()
	{
	}

	void Clean()
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}
	bool Running() { return isRunning; }
	void Quit() { isRunning = false; }
};