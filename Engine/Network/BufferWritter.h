#ifndef BUFFERWRITTER_H
#define BUFFERWRITTER_H

#include <cstdint>
#include <vector>

class BufferWritter final
{
private:
    std::vector<uint8_t> _data;
public:
    BufferWritter() = default;
    ~BufferWritter() = default;

    template<typename T>
    void write(const T& data)
    {
        const size_t oldSize = _data.size();
        _data.resize(oldSize + sizeof(T));

        memcpy(_data.data() + oldSize, &data, sizeof(T));
    }
    void writeBytes(const uint8_t* data, size_t size)
    {
        const size_t oldSize = _data.size();
        _data.resize(oldSize + size);

        memcpy(_data.data() + oldSize, data, size);
    }

    size_t size() const noexcept { return _data.size(); }
    const uint8_t* data() const noexcept { return _data.data(); }

    void clear() noexcept { _data.clear(); }
};

#endif
