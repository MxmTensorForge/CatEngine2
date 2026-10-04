#include "EventManager.h"

#include <algorithm>

EventManager& EventManager::getInstance() noexcept {
	static EventManager es;
	return es;
}

void EventManager::broadcast(const std::string& event) {
	if (std::find(_events.begin(), _events.end(), event) == _events.end()) {
		_events.push_back(event);
	}
}
bool EventManager::poll(const std::string& event) {
	auto e = std::find(_events.begin(), _events.end(), event);
	if (e == _events.end()) return false;

	_events.erase(e);
	return true;
}
