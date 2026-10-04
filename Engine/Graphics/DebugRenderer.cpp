#include "DebugRenderer.h"

#include "../Core/EngineConsts.h"
#include "../Core/Time.h"
#include "../ComponentSystem/Components/Camera.h"

#include <algorithm>

void DebugRenderer::init() noexcept {
    _debugShader = std::make_unique<Shader>(EngineConsts::VERTEX_DEBUG_SHADER_PATH, EngineConsts::FRAGMENT_DEBUG_SHADER_PATH);

    _vao = std::make_unique<VertexArray>();
    _vbo = std::make_unique<Buffer>(GL_ARRAY_BUFFER);

    _vao->bind();
    _vbo->bind();

    _vao->setAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    _vao->enableAttribute(0);

    _vbo->unBind();
    _vao->unBind();
}

void DebugRenderer::setColor(Color color) noexcept {
    _color = color;
}

void DebugRenderer::drawLine(const Mxm::Vec3& p0, const Mxm::Vec3& p1, float lifeTime) noexcept {
    _lines.push_back({p0, p1, lifeTime});
}
void DebugRenderer::drawTriangle(const Mxm::Vec3& p0, const Mxm::Vec3& p1, const Mxm::Vec3& p2, float lifeTime) noexcept {
    _lines.push_back({p0, p1, lifeTime});
    _lines.push_back({p1, p2, lifeTime});
    _lines.push_back({p2, p0, lifeTime});
}
void DebugRenderer::drawSphere(const Mxm::Vec3& center, float radius, float lifeTime) noexcept {
    _spheres.push_back({center, radius, lifeTime});
}

void DebugRenderer::flush(Camera* camera) noexcept {
    if (!camera) return;

    for (auto& line : _lines) {
        _vertices.push_back(line.p0);
        _vertices.push_back(line.p1);

        line.lifeTime -= Time::deltaTime();
    }
    for (auto& sphere : _spheres) {
        int segments = 24;
        float step = 2.0f * Mxm::Consts::PI / segments;
    
        for (int i = 0; i < segments; i++) {
            float a0 = i * step;
            float a1 = (i+1) * step;
    
            _vertices.push_back(sphere.center + Mxm::Vec3(cosf(a0), sinf(a0), 0.0f) * sphere.radius);
            _vertices.push_back(sphere.center + Mxm::Vec3(cosf(a1), sinf(a1), 0.0f) * sphere.radius);
            _vertices.push_back(sphere.center + Mxm::Vec3(0.0f, cosf(a0), sinf(a0)) * sphere.radius);
            _vertices.push_back(sphere.center + Mxm::Vec3(0.0f, cosf(a1), sinf(a1)) * sphere.radius);
            _vertices.push_back(sphere.center + Mxm::Vec3(cosf(a0), 0.0f, sinf(a0)) * sphere.radius);
            _vertices.push_back(sphere.center + Mxm::Vec3(cosf(a1), 0.0f, sinf(a1)) * sphere.radius);
        }

        sphere.lifeTime -= Time::deltaTime();
    }

    _debugShader->use();
    
    _debugShader->setUniform("uColor", _color.rf(), _color.gf(), _color.bf(), _color.af());
    _debugShader->setUniform("uProjection", camera->getProjectionMatrix().data(), true);
    _debugShader->setUniform("uView", camera->getViewMatrix().data(), true);

    _vao->bind();
    
    _vbo->bind();
    _vbo->bufferData(_vertices.size() * sizeof(Mxm::Vec3), _vertices.data(), GL_STREAM_DRAW);

    glLineWidth(_lineWidth);
    glDrawArrays(GL_LINES, 0, _vertices.size());

    _vertices.clear();

    _lines.erase(std::remove_if(_lines.begin(), _lines.end(), [](const DebugLine& line) {
        return line.lifeTime <= 0.0f;
    }), _lines.end());
    _spheres.erase(std::remove_if(_spheres.begin(), _spheres.end(), [](const DebugSphere& sphere) {
        return sphere.lifeTime <= 0.0f;
    }), _spheres.end());
}
