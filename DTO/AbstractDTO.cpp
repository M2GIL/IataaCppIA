#include "AbstractDTO.h"

std::string AbstractDTO::toJSON() const {
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);

    writer.StartObject();
    serialize(writer);
    writer.EndObject();

    return sb.GetString();
}
