#include "Beach.h"

#include "tools/RandomTextGenerator.h"
#include "tools/Converter.h"
#include "../AI/Board.h"
#include "../AI/AI.h"

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
            /// Conversion to internal format.
            Board b = Tool::Converter::convertToInternalFormat(board);

            /// AI reflection.
            // Get difficulty in good format.
            AI::AIDifficulty aiDifficulty;
            if (difficulty.toString() == Difficulty::EASY.toString()) {
                aiDifficulty = AI::AIDifficulty::Easy;
            } else if (difficulty.toString() == Difficulty::MEDIUM.toString()) {
                aiDifficulty = AI::AIDifficulty::Medium;
            } else if (difficulty.toString() == Difficulty::HARD.toString()) {
                aiDifficulty = AI::AIDifficulty::Hard;
            } else {
                throw "Unable to check difficulty in gamePlay.";
            }

            // Get color in good format.
            Board::Color color;
            if (player.toString() == Player::BLACK.toString()) {
                color = Board::Color::Black;
            } else if (player.toString() == Player::WHITE.toString()) {
                color = Board::Color::White;
            } else {
                throw "Unable to check color in gamePlay.";
            }

            // Launch AI.
            AI ai(aiDifficulty);
            Board iaBoard;
            ai.thinkAboutNextMove(b, color, iaBoard);

            /// Conversion to external format.
            return Tool::Converter::convertToExternalFormat(iaBoard);
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
