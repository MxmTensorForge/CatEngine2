#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <glad/glad.h>

class VertexArray final
{
private:
	GLuint _id;
public:
	VertexArray();
	~VertexArray();

	VertexArray(const VertexArray&) = delete;
	VertexArray& operator=(const VertexArray&) = delete;

	VertexArray(VertexArray&& other) noexcept;
	VertexArray& operator=(VertexArray&& other) noexcept;

	bool isValid() const noexcept { return _id != 0; }
	GLuint id() const noexcept { return _id; }

	void bind() const noexcept;
	void unBind() const noexcept;

	void setAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) const noexcept;

	void enableAttribute(GLuint index) const noexcept;
	void disableAttribute(GLuint index) const noexcept;
};

#endif // !GLBUFFER_H
