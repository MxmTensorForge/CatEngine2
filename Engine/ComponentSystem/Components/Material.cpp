#include "Material.h"

Material::Material(Color color) : _color(color), _isShaded{ true }, _isTwoSided{false} {}
Material::Material(const std::string& textureName, float uvScale) : _textureName(textureName), _isShaded{ true }, _uvScale{uvScale} {}
