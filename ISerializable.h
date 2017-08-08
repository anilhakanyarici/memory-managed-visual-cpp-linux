#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

class BinaryWriter;
class BinaryReader;

class ISerializable
{
public:
    virtual void GetSerializationData(BinaryWriter *writer) const = 0;
    virtual bool SetSerializationData(BinaryReader *reader) = 0;
};

#endif // ISERIALIZABLE_H
