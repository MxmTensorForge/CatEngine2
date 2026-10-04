#include "UISystem.h"

void UISystem::newFrame() {
	if (!_currentScreen) return;
	_currentScreen->update();
}
void UISystem::render(UIRenderer* renderer) {
	if (!_currentScreen) return;
	_currentScreen->render(renderer);
}
UIScreen* UISystem::addScreen(const std::string& name) {
	auto screen = std::make_unique<UIScreen>();
	UIScreen* ptr = screen.get();
	_screens[name] = std::move(screen);
	return ptr;
}

void UISystem::setCurrentScreen(const std::string& name) {
	auto screen = _screens.find(name);
	if (screen != _screens.end()) {
		_currentScreen = screen->second.get();
		return;
	}
	_currentScreen = nullptr;
}
UIScreen* UISystem::getCurrentScreen() {
	return _currentScreen;
}
UIScreen* UISystem::getScreen(const std::string& name) {
	auto screen = _screens.find(name);
	if (screen != _screens.end()) {
		return screen->second.get();
	}
	return nullptr;
}
