#ifndef CHECKERS_REST_IA_C_PLAYER_H
#define CHECKERS_REST_IA_C_PLAYER_H

#include "FalseEnum.h"

namespace Domain {
    namespace Enumeration {
        /**
         * Describes a player.
         */
        class Player : public FalseEnum {
        public:
            static const Player WHITE;
            static const Player BLACK;
            static const Player NONE;

        public:
            /**
             * Transforms a string to a Player.
             * @param str the string to transform
             * @return a Player
             * @throw a string if conversion is impossible
             */
            static Player getFromString(const string& str) {
                if (WHITE.m_toString == str) {
                    return WHITE;
                } else if (BLACK.m_toString == str) {
                    return BLACK;
                } else if (NONE.m_toString == str) {
                    return NONE;
                } else {
                    throw "Impossible to convert " + str + " to Player.";
                }
            }

        private:
            Player(string s) : FalseEnum(s) {}
        };
    }
}

#endif
