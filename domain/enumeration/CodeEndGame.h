#ifndef CHECKERS_REST_IA_C_CODEENDGAME_H
#define CHECKERS_REST_IA_C_CODEENDGAME_H

#include "FalseEnum.h"

namespace Domain {
    namespace Enumeration {
        class CodeEndGame : public FalseEnum {
        public:
            static const CodeEndGame TIMEOUT;
            static const CodeEndGame SURRENDER;
            static const CodeEndGame CLASSICAL;

        public:
            /**
             * Transforms a string to a CodeEndGame.
             * @param str the string to transform
             * @return a CodeEndGame
             * @throw a string if conversion is impossible
             */
            static CodeEndGame getFromString(const string &str) {
                if (TIMEOUT.m_toString == str) {
                    return TIMEOUT;
                } else if (SURRENDER.m_toString == str) {
                    return SURRENDER;
                } else if (CLASSICAL.m_toString == str) {
                    return CLASSICAL;
                } else {
                    throw "Impossible to convert " + str + " to CodeEndGame.";
                }
            }

        private:
            CodeEndGame(string s) : FalseEnum(s) {}
        };
    }
}

#endif
