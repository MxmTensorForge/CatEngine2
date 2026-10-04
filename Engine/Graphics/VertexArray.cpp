#include "VertexArray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &_id);
}
VertexArray::~VertexArray() {
	if (_id) glDeleteVertexArrays(1, &_id);
}

VertexArray::VertexArray(VertexArray&& other) noexcept {
	if (_id) glDeleteVertexArrays(1, &_id);

	_id = other._id;
	other._id = 0;
}
VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
	if (this != &other) {
		if (_id) glDeleteVertexArrays(1, &_id);

		_id = other._id;
		other._id = 0;
	}
	return *this;
}

void VertexArray::bind() const noexcept {
	glBindVertexArray(_id);
}
void VertexArray::unBind() const noexcept {
	glBindVertexArray(0);
}

void VertexArray::setAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) const noexcept {
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
}

void VertexArray::enableAttribute(GLuint index) const noexcept {
	glEnableVertexAttribArray(index);
}
void VertexArray::disableAttribute(GLuint index) const noexcept {
	glDisableVertexAttribArray(index);
}