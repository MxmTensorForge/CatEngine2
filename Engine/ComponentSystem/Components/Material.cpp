#include "Material.h"

Material::Material(Color color) : _color(color), _isShaded{ true }, _isTwoSided{false} {}
Material::Material(const std::string& textureName, float uvScale) : _textureName(textureName), _isShaded{ true }, _uvScale{uvScale} {}

uint64_t fnv_hash(const void* data, size_t size, uint64_t hash = 0xcbf29ce484222325ULL) noexcept {
    const auto* bytes = static_cast<const uint8_t*>(data);
    for (size_t i = 0; i < size; ++i) {
        hash ^= bytes[i];
        hash *= 0x100000001b3ULL;
    }
    return hash;
}

uint64_t Material::generateSignature() const noexcept {
    uint64_t hash = fnv_hash(_textureName.data(), _textureName.size());

    #pragma pack(push, 1)
    struct HashData final
    {
        Color color;
        float shininess;
        float specular;
        bool isShaded;
        bool isTwoSided;
        float uvScale;
    } data{};
    #pragma pack(pop)

    data.color = _color;
    data.shininess = _shininess;
    data.specular = _specular;
    data.isShaded = _isShaded;
    data.isTwoSided = _isTwoSided;
    data.uvScale = _uvScale;

    return fnv_hash(&data, sizeof(HashData));
}
