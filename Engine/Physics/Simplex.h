#ifndef SIMPLEX_H
#define SIMPLEX_H

#include "MinkowskiPoint.h"

class Simplex final
{
private:
    MinkowskiPoint _points[4];
    size_t _size = 0;
public:
    Simplex() = default;
    Simplex(const MinkowskiPoint& p0) : _points{p0}, _size{1} {};
    Simplex(const MinkowskiPoint& p0, const MinkowskiPoint& p1) : _points{p0, p1}, _size{2} {};
    Simplex(const MinkowskiPoint& p0, const MinkowskiPoint& p1, const MinkowskiPoint& p2) : _points{p0, p1, p2}, _size{3} {};
    Simplex(const MinkowskiPoint& p0, const MinkowskiPoint& p1, const MinkowskiPoint& p2, const MinkowskiPoint& p3) : _points{p0, p1, p2, p3}, _size{4} {};
    
    void push_front(const MinkowskiPoint& point) noexcept {
        _points[3] = _points[2];
        _points[2] = _points[1];
        _points[1] = _points[0];
        _points[0] = point;
        if (_size < 4) _size++;
    }

    size_t size() const noexcept { return _size; }
    void clear() noexcept { _size = 0; }

    MinkowskiPoint& operator[](size_t index) noexcept { return _points[index]; }
    const MinkowskiPoint& operator[](size_t index) const noexcept { return _points[index]; }

    MinkowskiPoint* begin() noexcept { return _points; }
    MinkowskiPoint* end() noexcept { return _points + _size; }

    const MinkowskiPoint* begin() const noexcept { return _points; }
    const MinkowskiPoint* end() const noexcept { return _points + _size; }
};

#endif
