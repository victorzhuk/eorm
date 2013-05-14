#include "test.h"

Test::Test()
{
    this->init();
}

Test::Test(QVariant pk)
{
    this->init(pk);
}

QString Test::tableName()
{
    return "test";
}

QString Test::primaryKeyName()
{
    return "id";
}
