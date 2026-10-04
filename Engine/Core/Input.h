#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL.h>
#include <bitset>

#include "../Mxm/Vec2.h"

enum class Key
{
	None,
	Q, W, E, R, T, Y, U, I, O, P, A, S, D, F, G, H, J, K, L, Z, X, C, V, B, N, M,
	Escape, Space, Left_Shift, Right_Shift, Tab,
	Num_0, Num_1, Num_2, Num_3, Num_4, Num_5, Num_6, Num_7, Num_8, Num_9,
	Up, Down, Right, Left, Enter,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	Backspace, Backslash,
	Max
};
constexpr size_t KEY_COUNT = static_cast<size_t>(Key::Max);

enum class MouseButton
{
	MOUSE0 = 0,
	MOUSE1 = 1,
	MOUSE2 = 2,
	MOUSE3 = 3,
	MOUSE4 = 4,
	Max
};
constexpr size_t MOUSE_COUNT = static_cast<size_t>(MouseButton::Max);

class Input final
{
private:
	static SDL_Window* _window;
	inline static void setWindow(SDL_Window* window) { _window = window; }

	static std::bitset<KEY_COUNT> _keys_down;
	static std::bitset<KEY_COUNT> _keys_pressed;
	static std::bitset<KEY_COUNT> _keys_released;

	static std::bitset<MOUSE_COUNT> _mouse_down;
	static std::bitset<MOUSE_COUNT> _mouse_pressed;
	static std::bitset<MOUSE_COUNT> _mouse_released;

	static Key scancodeToKey(SDL_Scancode scancode) noexcept;

	static Mxm::Vec2 _mouse_position;
	static Mxm::Vec2 _mouse_wheel;
	static Mxm::Vec2 _mouse_delta;

	static bool _is_mouse_locked;
	static bool _is_mouse_locked_user;
	static bool _is_window_focus;

	static void update();
	static void handleEvent(const SDL_Event& event);

	friend class Application;
	friend class Screen;
public:
	Input() = delete;
	~Input() = delete;

	static bool isKeyDown(Key key);
	static bool isKeyPressed(Key key);
	static bool isKeyReleased(Key key);

	static bool isMouseButtonDown(MouseButton key);
	static bool isMouseButtonPressed(MouseButton key);
	static bool isMouseButtonReleased(MouseButton key);

	static void setMouseLockState(bool state);
	static bool getMouseLockState();

	static const Mxm::Vec2& getMousePosition();
	static const Mxm::Vec2& getMouseWheel();
	static const Mxm::Vec2& getMouseDelta();
};

#endif
