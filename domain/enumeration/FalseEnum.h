#ifndef CHECKERS_REST_IA_C_FALSEENUM_H
#define CHECKERS_REST_IA_C_FALSEENUM_H

#include <string>

using std::string;

class FalseEnum {
public:
    virtual ~FalseEnum() {}

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

#endif
