#include "Converter.h"

namespace Domain {
    namespace Tool {
        void /* InternalFormat */ Converter::convertToInternalFormat(
                const vector<BoardSquareType> &board) {
            /// Change return type from void to internal format.
            /// Write function to convert board to your format.

            // Example :
            // InternalFormat iF;
            // for (int i = 0; i < board.size(); ++i) {
            //    iF.setSquare(i, board[i]);
            // }
            // return iF;
        }

        vector<BoardSquareType>
        Converter::convertToExternalFormat(/* const InternalFormat& iF */) {
            /// Take as parameter a const reference to internal format.
            /// Write a function to convert the board from your format to
            /// BoardSquareType format.

            // Example (white draughts everywhere) :
            vector<BoardSquareType> a;
            for (int i = 0; i < 50; ++i) {
                a.push_back(BoardSquareType::WHITE_DRAUGHT);
            }
            return a;
        }
    }
}
