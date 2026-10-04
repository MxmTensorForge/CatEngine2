#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <string>
#include <vector>
#include <glad/glad.h>

class CubeMap final
{
private:
	GLuint _id;
	int _width;
	int _height;
	int _channels;
public:
	CubeMap();
	CubeMap(const std::vector<std::string>& paths);

	~CubeMap();

	void load(const std::vector<std::string>& paths) noexcept;
	void bind(GLenum texture) const noexcept;

	GLuint getID() const { return _id; }
	int getWidth() const { return _width; }
	int getHeight() const { return _height; }
};

#endif
