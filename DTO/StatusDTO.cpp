#include "StatusDTO.h"

namespace Dto {
    void StatusDTO::serialize(PrettyWriter<StringBuffer> &writer) const {
        writer.String("token");
        writer.String(m_token.c_str());
        writer.String("status");
        writer.String(m_state.toString().c_str());
    }
}
