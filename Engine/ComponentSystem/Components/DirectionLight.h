#ifndef DIRECTIONLIGHT_H
#define DIRECTIONLIGHT_H

#include "../Component.h"
#include "../../Graphics/Color.h"
#include "../../Mxm/Vec3.h"

class DirectionLight final : public Component
{
private:
	float _intensity = 1.0f;
	Color _lightColor = Color(255, 255, 255);
public:
	float getIntensity() const noexcept { return _intensity; }
	Color getLightColor() const noexcept { return _lightColor; }

	void setIntensity(float value) noexcept { _intensity = value; }
	void setLightColor(Color value) noexcept { _lightColor = value; }
};

#endif