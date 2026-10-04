#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Component.h"
#include "../../Graphics/Color.h"

#include <string>

class Material final : public Component
{
private:
	std::string _textureName;
	Color _color;

	float _shininess = 64.0f;
	float _specular = 0.5f;

	bool _isShaded;
	bool _isTwoSided;

	float _uvScale = 1.0f;
public:
	Material(Color color);
	Material(const std::string& textureName, float uvScale = 1.0f);

	void setTextureName(const std::string& name) noexcept { _textureName = name; }
	const std::string& getTextureName() const noexcept { return _textureName; }

	void setColor(Color color) noexcept { _color = color; }
	const Color& getColor() const noexcept { return _color; }

	void setShaded(bool state) noexcept { _isShaded = state; }
	bool isShaded() const noexcept { return _isShaded; }

	void setTwoSided(bool state) noexcept { _isTwoSided = state; }
	bool isTwoSided() const noexcept { return _isTwoSided; }

	void setShininess(float value) noexcept { _shininess = value; }
	void setSpecular(float value) noexcept { _specular = value; }

	float getShininess() const noexcept { return _shininess; }
	float getSpecular() const noexcept { return _specular; }

	void setUvScale(float scale) noexcept { _uvScale = scale; }
	float getUvScale() const noexcept { return _uvScale; }
};

#endif
