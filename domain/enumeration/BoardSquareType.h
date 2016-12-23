#ifndef IATAA_C_BOARDSQUARETYPE_H
#define IATAA_C_BOARDSQUARETYPE_H

#include "FalseEnum.h"

namespace Domain {
    namespace Enumeration {
        class BoardSquareType : public FalseEnum {
        public:
            static const BoardSquareType EMPTY;
            static const BoardSquareType BLACK_PAWN;
            static const BoardSquareType BLACK_DRAUGHT;
            static const BoardSquareType WHITE_PAWN;
            static const BoardSquareType WHITE_DRAUGHT;

        public:
            /**
             * Transforms a char to a BoardSquareType.
             * @param c the char to transform
             * @return a BoardSquareType
             * @throw a string if conversion is impossible
             */
            static BoardSquareType getFromChar(char c) {
                string s(1, c);
                if (EMPTY.m_toString == s) {
                    return EMPTY;
                } else if (BLACK_PAWN.m_toString == s) {
                    return BLACK_PAWN;
                } else if (BLACK_DRAUGHT.m_toString == s) {
                    return BLACK_DRAUGHT;
                } else if (WHITE_PAWN.m_toString == s) {
                    return WHITE_PAWN;
                } else if (WHITE_DRAUGHT.m_toString == s) {
                    return WHITE_DRAUGHT;
                } else {
                    throw "Impossible to convert " + s + " to BoardSquareType.";
                }
            }

        private:
            BoardSquareType(string s) : FalseEnum(s) {}
        };
    }
}

#endif
