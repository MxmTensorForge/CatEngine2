#include "Camera.h"
#include "../../Core/EngineConsts.h"

#include "../Object/GameObject.h"
#include "../Object/Transform.h"

void Camera::dirtyProjection() noexcept {
	_isNeedUpdateProjection = true;
}
void Camera::recalcProjection() noexcept {
	float scale = _scale * 0.5f;

	_projectionMatrix = _isOrtho ? Mxm::Mat4::ortho(scale * _aspect, -scale * _aspect, scale, -scale, _zNear, _zFar)
		: Mxm::Mat4::perspective(_fov, _aspect, _zNear, _zFar);
	_isNeedUpdateProjection = false;
}

void Camera::start() {
	_aspect = (float)EngineConsts::STANDART_WIDTH / (float)EngineConsts::STANDART_HEIGHT;
	recalcProjection();
}
void Camera::update() {
	if (_isNeedUpdateProjection) recalcProjection();

	auto& camera_transform = getObject()->transform();
	_viewMatrix = Mxm::Mat4::view(camera_transform.getRight(), camera_transform.getUp(), camera_transform.getForward(), camera_transform.getWorldPosition());
}

void Camera::setFov(float fov) noexcept {
	_fov = fov;
	dirtyProjection();
}
void Camera::setNear(float near) noexcept {
	_zNear = near;
	dirtyProjection();
}
void Camera::setFar(float far) noexcept {
	_zFar = far;
	dirtyProjection();
}
void Camera::setScale(float scale) noexcept {
	_scale = scale;
	dirtyProjection();
}

void Camera::setPerspective() noexcept {
	_isOrtho = false;
	dirtyProjection();
}
void Camera::setOrthographic() noexcept {
	_isOrtho = true;
	dirtyProjection();
}
