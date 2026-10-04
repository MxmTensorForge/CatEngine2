#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>

class Buffer final
{
private:
	GLuint _id;
	GLenum _type;
public:
	Buffer(GLenum type);
	~Buffer();

	Buffer(const Buffer&) = delete;
	Buffer& operator=(const Buffer&) = delete;

	Buffer(Buffer&& other) noexcept;
	Buffer& operator=(Buffer&& other) noexcept;

	bool isValid() const noexcept { return _id != 0; }
	GLuint id() const noexcept { return _id; }
	GLenum type() const noexcept { return _type; }

	void bind() const noexcept;
	void unBind() const noexcept;

	void bufferData(GLsizeiptr size, const void* data, GLenum usage) const noexcept;
	void bufferSubData(GLintptr offset, GLsizeiptr size, void* data) const noexcept;
};

#endif // !GLBUFFER_H
