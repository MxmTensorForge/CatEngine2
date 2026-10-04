#include "CubeMap.h"
#include "../Core/Logger.h"

#include <stb_image.h>

#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

CubeMap::CubeMap() : _id(0), _width(0), _height(0), _channels(0) {}

CubeMap::CubeMap(const std::vector<std::string>& paths) : CubeMap() {
	load(paths);
}

CubeMap::~CubeMap() {
	if (_id) glDeleteTextures(1, &_id);
}

void CubeMap::load(const std::vector<std::string>& paths) noexcept {
    if (paths.size() != 6) return;

    stbi_set_flip_vertically_on_load(false);

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _id);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (int i = 0; i < 6; i++)
    {
        unsigned char* data = stbi_load(paths[i].c_str(), &_width, &_height, &_channels, 4);
        if (!data) {
            Logger::getInstance().log(LogType::Fatal, "CubeMap load failed");
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
void CubeMap::bind(GLenum texture) const noexcept {
	glActiveTexture(texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
}
