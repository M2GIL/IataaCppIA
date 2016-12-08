#ifndef CHECKERS_REST_IA_C_STATE_H
#define CHECKERS_REST_IA_C_STATE_H

#include "FalseEnum.h"

namespace Domain {
    namespace Enumeration {
        /**
         * Describes a status.
         */
        class Status : public FalseEnum {
        public:
            static const Status BUSY;
            static const Status AVAILABLE;

        private:
            Status(string s) : FalseEnum(s) {}
        };
    }
}

#endif
