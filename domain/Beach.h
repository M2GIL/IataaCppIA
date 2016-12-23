#ifndef CHECKERS_REST_IA_C_BEACH_H
#define CHECKERS_REST_IA_C_BEACH_H

#include "State.h"
#include "Difficulty.h"
#include "Player.h"

using std::string;

class Beach {
public:
    Beach() : m_state(State::AVAILABLE), m_token("") {}

    void newGameStarted(const Difficulty& difficulty, const Player& player);

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

    string getGameID() const {
        return m_gameID;
    }

private:
    State m_state;
    string m_token;
    string m_gameID;
};

#endif
