#include "MeshManager.h"
#include "../Geometry/MeshData.h"

#include "../Core/Logger.h"

#include <fstream>
#include <sstream>

MeshManager& MeshManager::getInstance() {
	static MeshManager manager;
	return manager;
}

void MeshManager::loadModelFromFile(const std::string& name, const std::string& path) {
	std::ifstream file;
	file.open(path, std::ios::binary);
	if (!file.is_open()) {
		Logger::getInstance().log(LogType::Fatal, "Model file not opened (" + path + ")");
		return;
	}

	MeshData result;

	std::string line;

	while (std::getline(file, line))
	{
		if (line.empty() || line[0] == '#') continue;

		std::string type;
		std::istringstream ss(line);

		ss >> type;

		if (type == "v") {
			float x, y, z;
			ss >> x >> y >> z;

			result.vertices.emplace_back(x, y, z);
		}
		else if (type == "vt") {
			float s, t;
			ss >> s >> t;

			result.textureCoords.emplace_back(s, t);
		}
		else if (type == "f") {
			std::string faceData;
			std::vector<unsigned int> faceIndices;
			std::vector<unsigned int> texCoordsIndices;

			while (ss >> faceData)
			{
				size_t slash = faceData.find('/');

				if (slash != std::string::npos) {
					int vertexIndex = std::stoi(faceData.substr(0, slash));
					faceIndices.push_back(vertexIndex - 1);

					size_t slash1 = faceData.find('/', slash + 1);
					int uvIndex = std::stoi(faceData.substr(slash + 1, slash1 - slash - 1));
					texCoordsIndices.push_back(uvIndex - 1);
				}
				else {
					int vertexIndex = std::stoi(faceData);
					faceIndices.push_back(vertexIndex - 1);
					texCoordsIndices.push_back(0);
				}
			}

			for (size_t i = 1; i + 1 < faceIndices.size(); i++)
			{
				result.indices.push_back(faceIndices[0]);
				result.indices.push_back(faceIndices[i]);
				result.indices.push_back(faceIndices[i + 1]);
			}
			for (size_t i = 1; i + 1 < texCoordsIndices.size(); i++)
			{
				result.textureIndices.push_back(texCoordsIndices[0]);
				result.textureIndices.push_back(texCoordsIndices[i]);
				result.textureIndices.push_back(texCoordsIndices[i + 1]);
			}
		}
	}
	file.close();

	result.calculateNormals();
	result.data.loadData(result.vertices, result.indices, result.normals, result.textureCoords, result.textureIndices);

	_meshes[name] = std::make_unique<MeshData>(std::move(result));
	Logger::getInstance().log(LogType::Message, "Model " + name + " (" + path + ") has been loaded successfully");
}
MeshData* MeshManager::getModel(const std::string& name) const {
	auto it = _meshes.find(name);
	if (it == _meshes.end()) {
		Logger::getInstance().log(LogType::Fatal, "Model not found (" + name + ")");
		return nullptr;
	}

	return it->second.get();
}

void MeshManager::removeModel(const std::string& name) {
	auto it = _meshes.find(name);
	if (it == _meshes.end()) return;

	_meshes.erase(it);
}
void MeshManager::clearModels(const std::string& name) {
	_meshes.clear();
}
