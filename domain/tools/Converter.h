#ifndef IATAA_C_CONVERTER_H
#define IATAA_C_CONVERTER_H

#include <vector>
#include "../enumeration/BoardSquareType.h"

using Domain::Enumeration::BoardSquareType;
using std::vector;

namespace Domain {
    namespace Tool {
        class Converter {
        public:
            /**
             * Converts a board to internal format.
             */
            static void /* InternalFormat */
            convertToInternalFormat(const vector<BoardSquareType>&);

            /**
             * Converts a board to external format.
             */
            static vector<BoardSquareType>
                convertToExternalFormat(/* const InternalFormat& */);
        };
    }
}

#endif
