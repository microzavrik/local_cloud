#include "received_type.hpp"

namespace types
{
    [[nodiscard]] received_type char_to_rectype(char received_byte)
    {
        switch(received_byte)
        {
            case 'f':
                return types::received_type::file;
            case 'p':
                return types::received_type::photo;
            case 'v':
                return types::received_type::video;
            case 't':
                return types::received_type::text;
            case 'j':
                return types::received_type::json;
            default:
                return types::received_type::none;
        }
    }
}