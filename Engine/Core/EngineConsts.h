#ifndef ENGINECONSTS_H
#define ENGINECONSTS_H

namespace EngineConsts
{
	constexpr int STANDART_WIDTH = 800;
	constexpr int STANDART_HEIGHT = 600;

	constexpr const char* VERTEX_SHADER_PATH = "shaders/shader.vert";
	constexpr const char* FRAGMENT_SHADER_PATH = "shaders/shader.frag";

	constexpr const char* VERTEX_RECT_SHADER_PATH = "shaders/shaderUI.vert";
	constexpr const char* FRAGMENT_RECT_SHADER_PATH = "shaders/shaderUI.frag";

	constexpr const char* VERTEX_TEXT_SHADER_PATH = "shaders/shaderTextUI.vert";
	constexpr const char* FRAGMENT_TEXT_SHADER_PATH = "shaders/shaderTextUI.frag";

	constexpr const char* VERTEX_DEBUG_SHADER_PATH = "shaders/shaderDebug.vert";
	constexpr const char* FRAGMENT_DEBUG_SHADER_PATH = "shaders/shaderDebug.frag";

	constexpr const char* VERTEX_SKYBOX_SHADER_PATH = "shaders/shaderSkybox.vert";
	constexpr const char* FRAGMENT_SKYBOX_SHADER_PATH = "shaders/shaderSkybox.frag";
}

#endif // !ENGINECONSTS_H
