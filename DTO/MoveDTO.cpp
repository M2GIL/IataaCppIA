#include "MoveDTO.h"

namespace Dto {
    void MoveDTO::serialize(PrettyWriter<StringBuffer> &writer) const {
        writer.String("token");
        writer.String(m_token.c_str());
        writer.String("difficulty");
        writer.String(m_difficulty.toString().c_str());
        writer.String("player");
        writer.String(m_player.toString().c_str());
        if (!m_board.empty()) {
            writer.String("board");
            writer.StartArray();
            for (const BoardSquareType &b : m_board) {
                writer.String(b.toString().c_str());
            }
            writer.EndArray();
        }
    }
}
