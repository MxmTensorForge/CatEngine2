#ifndef APPLICATION_H
#define APPLICATION_H

#include "Screen.h"
#include "../Graphics/MeshRenderer.h"
#include "../UI/UIRenderer.h"

class Material;
class GameObject;

class Application
{
private:
	std::unique_ptr<Screen> _screen;
	std::unique_ptr<MeshRenderer> _meshRenderer;
	std::unique_ptr<UIRenderer> _uiRenderer;

	int _width, _height;
	float _stateAccumulator = 0.0f;

	std::vector<Material*> _transparentMaterials;

	void initialize();
	void updatePhysics();
	void updateGame();

	void renderOpaque();
	void renderTransparent(GameObject* camera);

	void renderFrame();
	void renderUI();

	void applySceneChanges();

	bool processFrame();
	void swapBuffers();
protected:
	virtual void start() {}
	virtual void update() {}
	virtual void fixedUpdate() {}
	virtual void shutdown() {}

	void setDrawFrame(bool state) noexcept;
public:
	Application();
	virtual ~Application() = default;
	
	void run();
};

#endif // !APPLICATION_H
