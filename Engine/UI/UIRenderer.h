#ifndef UIRENDERER_H
#define UIRENDERER_H

#include "../Graphics/VertexArray.h"
#include "../Graphics/Buffer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

#include "../Graphics/Color.h"
#include "../Mxm/Mat4.h"

struct RectCmd final
{
	float x, y, z;
	float w, h;
	Color color;
};

struct TextCmd final 
{
	float x, y, z;
	float scale;
	std::string text;
	std::string fontName;
	Color color;
};
struct TextGeometry final
{
   	std::vector<float> vertices;
	unsigned int numVerts = 0;
};

class UIRenderer final
{
private:
	std::unique_ptr<VertexArray> _rectVAO;
	std::unique_ptr<Buffer> _rectVBO;
	std::unique_ptr<Shader> _rectShader;

	std::vector<float> _rectVertices;
	unsigned int _numVerts;

	std::unique_ptr<VertexArray> _textVAO;
	std::unique_ptr<Buffer> _textVBO;
	std::unique_ptr<Shader> _textShader;

	std::unordered_map<std::string, TextGeometry> _textsGeometry;

	void addVertex(float x, float y, float z, Color color);
	void addTextVertex(const std::string fontName, float x, float y, float z, float u, float v, Color color);

	Mxm::Mat4 _ortho;
public:
	UIRenderer();
	~UIRenderer();

	void init(int width, int height);

	void pushRect(const RectCmd& r);
	void pushText(const TextCmd& r);
	void flush();
};

#endif // !UIRENDERER_H
