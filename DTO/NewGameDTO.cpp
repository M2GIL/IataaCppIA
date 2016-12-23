#include "NewGameDTO.h"

namespace Dto {
    void NewGameDTO::serialize(PrettyWriter<StringBuffer> &writer) const {
        m_statusDTO.serialize(writer);
        writer.String("game_id");
        writer.String(m_gameID.c_str());
    }
}
