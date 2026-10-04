#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glad/glad.h>

class Texture final
{
private:
	GLuint _id;
	int _width;
	int _height;
	int _channels;
public:
	Texture();
	Texture(const std::string& path, bool isText);

	~Texture();

	void load(const std::string& path, bool isText) noexcept;
	void bind(GLenum texture) const noexcept;

	GLuint getID() const { return _id; }
	int getWidth() const { return _width; }
	int getHeight() const { return _height; }
};

#endif // !TEXTURE_H
