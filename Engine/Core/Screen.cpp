#include "Screen.h"
#include "Logger.h"
#include "../Core/Input.h"

#include <glad/glad.h>

bool Screen::open(int width, int height) {
	if (!SDL_Init(SDL_INIT_VIDEO)) 
		return false;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	_window = SDL_CreateWindow("main", width, height, SDL_WINDOW_OPENGL);
	if (!_window) {
		Logger::getInstance().log(LogType::Fatal, "Window creation error [sdl error]");
		return false;
	}
	Logger::getInstance().log(LogType::Message, "Window created successfully");

	_context = SDL_GL_CreateContext(_window);
	SDL_GL_MakeCurrent(_window, _context);
	Logger::getInstance().log(LogType::Message, "Context created successfully");

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		Logger::getInstance().log(LogType::Fatal, "Glad init error");
	}

	SDL_GL_SetSwapInterval(0);

	Input::setWindow(_window);

	return true;
}
void Screen::close() {
	SDL_DestroyWindow(_window);
	SDL_GL_DestroyContext(_context);

	SDL_Quit();
}
bool Screen::pollEvents() {
	while (SDL_PollEvent(&_event)) {
		if (_event.type == SDL_EVENT_QUIT) return false;
		Input::handleEvent(_event);
	}
	return true;
}
void Screen::swap() {
	SDL_GL_SwapWindow(_window);
}
