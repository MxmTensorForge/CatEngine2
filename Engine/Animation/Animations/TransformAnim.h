#ifndef TRANSFORMANIM_H
#define TRANSFORMANIM_H

#include "Animation.h"
#include "../../ComponentSystem/Object/GameObject.h"

#include <memory>

namespace Animations
{
	class TranslateByAnim final : public Animation
	{
	private:
		GameObject* _object;
		Mxm::Vec3 _value;

		void update() override {
			if (!_object) { stop(); return; }
			_object->transform().translate(_value * deltaProgress());
		}
	public:
		template <typename... Args>
		TranslateByAnim(GameObject* object, const Mxm::Vec3& value, Args&&... args)
			: Animation(std::forward<Args>(args)...), _object(object), _value(value) {
		}
	};

	class TranslateToAnim final : public Animation
	{
	private:
		GameObject* _object;

		bool _initialized = false;
		Mxm::Vec3 _start;
		Mxm::Vec3 _end;

		void update() override {
			if (!_object) { stop(); return; }

			if (!_initialized) {
				_start = _object->transform().getPosition();
				_initialized = true;
			}

			_object->transform().setPosition(_start + (_end - _start) * progress());
		}
	public:
		template <typename... Args>
		TranslateToAnim(GameObject* object, const Mxm::Vec3& value, Args&&... args)
			: Animation(std::forward<Args>(args)...), _object(object), _end(value) {
		}
	};

	class RotateByAnglesAnim final : public Animation {
	private:
		GameObject* _object;
		Mxm::Vec3 _axis;
		float _angle;

		bool _isStart = true;

		void update() override {
			if (!_object) { stop(); return; }

			if (_isStart) {
				_isStart = false;
			}

			Mxm::Quat rot = Mxm::Quat::aroundAxis(_axis, _angle * deltaProgress());
			_object->transform().rotate(rot);
		}

	public:
		template <typename... Args>
		RotateByAnglesAnim(GameObject* object, const Mxm::Vec3& angles, Args&&... args)
			: Animation(std::forward<Args>(args)...), _object(object) {
			float ax = std::abs(angles.x);
			float ay = std::abs(angles.y);
			float az = std::abs(angles.z);

			if (ax >= ay && ax >= az) {
				_angle = angles.x;
			}
			else if (ay >= ax && ay >= az) {
				_angle = angles.y;
			}
			else {
				_angle = angles.z;
			}
			_axis = Mxm::Vec3(ax, ay, az).normalized();
		}
	};

	class RotateByAxisAngleAnim final : public Animation
	{
	private:
		GameObject* _object;
		Mxm::Vec3 _axis;
		float _angle;

		bool _isStart = true;

		void update() override {
			if (!_object) { stop(); return; }

			if (_isStart) {
				_isStart = false;
			}

			Mxm::Quat rot = Mxm::Quat::aroundAxis(_axis, _angle * deltaProgress());
			_object->transform().rotate(rot);
		}
	public:
		template <typename... Args>
		RotateByAxisAngleAnim(GameObject* object, const Mxm::Vec3& axis, float angle, Args&&... args)
			: Animation(std::forward<Args>(args)...), _object(object), _axis(axis), _angle{ angle } {
		}
	};

	class RotateToAnim final : public Animation
	{
	private:
		GameObject* _object;

		bool _initialized = false;
		Mxm::Quat _start;
		Mxm::Quat _end;

		void update() override {
			if (!_object) { stop(); return; }

			if (!_initialized) {
				_start = _object->transform().getRotation();
				_initialized = true;
			}

			_object->transform().setRotation(_start.slerp(_end, progress()));
		}
	public:
		template <typename... Args>
		RotateToAnim(GameObject* object, const Mxm::Quat& value, Args&&... args)
			: Animation(std::forward<Args>(args)...), _object(object), _end(value) {
		}
	};

	class ScaleToAnim final : public Animation
	{
	private:
		GameObject* _object;

		bool _initialized = false;
		Mxm::Vec3 _start;
		Mxm::Vec3 _end;

		void update() override {
			if (!_object) { stop(); return; }

			if (!_initialized) {
				_start = _object->transform().getScale();
				_initialized = true;
			}

			_object->transform().setScale(_start + (_end - _start) * progress());
		}
	public:
		template <typename... Args>
		ScaleToAnim(GameObject* object, const Mxm::Vec3& value, Args&&... args)
			: Animation(std::forward<Args>(args)...), _object(object), _end(value) {
		}
	};
}

#endif
