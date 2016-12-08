#ifndef CHECKERS_REST_IA_C_STATUSDTO_H
#define CHECKERS_REST_IA_C_STATUSDTO_H

#include "AbstractDTO.h"
#include "../domain/enumeration/Status.h"

using Domain::Enumeration::Status;
using std::string;

namespace Dto {
    /**
     * Encapsulates a token and a status.
     */
    class StatusDTO : public AbstractDTO {
    public:
        StatusDTO(Status state, string token)
                : m_state(state), m_token(token) {}

        virtual ~StatusDTO() {}

    public:
        virtual void serialize(PrettyWriter<StringBuffer>&) const;

    private:
        /**
         * Token.
         */
        string m_token;

        /**
         * Status.
         */
        Status m_state;
    };
}

#endif
