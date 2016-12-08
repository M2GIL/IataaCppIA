#ifndef CHECKERS_REST_IA_C_ABSTRACTDTO_H
#define CHECKERS_REST_IA_C_ABSTRACTDTO_H

#include <string>

#include "../include/rapidjson/prettywriter.h"

using namespace rapidjson;
using std::string;

namespace Dto {
/**
 * An abstracton for all DTO.
 */
    class AbstractDTO {
    public:
        virtual ~AbstractDTO() {}

        /**
         * @return the JSON form of the object
         */
        virtual string toJSON() const;

    public:
        /**
         * Transforms the object to JSON.
         */
        virtual void serialize(PrettyWriter<StringBuffer>&) const = 0;
    };
}

#endif
