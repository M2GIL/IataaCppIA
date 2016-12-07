#ifndef IATAA_C_CONVERTER_H
#define IATAA_C_CONVERTER_H

#include <array>

using std::array;

class Converter {
public:
    static void convertToInternalFormat(const array<char, 50>& board);

    static array<char, 50> convertToExternalFormat();
};

#endif
