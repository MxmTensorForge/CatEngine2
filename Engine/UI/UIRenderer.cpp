#include "UIRenderer.h"
#include "../Core/Logger.h"
#include "../Core/EngineConsts.h"

#include "../Managers/TextManager.h"
#include "../Managers/TextureManager.h"

UIRenderer::UIRenderer() : _numVerts(0) {
}
UIRenderer::~UIRenderer() {

}

void UIRenderer::init(int width, int height) {
	_rectVAO = std::make_unique<VertexArray>();
	_rectVBO = std::make_unique<Buffer>(GL_ARRAY_BUFFER);
	_rectShader = std::make_unique<Shader>(EngineConsts::VERTEX_RECT_SHADER_PATH, EngineConsts::FRAGMENT_RECT_SHADER_PATH);

	_rectVAO->bind();
	_rectVBO->bind();

	_rectVAO->setAttribute(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	_rectVAO->setAttribute(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));

	_rectVAO->enableAttribute(0);
	_rectVAO->enableAttribute(1);


	_textVAO = std::make_unique<VertexArray>();
	_textVBO = std::make_unique<Buffer>(GL_ARRAY_BUFFER);
	_textShader = std::make_unique<Shader>(EngineConsts::VERTEX_TEXT_SHADER_PATH, EngineConsts::FRAGMENT_TEXT_SHADER_PATH);

	_textVAO->bind();
	_textVBO->bind();

	_textVAO->setAttribute(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	_textVAO->setAttribute(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	_textVAO->setAttribute(2, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(5 * sizeof(float)));

	_textVAO->enableAttribute(0);
	_textVAO->enableAttribute(1);
	_textVAO->enableAttribute(2);

	_ortho = Mxm::Mat4::ortho((float)width, 0.0f, 0.0f, (float)height, -1.0f, 1.0f);

	Logger::getInstance().log(LogType::Message, "UIRenderer has been successfully initialized");
}

void UIRenderer::addVertex(float x, float y, float z, Color color) {
	_rectVertices.push_back(x);
	_rectVertices.push_back(y);
	_rectVertices.push_back(z);

	_rectVertices.push_back(color.rf());
	_rectVertices.push_back(color.gf());
	_rectVertices.push_back(color.bf());
	_rectVertices.push_back(color.af());

	_numVerts++;
}
void UIRenderer::addTextVertex(const std::string fontName, float x, float y, float z, float u, float v, Color color) {
    TextGeometry& geometry = _textsGeometry[fontName];
    
	geometry.vertices.push_back(x);
	geometry.vertices.push_back(y);
	geometry.vertices.push_back(z);
	geometry.vertices.push_back(u);
	geometry.vertices.push_back(v);

	geometry.vertices.push_back(color.rf());
	geometry.vertices.push_back(color.gf());
	geometry.vertices.push_back(color.bf());
	geometry.vertices.push_back(color.af());

	geometry.numVerts++;
}

void UIRenderer::pushRect(const RectCmd& r) {
	addVertex(r.x, r.y, r.z, r.color);
	addVertex(r.x + r.w, r.y, r.z, r.color);
	addVertex(r.x, r.y + r.h, r.z, r.color);

	addVertex(r.x + r.w, r.y, r.z, r.color);
	addVertex(r.x + r.w, r.y + r.h, r.z, r.color);
	addVertex(r.x, r.y + r.h, r.z, r.color);
}
void UIRenderer::pushText(const TextCmd& t) {
    const auto* data = TextManager::getInstance().getTextData(t.fontName);
    const auto* textTexture = TextureManager::getInstance().getTexture(t.fontName);
    if (!data || !textTexture) return;

	int cursorX = t.x;
	int cursorY = t.y;

	for (char c : t.text) {
		if (c == '\n') {
			cursorY += data->lineHeight * t.scale;
			cursorX = t.x;
			continue;
		}

		auto it = data->fontData.find(static_cast<int>(c));
		if (it == data->fontData.end()) {
			continue;
		}

		const CharData& data = it->second;

		float xpos = (float)cursorX + (float)data.xoffset * t.scale;
		float ypos = (float)cursorY + (float)data.yoffset * t.scale;
		float w = (float)data.width * t.scale;
		float h = (float)data.height * t.scale;

		float texWidth = static_cast<float>(textTexture->getWidth());
		float texHeight = static_cast<float>(textTexture->getHeight());

		float u1 = (data.x) / texWidth;
		float v1 = (data.y) / texHeight;
		float u2 = (data.x + data.width) / texWidth;
		float v2 = (data.y + data.height) / texHeight;

		addTextVertex(t.fontName, xpos, ypos, t.z, u1, v1, t.color);
		addTextVertex(t.fontName, xpos + w, ypos, t.z, u2, v1, t.color);
		addTextVertex(t.fontName, xpos, ypos + h, t.z, u1, v2, t.color);

		addTextVertex(t.fontName, xpos + w, ypos, t.z, u2, v1, t.color);
		addTextVertex(t.fontName, xpos + w, ypos + h, t.z, u2, v2, t.color);
		addTextVertex(t.fontName, xpos, ypos + h, t.z, u1, v2, t.color);

		cursorX += data.xadvance * t.scale;
	}
}

void UIRenderer::flush() {
	if (_numVerts != 0) {
		_rectShader->use();
		_rectVAO->bind();

		_rectVBO->bind();
		_rectVBO->bufferData(_rectVertices.size() * sizeof(float), _rectVertices.data(), GL_STREAM_DRAW);

		_rectShader->setUniform("uProjection", _ortho.data(), true);
		glDrawArrays(GL_TRIANGLES, 0, _numVerts);

		_rectVertices.clear();
		_numVerts = 0;
	}
	for (auto& [fontName, geometry] : _textsGeometry) {
	    if (geometry.vertices.empty()) continue;
		
        _textShader->use();
        _textVAO->bind();

        _textVBO->bind();
        _textVBO->bufferData(geometry.vertices.size() * sizeof(float), geometry.vertices.data(), GL_STREAM_DRAW);

        TextureManager::getInstance().getTexture(fontName)->bind(0);
        _textShader->setUniform("textTexture", 0);

        _textShader->setUniform("uProjection", _ortho.data(), true);
        glDrawArrays(GL_TRIANGLES, 0, geometry.numVerts);

        geometry.vertices.clear();
        geometry.numVerts = 0;
	}
}
