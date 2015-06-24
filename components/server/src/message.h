#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "components/common/src/numeric_typedefs.h"
#include "BinaryIStream.h"
#include "BinaryOStream.h"

#include <deque>
#include <eigen/Eigen>

class Message
{
public:
    static const S32 headerLength = 8;
    static const S32 maxBodyLength = 512;

    Message(const U32 messageType = 0u)
        : ostream{ buffer }, msgType{messageType}
    {
        buffer.resize(headerLength);
    }

    ~Message() = default;

    Message(const Message&) = default;
    Message& operator=(const Message&) = delete;

    const U8* data() const { return buffer.data(); }

    U8* data()
{
        return buffer.data();
    }

    std::size_t getLength() const
    {
        return buffer.size();
    }

    const U8* body() const
    {
        return buffer.data() + headerLength;
    }

    U8* body()
    {
        return buffer.data() + headerLength;
    }

    S32 GetBodyLength() const
    {
        return buffer.size() - headerLength;
    }

    bool DecodeHeader();
    void EncodeHeader();

    template<typename T>
    Message& operator<<(const T& t)
    {
        ostream.write(t);
        return *this;
    }
private:
    std::vector<unsigned char> buffer;
    BinaryOStream ostream;

    U32 msgType{ 0 };
};

inline Message& operator<<(Message& stream, const Eigen::Quaternionf &quat)
{
    return stream << quat.w() << quat.x() << quat.y() << quat.z();
}

typedef std::deque<Message> MessageQueue;

#endif