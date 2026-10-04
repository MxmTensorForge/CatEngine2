#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>

class GameObject;

class Component
{
private:
	GameObject* _object = nullptr;
	bool _isStarted = false;
public:
	virtual ~Component() = default;

	virtual void init() {}
	virtual void start() {}
	virtual void update() {}
	virtual void fixedUpdate() {}

	void setObject(GameObject* object) noexcept { _object = object; }
	GameObject* getObject() const noexcept {
		return _object;
	}

	void started() noexcept { _isStarted = true; }
	bool isStarted() const noexcept { return _isStarted; }
};

#endif // !COMPONENT_H
