#ifndef CHECKERS_REST_IA_C_DIFFICULTY_H
#define CHECKERS_REST_IA_C_DIFFICULTY_H

#include "FalseEnum.h"

class Difficulty : public FalseEnum {
public:
    static const Difficulty EASY;
    static const Difficulty MEDIUM;
    static const Difficulty HARD;

public:
    static Difficulty getFromString(const string& str) {
        if (EASY.m_toString == str) {
            return EASY;
        } else if (MEDIUM.m_toString == str) {
            return MEDIUM;
        } else if (HARD.m_toString == str) {
            return HARD;
        } else {
            throw "Impossible to convert " + str + " to Difficulty.";
        }
    }

private:
    Difficulty(string s) : FalseEnum(s) {}
};

#endif
