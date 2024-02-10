#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <QDataStream>

class ISerializable {
public:
    virtual ~ISerializable() {}
    virtual void serialize(QDataStream& out) const = 0;
};

#endif // ISERIALIZABLE_H
