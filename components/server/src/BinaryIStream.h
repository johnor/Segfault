#ifndef BINARY_ISTREAM_H_
#define BINARY_ISTREAM_H_

#include <vector>

class BinaryIStream
{
public:
    BinaryIStream(std::vector<unsigned char>& vec) : index(0), buffer(vec) {}
    ~BinaryIStream() = default;

    template<typename T>
    void read(T& t)
    {
        RawRead(reinterpret_cast<unsigned char*>(&t), sizeof(T));
    }

    void read(std::vector<unsigned char>& vec)
    {
        RawRead(&vec[0], vec.size());
    }
private:
    BinaryIStream(const BinaryIStream&) = delete;
    BinaryIStream& operator=(const BinaryIStream&) = delete;

    void RawRead(unsigned char dest[], const size_t size)
    {
        if ((index + size) > buffer.size())
        {
            throw std::runtime_error("Not enough data in buffer");
        }

        std::memcpy(static_cast<void*>(dest), &buffer[index], size);
        index += size;
    }

    size_t index;
    std::vector<unsigned char> &buffer;
};

#endif
