#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <unordered_map>

class Shader final
{
private:
	GLuint _program;
	std::unordered_map<std::string, GLint> _uniformCache;

	static std::string loadFromFile(const std::string& path);
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	bool isValid() const noexcept { return _program != 0; }
	GLuint id() const noexcept { return _program; }

	void use() const noexcept;

	GLuint getUniformLoc(const std::string& name) noexcept;
	void setUniform(const std::string& name, int v) noexcept;
	void setUniform(const std::string& name, float v) noexcept;
	void setUniform(const std::string& name, float x, float y) noexcept;
	void setUniform(const std::string& name, float x, float y, float z) noexcept;
	void setUniform(const std::string& name, float x, float y, float z, float w) noexcept;
	void setUniform(const std::string& name, const float* mat4, bool transpose) noexcept;
};

#endif // !SHADER_H
