#ifndef CHECKERS_REST_IA_C_BEACH_H
#define CHECKERS_REST_IA_C_BEACH_H

#include "enumeration/State.h"
#include "enumeration/Difficulty.h"
#include "enumeration/Player.h"
#include "enumeration/CodeEndGame.h"

using std::string;

class Beach {
public:
    Beach() : m_state(State::AVAILABLE), m_token("c") {}

    void newGameStarted(const Difficulty& difficulty, const Player& player);

    void gameEnded(const string& gameID, Player winner, CodeEndGame codeEndGame);

public:
    // STATE METHODS

    void toggleState() {
        m_state = (m_state == State::AVAILABLE ? State::BUSY : State::AVAILABLE);
    }

    State getState() const {
        return m_state;
    }

    void setToken(string token) {
        m_token = token;
    }

    bool isGoodToken(string token) const {
        return m_token == token;
    }

    string getToken() const {
        return m_token;
    }

    void generateNewGameID();

    bool isKnownGameID(string gameID) const {
        return m_gameID == gameID;
    }

    string getGameID() const {
        return m_gameID;
    }

private:
    State m_state;
    string m_token;
    string m_gameID;
};

#endif
