// MinE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "EngineManager.h"
#include "INIReader.h"
#include <ctime>

int main(int argc, char* argv[])
{
	srand(time(NULL));
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	StackAllocator* stack = new StackAllocator(MB * 10);
	EngineManager* engine = (EngineManager*)stack->alloc(sizeof(EngineManager));

	INIReader reader("System Config.ini");
	
	if (reader.ParseError() < 0) {
		std::cout << "Can't load ini file\n";
		return -1;
	}

	int wheight = reader.GetInteger("system", "wheight", 0);
	int wwidth = reader.GetInteger("system", "wwidth", 0);


	engine->Init("EngineWindow", wwidth, wheight, false);

	while (engine->Running())
	{
		frameStart = SDL_GetTicks();

		engine->HandleEvents();
		engine->Update();
		engine->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	engine->Clean();
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
