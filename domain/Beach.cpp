#include "Beach.h"

#include "tools/RandomTextGenerator.h"
#include "tools/Converter.h"

namespace Domain {
    void Beach::generateNewGameID() {
        // Generates a new random gameID of length 10.
        m_gameID = Tool::RandomTextGenerator::getInstance()(10);
    }

    void
    Beach::newGameStarted(const Difficulty &difficulty, const Player &player) {
        generateNewGameID();
        toggleState();

        /// Complete it if you need to do something when a new game starts.
    }

    vector<BoardSquareType>
    Beach::gamePlay(const string &gameID, const Difficulty &difficulty,
                    const Player &player,
                    const vector<BoardSquareType> &board) {
        // Only if gameID is the good one.
        if (m_gameID == gameID) {
            // TODO
            /// Conversion to internal format.
            /* InternalFormat iF = */Tool::Converter::convertToInternalFormat(board);

            /// AI reflection.
            /* InternalFormat iaBoard = iF.think(player, difficulty);*/

            /// Conversion to external format.
            return Tool::Converter::convertToExternalFormat(/*iaBoard*/);
        } else {
            throw "Unknown gameID : " + gameID;
        }
    }

    void
    Beach::gameEnded(const string &gameID, const Player &winner,
                     const CodeEndGame &codeEndGame) {
        // Only if gameID is the good one.
        if (m_gameID == gameID) {
            m_gameID = "";
            toggleState();

            /// Complete it if you need to do something when a new game ends.
        } else {
            throw "Unknown gameID : " + gameID;
        }
    }
}
