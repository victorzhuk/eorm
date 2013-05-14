#ifndef TEST_H
#define TEST_H

#include "eormactiverecord.h"

class Test : public EOrmActiveRecord
{
public:
    // constructor for creating new object
    Test();
    // constructor for load existing object
    Test(QVariant pk);
    // reimplement pure virtual funtion, returning object table name
    QString tableName();
    // reimplement pure virtual funtion, returning object primary key name
    QString primaryKeyName();
};

#endif // TEST_H
