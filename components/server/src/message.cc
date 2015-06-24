#include "message.h"

bool Message::DecodeHeader()
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

void Message::EncodeHeader()
{
    S32 bodyLength = GetBodyLength();
    std::memcpy(buffer.data(), &bodyLength, 4);
    std::memcpy(buffer.data() + 4, &msgType, 4);
}
