#ifndef SKYBOX_H
#define SKYBOX_H

#include "../Component.h"

#include <string>

class SkyBox final : public Component
{
private:
	std::string _cubeMapName;
public:
	SkyBox(const std::string& cubeMapName) : _cubeMapName{cubeMapName} {}

	inline void setCubeMapName(const std::string& name) noexcept { _cubeMapName = name; }
	inline const std::string& getCubeMapName() const noexcept { return _cubeMapName; }
};

#endif
