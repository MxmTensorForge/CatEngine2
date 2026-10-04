#include "Input.h"
#include "EngineConsts.h"

SDL_Window* Input::_window = nullptr;

std::bitset<KEY_COUNT> Input::_keys_down;
std::bitset<KEY_COUNT> Input::_keys_pressed;
std::bitset<KEY_COUNT> Input::_keys_released;

std::bitset<MOUSE_COUNT> Input::_mouse_down;
std::bitset<MOUSE_COUNT> Input::_mouse_pressed;
std::bitset<MOUSE_COUNT> Input::_mouse_released;

bool Input::_is_mouse_locked = false;
bool Input::_is_mouse_locked_user = false;
bool Input::_is_window_focus = false;

Mxm::Vec2 Input::_mouse_position{};
Mxm::Vec2 Input::_mouse_wheel{};
Mxm::Vec2 Input::_mouse_delta{};

Key Input::scancodeToKey(SDL_Scancode scancode) noexcept
{
	Key key;
	switch (scancode)
	{
	case SDL_SCANCODE_Q: key = Key::Q; break;
	case SDL_SCANCODE_W: key = Key::W; break;
	case SDL_SCANCODE_E: key = Key::E; break;
	case SDL_SCANCODE_R: key = Key::R; break;
	case SDL_SCANCODE_T: key = Key::T; break;
	case SDL_SCANCODE_Y: key = Key::Y; break;
	case SDL_SCANCODE_U: key = Key::U; break;
	case SDL_SCANCODE_I: key = Key::I; break;
	case SDL_SCANCODE_O: key = Key::O; break;
	case SDL_SCANCODE_P: key = Key::P; break;
	case SDL_SCANCODE_A: key = Key::A; break;
	case SDL_SCANCODE_S: key = Key::S; break;
	case SDL_SCANCODE_D: key = Key::D; break;
	case SDL_SCANCODE_F: key = Key::F; break;
	case SDL_SCANCODE_G: key = Key::G; break;
	case SDL_SCANCODE_H: key = Key::H; break;
	case SDL_SCANCODE_J: key = Key::J; break;
	case SDL_SCANCODE_K: key = Key::K; break;
	case SDL_SCANCODE_L: key = Key::L; break;
	case SDL_SCANCODE_Z: key = Key::Z; break;
	case SDL_SCANCODE_X: key = Key::X; break;
	case SDL_SCANCODE_C: key = Key::C; break;
	case SDL_SCANCODE_V: key = Key::V; break;
	case SDL_SCANCODE_B: key = Key::B; break;
	case SDL_SCANCODE_N: key = Key::N; break;
	case SDL_SCANCODE_M: key = Key::M; break;

	case SDL_SCANCODE_ESCAPE: key = Key::Escape; break;
	case SDL_SCANCODE_SPACE: key = Key::Space; break;
	case SDL_SCANCODE_LSHIFT: key = Key::Left_Shift; break;
	case SDL_SCANCODE_RSHIFT: key = Key::Right_Shift; break;
	case SDL_SCANCODE_TAB: key = Key::Tab; break;

	case SDL_SCANCODE_0: key = Key::Num_0; break;
	case SDL_SCANCODE_1: key = Key::Num_1; break;
	case SDL_SCANCODE_2: key = Key::Num_2; break;
	case SDL_SCANCODE_3: key = Key::Num_3; break;
	case SDL_SCANCODE_4: key = Key::Num_4; break;
	case SDL_SCANCODE_5: key = Key::Num_5; break;
	case SDL_SCANCODE_6: key = Key::Num_6; break;
	case SDL_SCANCODE_7: key = Key::Num_7; break;
	case SDL_SCANCODE_8: key = Key::Num_8; break;
	case SDL_SCANCODE_9: key = Key::Num_9; break;

	case SDL_SCANCODE_UP: key = Key::Up; break;
	case SDL_SCANCODE_DOWN: key = Key::Down; break;
	case SDL_SCANCODE_RIGHT: key = Key::Right; break;
	case SDL_SCANCODE_LEFT: key = Key::Left; break;
	case SDL_SCANCODE_RETURN: key = Key::Enter; break;

	case SDL_SCANCODE_F1: key = Key::F1; break;
	case SDL_SCANCODE_F2: key = Key::F2; break;
	case SDL_SCANCODE_F3: key = Key::F3; break;
	case SDL_SCANCODE_F4: key = Key::F4; break;
	case SDL_SCANCODE_F5: key = Key::F5; break;
	case SDL_SCANCODE_F6: key = Key::F6; break;
	case SDL_SCANCODE_F7: key = Key::F7; break;
	case SDL_SCANCODE_F8: key = Key::F8; break;
	case SDL_SCANCODE_F9: key = Key::F9; break;
	case SDL_SCANCODE_F10: key = Key::F10; break;
	case SDL_SCANCODE_F11: key = Key::F11; break;
	case SDL_SCANCODE_F12: key = Key::F12; break;

	case SDL_SCANCODE_BACKSLASH: key = Key::Backslash; break;
	case SDL_SCANCODE_BACKSPACE: key = Key::Backspace; break;

	default: return Key::None;
	}
	return key;
}

void Input::update()
{
	_keys_pressed.reset();
	_keys_released.reset();

	_mouse_pressed.reset();
	_mouse_released.reset();

	float posX{}, posY{};
	SDL_GetMouseState(&posX, &posY);
	_mouse_position = Mxm::Vec2(posX, posY);

	float deltaX{}, deltaY{};
	SDL_GetRelativeMouseState(&deltaX, &deltaY);
	_mouse_delta = Mxm::Vec2(deltaX, deltaY);

	_mouse_wheel = Mxm::Vec2();

	if (_is_mouse_locked) SDL_WarpMouseInWindow(_window, EngineConsts::STANDART_WIDTH * 0.5f, EngineConsts::STANDART_HEIGHT * 0.5f);

	if (_is_mouse_locked_user && _is_window_focus) _is_mouse_locked = true;
	else _is_mouse_locked = false;
}
void Input::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_EVENT_KEY_DOWN)
	{
	    if (event.key.repeat) return;
		
		Key key = scancodeToKey(event.key.scancode);
		if (key == Key::None) return;

		_keys_down[static_cast<size_t>(key)] = true;
		_keys_pressed[static_cast<size_t>(key)] = true;
	}
	else if (event.type == SDL_EVENT_KEY_UP)
	{
		Key key = scancodeToKey(event.key.scancode);
		if (key == Key::None) return;

		_keys_down[static_cast<size_t>(key)] = false;
		_keys_released[static_cast<size_t>(key)] = true;
	}
	else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
	{
		MouseButton button = static_cast<MouseButton>(event.button.button - 1);
		if (static_cast<size_t>(button) >= MOUSE_COUNT) return;

		_mouse_down[static_cast<size_t>(button)] = true;
		_mouse_pressed[static_cast<size_t>(button)] = true;
	}
	else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
	{
		MouseButton button = static_cast<MouseButton>(event.button.button - 1);
		if (static_cast<size_t>(button) >= MOUSE_COUNT) return;

		_mouse_down[static_cast<size_t>(button)] = false;
		_mouse_released[static_cast<size_t>(button)] = true;
	}
	else if (event.type == SDL_EVENT_MOUSE_WHEEL) {
		_mouse_wheel = Mxm::Vec2(event.wheel.x, event.wheel.y);
	}
	
	if (event.type == SDL_EVENT_WINDOW_FOCUS_LOST)
	{
		_is_window_focus = false;
		_keys_down.reset();
	}
	else if (event.type == SDL_EVENT_WINDOW_FOCUS_GAINED)
	{
		_is_window_focus = true;
	}
}

bool Input::isKeyDown(Key key) { return _keys_down[static_cast<size_t>(key)]; }
bool Input::isKeyPressed(Key key) { return _keys_pressed[static_cast<size_t>(key)]; }
bool Input::isKeyReleased(Key key) { return _keys_released[static_cast<size_t>(key)]; }

bool Input::isMouseButtonDown(MouseButton button) { return _mouse_down[static_cast<size_t>(button)]; }
bool Input::isMouseButtonPressed(MouseButton button) { return _mouse_pressed[static_cast<size_t>(button)]; }
bool Input::isMouseButtonReleased(MouseButton button) { return _mouse_released[static_cast<size_t>(button)]; }

void Input::setMouseLockState(bool state) {
	_is_mouse_locked_user = state;
	SDL_SetWindowRelativeMouseMode(_window, state);
}
bool Input::getMouseLockState() {
	return _is_mouse_locked_user;
}

const Mxm::Vec2& Input::getMousePosition() { return _mouse_position; }
const Mxm::Vec2& Input::getMouseWheel() { return _mouse_wheel; }
const Mxm::Vec2& Input::getMouseDelta() { return _mouse_delta; }
