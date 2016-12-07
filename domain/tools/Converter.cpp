#include "Converter.h"

void Converter::convertToInternalFormat(const array<char, 50>& board) {
    // Convert from a 50-char array to internal format.
    /// Change return type from void to internal format.
}

array<char, 50> Converter::convertToExternalFormat() {
    // Convert from internal format to a 50-char array.
    /// Take as parameter a const reference to internal format.

    array<char, 50> a;
    for (int i = 0; i < 50; ++i) {
        a[i] = '1';
    }
    return a;
}
