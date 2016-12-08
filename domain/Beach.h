#ifndef CHECKERS_REST_IA_C_BEACH_H
#define CHECKERS_REST_IA_C_BEACH_H

#include "enumeration/Status.h"
#include "enumeration/Difficulty.h"
#include "enumeration/Player.h"
#include "enumeration/CodeEndGame.h"
#include "enumeration/BoardSquareType.h"
#include <vector>

using Domain::Enumeration::CodeEndGame;
using Domain::Enumeration::BoardSquareType;
using Domain::Enumeration::Difficulty;
using Domain::Enumeration::Player;
using Domain::Enumeration::Status;
using std::string;
using std::vector;

namespace Domain {
    /**
     * Interface between REST services and AI implementation.
     */
    class Beach {
    public:
        Beach() : m_state(Status::AVAILABLE), m_token("c") {}

        // INDICATORS METHODS
        /**
         * Indicates that a new game started.
         */
        void newGameStarted(const Difficulty&, const Player&);

        /**
         * Indicates that we need a new move.
         * @return the calculated move
         */
        vector<BoardSquareType>
        gamePlay(const string&, const Difficulty&, const Player&,
                 const vector<BoardSquareType>&);

        /**
         * Indicates that a game ended.
         */
        void gameEnded(const string&, const Player&, const CodeEndGame&);

    public:
        // STATE METHODS
        /**
         * Toggles the state between AVAILABLE and BUSY.
         */
        void toggleState() {
            m_state = (m_state == Status::AVAILABLE ? Status::BUSY
                                                   : Status::AVAILABLE);
        }

        Status getState() const {
            return m_state;
        }

        void setToken(string token) {
            m_token = token;
        }

        /**
         * Verifies the token.
         * @param token the token
         * @return true if token is valid, false otherwise
         */
        bool isGoodToken(string token) const {
            return m_token == token;
        }

        string getToken() const {
            return m_token;
        }

        void generateNewGameID();

        /**
         * Verifies the gameID.
         * @param gameID the gameID
         * @return true if gameID is recognized, false otherwise
         */
        bool isKnownGameID(string gameID) const {
            return m_gameID == gameID;
        }

        string getGameID() const {
            return m_gameID;
        }

    private:
        /**
         * The token.
         */
        string m_token;

        /**
         * The status of the system.
         */
        Status m_state;

        /**
         * THe gameID.
         */
        string m_gameID;
    };
}

#endif
