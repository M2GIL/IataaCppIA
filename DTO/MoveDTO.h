#ifndef IATAA_C_MOVEDTO_H
#define IATAA_C_MOVEDTO_H

#include "AbstractDTO.h"
#include "../domain/enumeration/State.h"
#include "../domain/enumeration/Difficulty.h"
#include "../domain/enumeration/Player.h"
#include "../domain/enumeration/BoardSquareType.h"

#include <iostream>

#include <vector>

using Domain::Enumeration::State;
using Domain::Enumeration::BoardSquareType;
using Domain::Enumeration::Difficulty;
using Domain::Enumeration::Player;
using std::string;
using std::vector;

namespace Dto {
/**
 * Encapsulates a new move response.
 */
    class MoveDTO : public AbstractDTO {
    public:
        MoveDTO(string token, Difficulty difficulty, Player player,
                vector<BoardSquareType> &board)
                : m_token(token), m_difficulty(difficulty), m_player(player),
                  m_board(board) {}

        virtual ~MoveDTO() {}

    public:
        virtual void serialize(PrettyWriter<StringBuffer>&) const;

    private:
        /**
         * Token.
         */
        string m_token;

        /**
         * Difficulty.
         */
        Difficulty m_difficulty;

        /**
         * Player.
         */
        Player m_player;

        /**
         * Board.
         */
        vector<BoardSquareType> m_board;
    };
}

#endif
