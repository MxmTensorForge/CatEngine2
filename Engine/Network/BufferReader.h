#ifndef BUFFERREADER_H
#define BUFFERREADER_H

#include <cstdint>

class BufferReader final
{
private:
    const uint8_t* _data;
    size_t _size;
    size_t _offset = 0;
public:
    BufferReader(const void* data, size_t size) : _data{static_cast<const uint8_t*>(data)}, _size{size} {
        
    }
    ~BufferReader() = default;
    
    template<typename T>
    T read() noexcept
    {
        T data;
        memcpy(&data, _data + _offset, sizeof(T));

        _offset += sizeof(T);

        return data;
    }

    const uint8_t* data() const noexcept { return _data + _offset; }
    size_t size() const noexcept { return _size; }
};

#endif
