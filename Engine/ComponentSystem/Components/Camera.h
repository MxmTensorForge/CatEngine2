#ifndef CAMERA_H
#define CAMERA_H

#include "../Component.h"

#include "../../Geometry/Triangle.h"
#include "../../Geometry/Plane.h"
#include <vector>

class MeshComponent;
class Transform;

class Camera final : public Component
{
private:
	float _aspect{};
	float _zNear = 0.01f, _zFar = 1000.0f;
	float _fov{};
	float _scale{};

	bool _isNeedUpdateProjection = true;
	bool _isOrtho = false;

	Mxm::Mat4 _projectionMatrix{};
	Mxm::Mat4 _viewMatrix{};

	void start() override;
	void update() override;

	void dirtyProjection() noexcept;
	void recalcProjection() noexcept;
public:
	const Mxm::Mat4& getViewMatrix() const { return _viewMatrix; }
	const Mxm::Mat4& getProjectionMatrix() const { return _projectionMatrix; }
	Mxm::Mat4 getViewProjection() const { return _projectionMatrix * _viewMatrix; }

	void setFov(float fov) noexcept;
	void setNear(float near) noexcept;
	void setFar(float far) noexcept;
	void setScale(float scale) noexcept;

	void setPerspective() noexcept;
	void setOrthographic() noexcept;
};

#endif