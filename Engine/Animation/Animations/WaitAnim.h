#ifndef WAITANIM_H
#define WAITANIM_H

#include "Animation.h"
#include <functional>
#include <memory>

namespace Animations
{
    class WaitAnim final : public Animation
    {
    private:
        void update() override {}

    public:
        template <typename... Args>
        WaitAnim(Args&&... args)
            : Animation(std::forward<Args>(args)...) {
        }
    };
}

#endif