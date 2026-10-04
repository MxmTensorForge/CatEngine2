#ifndef COLORANIM_H
#define COLORANIM_H

#include "Animation.h"
#include "../../ComponentSystem/Components/Material.h"

#include <memory>

namespace Animations
{
	class ColorAnim final : public Animation
	{
	private:
		Material* _object;

		bool _initialized = false;
		Color _start;
		Color _end;

		void update() override {
			if (!_object) { stop(); return; }

			if (!_initialized) {
				_start = _object->getColor();
				_initialized = true;
			}

			float t = progress();
			Color current(
				Color::clamp(static_cast<uint8_t>(_start.r() * (1.0f - t) + _end.r() * t)),
				Color::clamp(static_cast<uint8_t>(_start.g() * (1.0f - t) + _end.g() * t)),
				Color::clamp(static_cast<uint8_t>(_start.b() * (1.0f - t) + _end.b() * t)),
				Color::clamp(static_cast<uint8_t>(_start.a() * (1.0f - t) + _end.a() * t))
			);
			_object->setColor(current);
		}
	public:
		template <typename... Args>
		ColorAnim(Material* material, Color value, Args&&... args)
			: Animation(std::forward<Args>(args)...), _object(material), _end(value) {
		}
	};
}

#endif