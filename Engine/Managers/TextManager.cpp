#include "TextManager.h"
#include "TextureManager.h"

#include "../Core/Logger.h"

#include <fstream>
#include <sstream>

void TextManager::loadFromFile(const std::string& name, const std::string& fntPath, const std::string& texturePath) noexcept {
   	TextureManager::getInstance().loadTextureFromFile(name, texturePath, true);
   
	std::ifstream texFile(fntPath);
	if (!texFile.is_open()) {
		return;
	}

	_textsData[name] = std::make_unique<TextData>();
   
	std::string line;
	while (std::getline(texFile, line)) {
		if (line.find("char id=") != std::string::npos) {
			CharData data;
			int id = 0;
   
			std::istringstream ss(line);
			std::string token;
   
			while (ss >> token) {
				if (token.find("id=") != std::string::npos) id = std::stoi(token.substr(3));
				else if (token.find("x=") != std::string::npos) data.x = std::stoi(token.substr(2));
				else if (token.find("y=") != std::string::npos) data.y = std::stoi(token.substr(2));
				else if (token.find("width=") != std::string::npos) data.width = std::stoi(token.substr(6));
				else if (token.find("height=") != std::string::npos) data.height = std::stoi(token.substr(7));
				else if (token.find("xoffset=") != std::string::npos) data.xoffset = std::stoi(token.substr(8));
				else if (token.find("yoffset=") != std::string::npos) data.yoffset = std::stoi(token.substr(8));
				else if (token.find("xadvance=") != std::string::npos) data.xadvance = std::stoi(token.substr(9));
			}
   
			_textsData[name]->fontData[id] = data;
		}
		else if (line.find("common") != std::string::npos) {
			size_t pos = line.find("lineHeight=");
			if (pos != std::string::npos) {
				size_t end = line.find(" ", pos);
				_textsData[name]->lineHeight = std::stoi(line.substr(pos + 11, end - pos - 11));
			}
		}
	}
   
	texFile.close();

	Logger::getInstance().log(LogType::Message, "Font loaded successfully: " + name);
}
const TextData* TextManager::getTextData(const std::string& name) const noexcept {
    auto data = _textsData.find(name);
    if (data != _textsData.end()) {
        return data->second.get();
    }
    return nullptr;
}
