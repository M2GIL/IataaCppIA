#ifndef CHECKERS_REST_IA_C_STATE_H
#define CHECKERS_REST_IA_C_STATE_H

#include "FalseEnum.h"

class State : public FalseEnum {
public:
    static const State BUSY;
    static const State AVAILABLE;

private:
    State(string s) : FalseEnum(s) {}
};

#endif
