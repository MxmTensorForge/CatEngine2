#include "Texture.h"
#include "../Core/Logger.h"

#include <stb_image.h>

#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

Texture::Texture() : _id(0), _width(0), _height(0), _channels(0) {}

Texture::Texture(const std::string& path, bool isText) : Texture() {
	load(path, isText);
}

Texture::~Texture() {
	if (_id) glDeleteTextures(1, &_id);
}

void Texture::load(const std::string& path, bool isText) noexcept {
	stbi_set_flip_vertically_on_load(!isText);
	int width, height, channels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);

	if (!data) {
		Logger::getInstance().log(LogType::Fatal, "Image load failed");
	}

	GLenum format = GL_RGBA;
	/*if (channels == 4) format = GL_RGBA;
	else if (channels == 3) format = GL_RGB;
	else if (channels == 1) format = GL_RED;*/

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, isText ? GL_NEAREST : GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, isText ? GL_NEAREST : GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (!isText) {
		float maxAniso{};
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAniso);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	if (!isText) glGenerateMipmap(GL_TEXTURE_2D);;

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);

	_id = texture;
	_width = width;
	_height = height;
}
void Texture::bind(GLenum texture) const noexcept {
	glActiveTexture(texture);
	glBindTexture(GL_TEXTURE_2D, _id);
}
