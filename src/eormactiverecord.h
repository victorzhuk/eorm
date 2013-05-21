/****************************************************************************
**
** Copyright (C) 2013 Victor Zhuk.
** Contact: chewire@gmail.com
**
** This file is part of the EOrm library.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**
**  * Redistributions of source code must retain the above copyright notice,
**    this list of conditions and the following disclaimer.
**
**  * Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
**
**  * Neither the name of the project's author nor the names of its
**    contributors may be used to endorse or promote products derived from
**    this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef EORMACTIVERECORD_H
#define EORMACTIVERECORD_H

#include "eorm_global.h"
#include "eorm.h"

/*!
 * \class EOrmActiveRecord
 *
 * \lang_en
 * \brief Implementation of a design pattern ActiveRecord. Class is abstract, so
 *  what to use it independently it will not turn out.
 *
 *  In child classes it is enough to redefine function tableName(), which
 *  should return a name of the table in QString. At necessities, it is
 *  possible to redefine also function primaryKeyName(), which should return
 *  the name of primary key. Also it are necessary call init() function i.e. in
 *  child constructor. Also if you don`t set QSqlDatabase object in constructor,
 *  EOrmActiveRecord use EOrm::activeConnection() for this. Example of usage:
 * \code
 *  // creation of new object
 *  Region *obj = new Region();
 *  // determination of attributes
 *  obj->setProperty("name", "Moscow");
 *  obj->setProperty("code", 77);
 *  // saving in database
 *  bool objOk = obj->save();
 *
 *
 *  // loading of exist object
 *  Region *obj = new Region(1);
 *  // display value of attribute
 *  qDebug() << obj->property("name").toString();
 *  // redefinition of value of attribute
 *  obj->setProperty("code", 199);
 *  // saving in database
 *  bool objOk = obj->save();
 *
 *
 *  // loading of exist object
 *  Region *obj = new Region(1);
 *  // removal of record form database
 *  bool objOk = obj->remove();
 *  // removal of object
 *  delete obj;
 * \endcode
 * \endlang
 *
 *
 * \lang_ru
 * \brief  Реализация шаблона проектирования ActiveRecord. Класс абстрактый, так
 *  что использовать его самостоятельно не получится.
 *
 *  В дочерних классах достаточно переопределить функцию tableName(),
 *  которая должна возвращать имя таблицы в виде объекта QString. При
 *  необходимости, можно также переопределить функцию primaryKeyName(), которая
 *  должна возвращать наименование первичного ключа. Также необходимо вызывать
 *  либо самостоятельно, либо для удобства в конструкторах дочерних классов
 *  вызывать функцию init(). Если создаваемому объекту не указать какой объект
 *  QSqlDatabase использовать, он будет получен используя функцию
 *  EOrm::activeConnection(). Пример использования:
 * \code
 *  // создание нового объекта
 *  Region *obj = new Region();
 *  // определение атрибутов
 *  obj->setProperty("name", "Moscow");
 *  obj->setProperty("code", 77);
 *  // сохранение в базу
 *  bool objOk = obj->save();
 *
 *
 *  // загрузка существующего объекта
 *  Region *obj = new Region(1);
 *  // отображение значение атрибута
 *  qDebug() << obj->property("name").toString();
 *  // переопределение значения атрибута
 *  obj->setProperty("code", 199);
 *  // запись в базу
 *  bool objOk = obj->save();
 *
 *
 *  // загрузка существующего объекта
 *  Region *obj = new Region(1);
 *  // удаление записи в базе
 *  bool objOk = obj->remove();
 *  // удаление объекта
 *  delete obj;
 * \endcode
 * \endlang
 */
class EORMSHARED_EXPORT EOrmActiveRecord : public QObject
{
    Q_OBJECT

public:
    explicit EOrmActiveRecord(QObject *parent = 0);
    /*!
     * \lang_en
     * \brief Pure virtual function which should return a name of the object
     *  table in database.
     * \return QString
     * \endlang
     *
     * \lang_ru
     * \brief Чистая виртуальная функция, которая должна возвращать имя таблицы
     *  объекта в базе.
     * \return QString
     * \endlang
     */
    virtual QString tableName() =0;
    virtual QString primaryKeyName();
    bool save(bool updateProperties = true);
    bool remove(bool updateProperties = true);
    bool load(QVariant primaryKey);
    bool clear();
    bool isRequired(QString propertyName);
    QHash<QString, QVariant> properties();
    QSqlDatabase db();
    QVariant pk();

protected:
    bool init();
    bool init(QVariant pk);
    bool init(QSqlDatabase db);
    bool init(QSqlDatabase db, QVariant pk);


private:
    bool preload();
    bool updateObject(QStringList properties, QVariantList values, bool updateProperties);
    bool insertObject(QStringList properties, QVariantList values, bool updateProperties);
    QVariant lastInsertId(QSqlQuery *insertQuery);
    QString placeholders(QVariantList list);

    QStringList m_properties;
    QStringList m_requiredProperties;
    QSqlDatabase m_db;
    QVariant m_pk;

};

#endif // EORMACTIVERECORD_H
