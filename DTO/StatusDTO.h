#ifndef CHECKERS_REST_IA_C_STATUSDTO_H
#define CHECKERS_REST_IA_C_STATUSDTO_H

#include "AbstractDTO.h"
#include "../domain/enumeration/State.h"

using Domain::Enumeration::State;
using std::string;

namespace Dto {
    /**
     * Encapsulates a token and a status.
     */
    class StatusDTO : public AbstractDTO {
    public:
        StatusDTO(State state, string token)
                : m_state(state), m_token(token) {}

        virtual ~StatusDTO() {}

    public:
        virtual void serialize(PrettyWriter<StringBuffer>& writer) const;

    private:
        /**
         * Token.
         */
        string m_token;

        /**
         * Status.
         */
        State m_state;
    };
}

#endif
