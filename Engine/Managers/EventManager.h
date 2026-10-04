#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <string>
#include <vector>

class EventManager final
{
private:
	std::vector<std::string> _events;

	EventManager() = default;
	~EventManager() = default;
public:
	EventManager(const EventManager&) = delete;
	EventManager& operator=(const EventManager&) = delete;
	EventManager(EventManager&&) = delete;
	EventManager& operator=(EventManager&&) = delete;

	static EventManager& getInstance() noexcept;

	void broadcast(const std::string& event);
	bool poll(const std::string& event);
};

#endif // !EVENTMANAGER_H
