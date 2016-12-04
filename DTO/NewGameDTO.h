#ifndef CHECKERS_REST_IA_C_NEWGAMEDTO_H
#define CHECKERS_REST_IA_C_NEWGAMEDTO_H

#include "AbstractDTO.h"
#include "StatusDTO.h"
#include "../domain/State.h"

using std::string;

class NewGameDTO : public AbstractDTO {
public:
    NewGameDTO(State state, string token, string gameID)
            : m_statusDTO(state, token), m_gameID(gameID) {}

    virtual ~NewGameDTO() {}

public:
    virtual void serialize(PrettyWriter<StringBuffer>& writer) const {
        m_statusDTO.serialize(writer);
        writer.String("game_id");
        writer.String(m_gameID.c_str());
    }

private:
    StatusDTO m_statusDTO;
    string m_gameID;
};

#endif
