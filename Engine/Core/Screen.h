#ifndef SCREEN_H
#define SCREEN_H

#include <SDL3/SDL.h>

class Screen final
{
private:
	SDL_Window* _window = nullptr;
	SDL_GLContext _context = nullptr;

	SDL_Event _event{};

public:
	Screen() = default;

	bool open(int width, int height);
	void close();
	bool pollEvents();
	void swap();
};

#endif // !SCREEN_H