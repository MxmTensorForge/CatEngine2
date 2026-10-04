#ifndef UISCREEN_H
#define UISCREEN_H

#include "UIElement.h"

#include <utility>
#include <vector>
#include <memory>

class UIScreen final
{
private:
	std::vector<std::unique_ptr<UIElement>> _elements;
public:
	UIScreen() = default;
	~UIScreen() = default;

	template <typename T, typename... Args>
	T* add(Args&&... args) {
		auto element = std::make_unique<T>(std::forward<Args>(args)...);
		T* ptr = element.get();
		_elements.push_back(std::move(element));
		return ptr;
	}

	void update() noexcept {
		for (auto& e : _elements) if (e) e->update();
	}
	void render(UIRenderer* renderer) noexcept {
		for (const auto& e : _elements) {
			if (!e->getVisible()) continue;
			e->render(renderer);
		}
	}
	void clear() noexcept {
		_elements.clear();
	}
};

#endif // !UISCREEN_H
