#ifndef CHECKERS_REST_IA_C_NEWGAMEDTO_H
#define CHECKERS_REST_IA_C_NEWGAMEDTO_H

#include "AbstractDTO.h"
#include "StatusDTO.h"
#include "../domain/enumeration/State.h"

using std::string;

namespace Dto {
/**
 * Encapsulates a new game response.
 */
    class NewGameDTO : public AbstractDTO {
    public:
        NewGameDTO(State state, string token, string gameID)
                : m_statusDTO(state, token), m_gameID(gameID) {}

        virtual ~NewGameDTO() {}

    public:
        virtual void serialize(PrettyWriter<StringBuffer>&) const;

    private:
        /**
         * Status.
         */
        StatusDTO m_statusDTO;

        /**
         * GameID.
         */
        string m_gameID;
    };
}

#endif
