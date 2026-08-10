
#ifndef SERIALIZEDTYPES_H
#define SERIALIZEDTYPES_H

#include "string"


struct SerializedText {
    std::string buffer;
};

struct SerializedAlert{
    std::string buffer;
};

struct SerializedPing{
    std::string buffer;
};




#endif // SERIALIZEDTYPES_H
