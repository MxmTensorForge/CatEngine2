#include "Animator.h"

void Animator::update() {
    for (auto& [tag, deque] : _animationList)
    {
        while (!deque.empty()) {
            if (!deque.front()->updateState()) deque.pop_front();
            else break;
        }
    }

    auto it = _animationList.begin();
    while (it != _animationList.end()) {
        if (it->second.empty()) {
            it = _animationList.erase(it);
        }
        else {
            it++;
        }
    }
}

void Animator::remove(AnimTag tag) {
    auto it = _animationList.find(tag);

    if (it != _animationList.end()) {
        _animationList.erase(it);
    }
}

bool Animator::isPlaying(AnimTag tag) const {
    auto it = _animationList.find(tag);

    if (it != _animationList.end()) {
        return it->second.front()->isPlaying();
    }
    return false;
}
