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
        : bodyLength(0)
    {
        memset(buffer, 0, headerLength + maxBodyLength);
        currentWritePos = headerLength;
    }

    const U8* data() const
    {
        return buffer;
    }

    U8* data()
    {
        return buffer;
    }

    std::size_t getLength() const
    {
        return headerLength + bodyLength;
    }

    const U8* body() const
    {
        return buffer + headerLength;
    }

    U8* body()
    {
        return buffer + headerLength;
    }

    S32 GetBodyLength() const
    {
        return bodyLength;
    }

    void SetBodyLength(std::size_t new_length)
    {
        bodyLength = new_length;
        if (bodyLength > maxBodyLength)
        {
            bodyLength = maxBodyLength;
        }
    }

    void SetMsgType(const S32 type)
    {
        msgType = type;
    }

    bool DecodeHeader()
    {
        std::memcpy(&bodyLength, buffer, sizeof(bodyLength));

        if (bodyLength > maxBodyLength)
        {
            bodyLength = 0;
            return false;
        }
        return true;
    }

    void EncodeHeader()
    {
        std::memcpy(buffer, &bodyLength, 4);
        std::memcpy(buffer + 4, &msgType, 4);
    }

    void WriteFloat(const F32 number)
    {
        std::memcpy(buffer + currentWritePos, &number, sizeof(number));
        currentWritePos += sizeof(number);
    }

    void WriteS32(const S32 number)
    {
        std::memcpy(buffer + currentWritePos, &number, sizeof(number));
        currentWritePos += sizeof(number);
    }

    void WriteChar(const char ch)
    {
        std::memcpy(buffer + currentWritePos, &ch, sizeof(ch));
        currentWritePos += sizeof(ch);
    }
private:
    U8 buffer[headerLength + maxBodyLength];
    S32 currentWritePos;
    S32 bodyLength;
    S32 msgType{ 0 };
};

typedef std::deque<Message> MessageQueue;

#endif