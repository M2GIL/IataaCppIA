#ifndef CHECKERS_REST_IA_C_FALSEENUM_H
#define CHECKERS_REST_IA_C_FALSEENUM_H

#include <string>

using std::string;

namespace Domain {
    namespace Enumeration {
        /**
         * Super class of Java-style enumerations.
         */
        class FalseEnum {
        public:
            virtual ~FalseEnum() {}

            /**
             * Converts the enumeration to string.
             * @return string value of the enumeration
             */
            string toString() const {
                return m_toString;
            };

            bool operator==(const FalseEnum& s1) {
                return m_toString == s1.m_toString;
            }

        protected:
            FalseEnum(string s) : m_toString(s) {}

        protected:
            string m_toString;
        };
    }
}

#endif
