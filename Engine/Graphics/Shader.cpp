#include "Shader.h"
#include "../Core/Logger.h"

#include <fstream>
#include <sstream>

std::string Shader::loadFromFile(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open()) {
		return "";
	}

	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexShaderSource = loadFromFile(vertexPath);
	const char* vertexSource = vertexShaderSource.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	GLint verSuccess;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &verSuccess);
	if (!verSuccess) {
		char log[512];
		glGetShaderInfoLog(vertexShader, 512, nullptr, log);
		Logger::getInstance().log(LogType::Fatal, log);
	}

	std::string fragmentShaderSource = loadFromFile(fragmentPath);
	const char* fragmentSource = fragmentShaderSource.c_str();

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);

	GLint frSuccess;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &frSuccess);
	if (!frSuccess) {
		char log[512];
		glGetShaderInfoLog(fragmentShader, 512, nullptr, log);
		Logger::getInstance().log(LogType::Fatal, log);
	}

	_program = glCreateProgram();
	glAttachShader(_program, vertexShader);
	glAttachShader(_program, fragmentShader);
	glLinkProgram(_program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLint pSuccess;
	glGetProgramiv(_program, GL_LINK_STATUS, &pSuccess);
	if (!pSuccess) {
		char log[512];
		glGetProgramInfoLog(_program, 512, nullptr, log);
		Logger::getInstance().log(LogType::Fatal, log);
	}
}
Shader::~Shader() {
	if (isValid()) glDeleteProgram(_program);
}

void Shader::use() const noexcept {
	glUseProgram(_program);
}

GLuint Shader::getUniformLoc(const std::string& name) noexcept {
	if (_uniformCache.count(name)) return _uniformCache[name];

	GLint loc = glGetUniformLocation(_program, name.c_str());
	if (loc == -1) {
		Logger::getInstance().log(LogType::Error, "Uniform not found: " + name);
	}
	_uniformCache[name] = loc;
	return loc;
}
void Shader::setUniform(const std::string& name, int v) noexcept {
	glUniform1i(getUniformLoc(name), v);
}
void Shader::setUniform(const std::string& name, float v) noexcept {
	glUniform1f(getUniformLoc(name), v);
}
void Shader::setUniform(const std::string& name, float x, float y) noexcept {
	glUniform2f(getUniformLoc(name), x, y);
}
void Shader::setUniform(const std::string& name, float x, float y, float z) noexcept {
	glUniform3f(getUniformLoc(name), x, y, z);
}
void Shader::setUniform(const std::string& name, float x, float y, float z, float w) noexcept {
	glUniform4f(getUniformLoc(name), x, y, z, w);
}
void Shader::setUniform(const std::string& name, const float* mat4, bool transpose) noexcept {
	glUniformMatrix4fv(getUniformLoc(name), 1, transpose, mat4);
}
