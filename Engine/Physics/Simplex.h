#ifndef SIMPLEX_H
#define SIMPLEX_H

#include "../Mxm/Vec3.h"

class Simplex final
{
private:
    Mxm::Vec3 _points[4];
    size_t _size = 0;
public:
    Simplex() = default;
    Simplex(const Mxm::Vec3& p0) : _points{p0}, _size{1} {};
    Simplex(const Mxm::Vec3& p0, const Mxm::Vec3& p1) : _points{p0, p1}, _size{2} {};
    Simplex(const Mxm::Vec3& p0, const Mxm::Vec3& p1, const Mxm::Vec3& p2) : _points{p0, p1, p2}, _size{3} {};
    Simplex(const Mxm::Vec3& p0, const Mxm::Vec3& p1, const Mxm::Vec3& p2, const Mxm::Vec3& p3) : _points{p0, p1, p2, p3}, _size{4} {};
    
    void push_front(const Mxm::Vec3& point) noexcept {
        _points[3] = _points[2];
        _points[2] = _points[1];
        _points[1] = _points[0];
        _points[0] = point;
        if (_size < 4) _size++;
    }

    size_t size() const noexcept { return _size; }
    void clear() noexcept { _size = 0; }

    Mxm::Vec3& operator[](size_t index) noexcept { return _points[index]; }
    const Mxm::Vec3& operator[](size_t index) const noexcept { return _points[index]; }

    Mxm::Vec3* begin() noexcept { return _points; }
    Mxm::Vec3* end() noexcept { return _points + _size; }

    const Mxm::Vec3* begin() const noexcept { return _points; }
    const Mxm::Vec3* end() const noexcept { return _points + _size; }
};

#endif
