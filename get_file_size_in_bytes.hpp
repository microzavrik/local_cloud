#ifndef GET_FILE_SIZE_IN_BYTES_HPP
#define GET_FILE_SIZE_IN_BYTES_HPP

#include <sys/stat.h>
#include <iostream>

off_t get_file_size_in_bytes(const char* filename)
{
    struct stat st;
    if(stat(filename, &st) == 0)
    {
        return st.st_size;
    }
    else
    {
        return -1;
    }
}

#endif