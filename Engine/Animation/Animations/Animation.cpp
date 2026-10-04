#include "Animation.h"
#include "../../Mxm/Consts.h"
#include "../../Mxm/Easing.h"

#include "../../Core/Time.h"

Animation::Animation(float duration, InterpolationType type, const CompleteCallback& callback, const Mxm::Vec2& point0, const Mxm::Vec2& point1)
	: _duration(duration), _type(type), _onComplete(callback), _point0(point0), _point1(point1) {

}

bool Animation::updateState() noexcept {
	if (_isFinished || _duration < Mxm::Consts::EPS) {
		return false;
	}

	_elapsed += Time::deltaTime();

	float t = _elapsed / _duration;
	if (t > 1.0f) t = 1.0f;

	switch (_type)
	{
	case InterpolationType::LINEAR:
		_progress = t;
		break;
	case InterpolationType::COS:
		_progress = Mxm::Easing::easeInSine(t);
		break;
	case InterpolationType::EASY_IN_EXP:
		_progress = Mxm::Easing::easeExp(t, -3.0f);
		break;
	case InterpolationType::EASY_OUT_EXP:
		_progress = Mxm::Easing::easeExp(t, 3.0f);
		break;
	case InterpolationType::EASY_IN_SINE:
		_progress = Mxm::Easing::easeInSine(t);
		break;
	case InterpolationType::EASY_OUT_SINE:
		_progress = Mxm::Easing::easeOutSine(t);
		break;
	case InterpolationType::SMOOTHSTEP:
		_progress = Mxm::Easing::smoothstep(t);
		break;
	case InterpolationType::COS_BOUNCE:
		_progress = Mxm::Easing::cosBounceIn(t, 3.0f, 1.0f);
		break;
	case InterpolationType::ELASTIC_COS_BOUNCE:
		_progress = Mxm::Easing::elasticCosBounceIn(t, 3.0f, 1.0f);
		break;
	case InterpolationType::BEZIER:
		_progress = Mxm::Easing::bezier(t, _point0.x, _point0.y, _point1.x, _point1.y);
		break;
	}

	_deltaprogress = _progress - _lastprogress;
	_lastprogress = _progress;

	update();

	if (t >= 1.0f) {
		_isFinished = true;
		if (_onComplete) {
			_onComplete();
		}
	}

	return !_isFinished;
}