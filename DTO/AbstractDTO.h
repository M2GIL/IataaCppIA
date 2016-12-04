#ifndef CHECKERS_REST_IA_C_ABSTRACTDTO_H
#define CHECKERS_REST_IA_C_ABSTRACTDTO_H

#include <string>

#include "../include/rapidjson/prettywriter.h"

using namespace rapidjson;
using std::string;

class AbstractDTO {
public:
    virtual ~AbstractDTO() {}

    virtual string toJSON() const;

public:
    virtual void serialize(PrettyWriter<StringBuffer>&) const = 0;
};

#endif
