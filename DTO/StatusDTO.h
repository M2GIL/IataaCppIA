#ifndef CHECKERS_REST_IA_C_STATUSDTO_H
#define CHECKERS_REST_IA_C_STATUSDTO_H

#include "AbstractDTO.h"
#include "../domain/enumeration/State.h"

using std::string;

class StatusDTO : public AbstractDTO {
public:
    StatusDTO(State state, string token)
            : m_state(state), m_token(token) {}

    virtual ~StatusDTO() {}

public:
    virtual void serialize(PrettyWriter<StringBuffer>& writer) const {
        writer.String("token");
        writer.String(m_token.c_str());
        writer.String("status");
        writer.String(m_state.toString().c_str());
    }

private:
    State m_state;
    string m_token;
};

#endif
