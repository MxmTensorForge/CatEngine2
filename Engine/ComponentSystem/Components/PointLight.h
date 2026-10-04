#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "../Component.h"
#include "../../Graphics/Color.h"

class PointLight final : public Component
{
private:
	float _linearFading = 0.09f;
	float _quadraticFading = 0.032f;
	float _intensity = 1.0f;
	Color _lightColor = Color(255, 255, 255);
public:
	float getLinearFading() const noexcept { return _linearFading; }
	float getQuadraticFading() const noexcept { return _quadraticFading; }
	float getIntensity() const noexcept { return _intensity; }
	Color getLightColor() const noexcept { return _lightColor; }

	void setLinearFading(float value) noexcept { _linearFading = value; }
	void setQuadraticFading(float value) noexcept { _quadraticFading = value; }
	void setIntensity(float value) noexcept { _intensity = value; }
	void setLightColor(Color value) noexcept { _lightColor = value; }
};

#endif