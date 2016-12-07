#ifndef IATAA_C_MOVEDTO_H
#define IATAA_C_MOVEDTO_H

#include "AbstractDTO.h"
#include "../domain/enumeration/State.h"
#include "../domain/enumeration/Difficulty.h"
#include "../domain/enumeration/Player.h"

#include <iostream>

#include <array>

using std::string;
using std::array;

class MoveDTO : public AbstractDTO {
public:
    MoveDTO(string token, Difficulty difficulty, Player player,
            array<char, 50>& board)
            : m_token(token), m_difficulty(difficulty), m_player(player),
              m_board(board) {}

    virtual ~MoveDTO() {}

public:
    virtual void serialize(PrettyWriter<StringBuffer>& writer) const {
        writer.String("token");
        writer.String(m_token.c_str());
        writer.String("difficulty");
        writer.String(m_difficulty.toString().c_str());
        writer.String("player");
        writer.String(m_player.toString().c_str());
        writer.String("board");
        writer.StartArray();
        for (const char& c : m_board) {
            string s(1, c);
            writer.String(s.c_str());
        }
        writer.EndArray();
    }

private:
    string m_token;
    Difficulty m_difficulty;
    Player m_player;
    array<char, 50> m_board;
};

#endif
