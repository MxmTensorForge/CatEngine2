#ifndef DEBUGRENDERER_H
#define DEBUGRENDERER_H

#include <vector>
#include <memory>

#include "../Mxm/Vec3.h"
#include "../Graphics/VertexArray.h"
#include "../Graphics/Buffer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Color.h"

class Camera;

struct DebugLine final
{
    Mxm::Vec3 p0;
    Mxm::Vec3 p1;
    float lifeTime = 0.0f;
};
struct DebugSphere final
{
    Mxm::Vec3 center;
    float radius = 0.0f;
    float lifeTime = 0.0f;
};

class DebugRenderer final
{
private:
    std::vector<Mxm::Vec3> _vertices;

    std::vector<DebugLine> _lines;
    std::vector<DebugSphere> _spheres;

    std::unique_ptr<VertexArray> _vao;
    std::unique_ptr<Buffer> _vbo;

    std::unique_ptr<Shader> _debugShader;

    Color _color = Color(120, 120, 120, 255);
    float _lineWidth = 2.0f;

    DebugRenderer() = default;
    ~DebugRenderer() = default;
public:
    DebugRenderer(const DebugRenderer&) = delete;
    DebugRenderer& operator=(const DebugRenderer&) = delete;
    DebugRenderer(DebugRenderer&&) = delete;
    DebugRenderer& operator=(DebugRenderer&&) = delete;

    static DebugRenderer& getInstance() noexcept {
        static DebugRenderer renderer;
        return renderer;
    }
    void init() noexcept;

    void setColor(Color color) noexcept;

    void drawLine(const Mxm::Vec3& p0, const Mxm::Vec3& p1, float lifeTime = 0.0f) noexcept;
    void drawTriangle(const Mxm::Vec3& p0, const Mxm::Vec3& p1, const Mxm::Vec3& p2, float lifeTime = 0.0f) noexcept;
    void drawSphere(const Mxm::Vec3& center, float radius, float lifeTime = 0.0f) noexcept;

    void flush(Camera* camera) noexcept;
};

#endif
