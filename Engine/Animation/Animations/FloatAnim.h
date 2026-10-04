#ifndef FLOATANIM_H
#define FLOATANIM_H

#include "Animation.h"
#include <functional>
#include <memory>

namespace Animations
{
    class SetFloatAnim final : public Animation
    {
    private:
        std::function<void(float)> _setter;
        float _start;
        float _end;

        void update() override {
            float t = progress();
            float current = _start + (_end - _start) * t;
            _setter(current);
        }

    public:
        template <typename... Args>
        SetFloatAnim(float startValue, float endValue, const std::function<void(float)>& setter, Args&&... args)
            : Animation(std::forward<Args>(args)...), _start(startValue), _end(endValue), _setter(setter) {
        }
    };
    class AddFloatAnim final : public Animation
    {
    private:
        std::function<void(float)> _addFunc;
        float _value;

        void update() override {
            _addFunc(_value * deltaProgress());
        }

    public:
        template <typename... Args>
        AddFloatAnim(float value, const std::function<void(float)>& addFunc, Args&&... args)
            : Animation(std::forward<Args>(args)...), _value{value}, _addFunc(addFunc) {
        }
    };
}

#endif
