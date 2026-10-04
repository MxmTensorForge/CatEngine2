#ifndef ANIMATION_H
#define ANIMATION_H

#include "../../Mxm/Vec2.h"
#include <functional>

class Animation
{
public:
	enum class InterpolationType
	{
		LINEAR,
		COS, EASY_IN_EXP, EASY_OUT_EXP, EASY_IN_SINE, EASY_OUT_SINE, SMOOTHSTEP,
		COS_BOUNCE, ELASTIC_COS_BOUNCE,
		BEZIER
	};

	using CompleteCallback = std::function<void()>;
private:
	float _duration = 0;
	float _elapsed = 0;

	float _progress = 0;
	float _lastprogress = 0;
	float _deltaprogress = 0;

	CompleteCallback _onComplete;

	Mxm::Vec2 _point0{};
	Mxm::Vec2 _point1{};

	bool _isFinished = false;

	InterpolationType _type;

	virtual void update() = 0;
protected:
	inline void stop() noexcept { _isFinished = true; }

	inline float progress() const noexcept { return _progress; }
	inline float deltaProgress() const noexcept { return _deltaprogress; }
public:
	virtual ~Animation() = default;

	Animation(float duration, InterpolationType type, const CompleteCallback& callback = {},
		const Mxm::Vec2& point0 = Mxm::Vec2{}, const Mxm::Vec2& point1 = Mxm::Vec2{});

	bool updateState() noexcept;
	bool isPlaying() const noexcept { return _elapsed > 0.0f; }
};

#endif // ANIMATION_H