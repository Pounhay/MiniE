#include "SDL.h"
#include "StackAllocator.h"
#include <vector>
#include "lua.hpp"
#include "GameObject.h"
#include "Rect.h"
#include <assert.h>

class EngineManager
{
private:
	bool isRunning = false;

	StackAllocator* stack = new StackAllocator(MB * 10);
	SDL_Window* window;
	SDL_Renderer* renderer;
	lua_State* L = luaL_newstate();

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
		Lua();
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

	void Lua() {
		static int numberOfSpritesExisting = 0;

		struct Sprite
		{
			int x;
			int y;

			Sprite() : x(0), y(0)
			{
				numberOfSpritesExisting++;
			}

			~Sprite()
			{
				numberOfSpritesExisting--;
			}

			void Move(int velX, int velY)
			{
				x += velX;
				y += velY;
			}

			void Draw()
			{
				printf("sprite(%p): x = %d, y = %d\n", this, x, y);
			}
		};

		auto CreateRect = [](lua_State* L) -> int
		{
			void* pointerToARect = lua_newuserdata(L, sizeof(Rect));
			std::string N = lua_tostring(L, -3);
			lua_Number X = lua_tonumber(L, -2);
			lua_Number Y = lua_tonumber(L, -1);
			std::u32string s32(N.begin(), N.end());
			new (pointerToARect) Rect(s32,(int)X, (int)Y);
			luaL_getmetatable(L, "SpriteMetaTable");
			assert(lua_istable(L, -1));
			lua_setmetatable(L, -2);
			return 1;
		};

		auto DestroyRect = [](lua_State* L) -> int
		{
			Rect* sprite = (Rect*)lua_touserdata(L, -1);
			sprite->~Rect();
			return 0;
		};

		auto MoveRect = [](lua_State* L) -> int
		{
			Rect* sprite = (Rect*)lua_touserdata(L, -3);
			lua_Number velX = lua_tonumber(L, -2);
			lua_Number velY = lua_tonumber(L, -1);
			sprite->Update((int)velX, (int)velY);
			return 0;
		};

		auto DrawRect = [](lua_State* L) -> int
		{
			Rect* sprite = (Rect*)lua_touserdata(L, -1);
			sprite->Render();
			return 0;
		};

		L = lua_open();
		luaL_openlibs(L);
		lua_register(L, "CreateRect", CreateRect);
		lua_register(L, "DrawRect", DrawRect);
		lua_register(L, "MoveRect", MoveRect);
		lua_register(L, "DestroyRect", DestroyRect);
		luaL_dofile(L, "Test.lua");
		lua_close(L);

		assert(numberOfSpritesExisting == 0);
	}


};