#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <unordered_map>
#include <deque>
#include <string>
#include <memory>

#include "Animations/Animation.h"

using AnimTag = std::string;

class Animator final
{
private:
	std::unordered_map<AnimTag, std::deque<std::unique_ptr<Animation>>> _animationList;
	void update();

	friend class Scene;
public:
	template <typename T, typename... Args>
	void add(const AnimTag& tag, Args&&... args) {
		_animationList[tag].emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
	}
	void remove(AnimTag tag);
	bool isPlaying(AnimTag tag) const;
};

#endif // !ANIMATOR_H