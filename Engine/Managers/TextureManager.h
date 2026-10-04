#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

class Texture;
class CubeMap;

class TextureManager final
{
private:
    std::unordered_map<std::string, std::unique_ptr<Texture>> _textures;
	std::unordered_map<std::string, std::unique_ptr<CubeMap>> _cubeMaps;

	TextureManager() = default;
	~TextureManager() = default;
public:
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;
	TextureManager& operator=(TextureManager&&) = delete;

	static TextureManager& getInstance();

	void loadTextureFromFile(const std::string& name, const std::string& path, bool isText = false);
	const Texture* getTexture(const std::string& name) const;

	void loadCubeMapFromFile(const std::string& name, const std::vector<std::string>& paths);
	const CubeMap* getCubeMap(const std::string& name) const;

	void removeTexture(const std::string& name);
	void clearTextures(const std::string& name);
};

#endif // !RESOURCEMANAGER_H
