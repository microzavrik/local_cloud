#ifndef RECEIVED_TYPE_HPP
#define RECEIVED_TYPE_HPP

namespace types
{
    enum class received_type
    {
        file,
        photo,
        video,
        text,
        json,
        none
    };

    [[nodiscard]] received_type char_to_rectype(char received_byte);
}

#endif