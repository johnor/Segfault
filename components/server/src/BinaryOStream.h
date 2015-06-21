#ifndef BINARY_OSTREAM_H_
#define BINARY_OSTREAM_H_

#include <vector>

class BinaryOStream
{
public:
    BinaryOStream(std::vector<unsigned char>& vec) : buffer(vec) {}
    ~BinaryOStream() = default;

    template<typename T>
    void write(const T& t)
    {
        std::vector<unsigned char> vec(sizeof(T));
        std::memcpy(static_cast<void*>(&vec[0]), static_cast<const void*>(&t), sizeof(T));
        write(vec);
    }

    void write(const std::vector<unsigned char>& vec)
    {
        for (size_t i = 0; i < vec.size(); ++i)
        {
            buffer.push_back(vec[i]);
        }
    }
private:
    BinaryOStream(const BinaryOStream&) = delete;
    BinaryOStream& operator=(const BinaryOStream&) = delete;

    std::vector<unsigned char> &buffer;
};

#endif