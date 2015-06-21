#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "components/common/src/numeric_typedefs.h"
#include "BinaryIStream.h"
#include "BinaryOStream.h"

#include <deque>

class Message
{
public:
    static const S32 headerLength = 8;
    static const S32 maxBodyLength = 512;

    Message()
        : ostream{buffer}
    {
        buffer.resize(headerLength);
    }

    ~Message() = default;

    Message(const Message&) = default;
    Message& operator=(const Message&) = delete;

    const U8* data() const
    {
        return buffer.data();
    }

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

    void SetMsgType(const S32 type)
    {
        msgType = type;
    }

    bool DecodeHeader()
    {
        S32 bodyLength;
        std::memcpy(&bodyLength, buffer.data(), sizeof(bodyLength));

        if (bodyLength > maxBodyLength)
        {
            bodyLength = 0;
            return false;
        }

        buffer.resize(bodyLength + headerLength);

        return true;
    }

    void EncodeHeader()
    {
        S32 bodyLength = GetBodyLength();
        std::memcpy(buffer.data(), &bodyLength, 4);
        std::memcpy(buffer.data() + 4, &msgType, 4);
    }

    void WriteFloat(const F32 number)
    {
        ostream.write(number);
    }

    void WriteS32(const S32 number)
    {
        ostream.write(number);
    }

    void WriteChar(const char ch)
    {
        ostream.write(ch);
    }
private:
    std::vector<unsigned char> buffer;
    BinaryOStream ostream;

    S32 msgType{ 0 };
};

typedef std::deque<Message> MessageQueue;

#endif