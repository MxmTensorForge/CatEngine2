#ifndef FIXEDVECTOR_H
#define FIXEDVECTOR_H

#include <array>
#include <cstdint>

template<typename T, size_t N>
class FixedVector final
{
private:
    std::array<T, N> _data;
    size_t _size = 0;
public:
    void push_back(const T& value) noexcept {
        if (_size < N) _data[_size++] = value;
    }
    void erase_unordered(size_t index) noexcept {
        _data[index] = _data[--_size];
    }

    size_t size() const noexcept { return _size; }

    T& operator[](size_t index) { return _data[index]; }
    const T& operator[](size_t index) const { return _data[index]; }

    T* begin() noexcept { return _data.data(); }
    T* end() noexcept { return _data.data() + _size; }

    const T* begin() const noexcept { return _data.data(); }
    const T* end() const noexcept { return _data.data() + _size; }
};

#endif
