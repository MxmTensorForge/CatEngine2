#include "Buffer.h"

Buffer::Buffer(GLenum type) : _type(type) {
	glGenBuffers(1, &_id);
}
Buffer::~Buffer() {
	if (_id) glDeleteBuffers(1, &_id);
}

Buffer::Buffer(Buffer&& other) noexcept {
    if (_id) glDeleteBuffers(1, &_id);

    _id = other._id;
    _type = other._type;

    other._id = 0;
    other._type = 0;
}
Buffer& Buffer::operator=(Buffer&& other) noexcept {
    if (this != &other) {
        if (_id) glDeleteBuffers(1, &_id);

        _id = other._id;
        _type = other._type;

        other._id = 0;
        other._type = 0;
    }
    return *this;
}

void Buffer::bind() const noexcept {
	glBindBuffer(_type, _id);
}
void Buffer::unBind() const noexcept {
	glBindBuffer(_type, 0);
}

void Buffer::bufferData(GLsizeiptr size, const void* data, GLenum usage) const noexcept {
	glBufferData(_type, size, data, usage);
}
void Buffer::bufferSubData(GLintptr offset, GLsizeiptr size, void* data) const noexcept {
	glBufferSubData(_type, offset, size, data);
}