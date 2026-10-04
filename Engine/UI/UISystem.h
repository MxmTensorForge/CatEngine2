#ifndef UISYSTEM_H
#define UISYSTEM_H

#include "UIScreen.h"

#include <utility>
#include <unordered_map>
#include <memory>
#include <string>

class UISystem final
{
private:
	std::unordered_map<std::string, std::unique_ptr<UIScreen>> _screens;
	UIScreen* _currentScreen = nullptr;

	UISystem() = default;
	~UISystem() = default;
public:
	UISystem(const UISystem&) = delete;
	UISystem& operator=(const UISystem&) = delete;
	UISystem(UISystem&&) = delete;
	UISystem& operator=(UISystem&&) = delete;

	static UISystem& getInstance() {
		static UISystem sys;
		return sys;
	}

	void newFrame();
	void render(UIRenderer* renderer);
	UIScreen* addScreen(const std::string& name);

	void setCurrentScreen(const std::string& name);
	UIScreen* getCurrentScreen();
	UIScreen* getScreen(const std::string& name);
};

#endif // !UISYSTEM_H
