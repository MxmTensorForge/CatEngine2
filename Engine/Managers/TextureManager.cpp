#include "TextureManager.h"
#include "../Graphics/Texture.h"
#include "../Graphics/CubeMap.h"

#include "../Core/Logger.h"
#include <utility>

TextureManager& TextureManager::getInstance() {
	static TextureManager manager;
	return manager;
}

void TextureManager::loadTextureFromFile(const std::string& name, const std::string& path, bool isText) {
	std::unique_ptr<Texture> tex = std::make_unique<Texture>(path, isText);
	_textures[name] = std::move(tex);

	Logger::getInstance().log(LogType::Message, "Texture loaded successfully: " + name);
}
const Texture* TextureManager::getTexture(const std::string& name) const {
	auto it = _textures.find(name);
	if (it == _textures.end()) {
		Logger::getInstance().log(LogType::Fatal, "Texture not found (" + name + ").");
	}

	return it->second.get();
}

void TextureManager::loadCubeMapFromFile(const std::string& name, const std::vector<std::string>& paths) {
   	std::unique_ptr<CubeMap> cubeMap = std::make_unique<CubeMap>(paths);
	_cubeMaps[name] = std::move(cubeMap);
   
	Logger::getInstance().log(LogType::Message, "CubeMap loaded successfully: " + name);
}
const CubeMap* TextureManager::getCubeMap(const std::string& name) const {
   	auto it = _cubeMaps.find(name);
	if (it == _cubeMaps.end()) {
		Logger::getInstance().log(LogType::Fatal, "CubeMap not found (" + name + ").");
	}
   
	return it->second.get();
}

void TextureManager::removeTexture(const std::string& name) {
	auto it = _textures.find(name);
	if (it == _textures.end()) return;

	_textures.erase(it);
}
void TextureManager::clearTextures(const std::string& name) {
	_textures.clear();
}
