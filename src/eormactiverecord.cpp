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

#include "eormactiverecord.h"

/*!
 * \lang_en
 * \brief Сonstructor by default. Created empty object.
 * \param parent - parent object
 * \endlang
 *
 * \lang_ru
 * \brief Конструктор по-умолчанию. Создает пустой объект.
 * \param parent - родительский объект
 * \endlang
 */
EOrmActiveRecord::EOrmActiveRecord(QObject *parent) :
    QObject(parent)
{
    this->m_pk = QVariant();
}

/*!
 * \lang_en
 * \brief Function of initialization.
 *
 *  It is called in constructor of child classes for loading object properties.
 *  If there are the active connection with database, the main table and
 *  at least the one field in the table, returned TRUE, otherwise FALSE.
 * \return bool
 * \endlang
 *
 * \lang_ru
 * \brief Функция инициализации.
 *
 *  Вызывается в конструкторах дочерних классов для загрузки свойств
 *  объекта. Если существует активное соединение с базой, главная таблица и
 *  хотя бы одно поле в таблице, возвращается TRUE, в противном случае FALSE.
 * \return bool
 * \endlang
 */
bool EOrmActiveRecord::init()
{
    if (!this->m_db.isOpen()) {
        if (EOrm::activeConnection().isOpen()) {
            this->m_db = EOrm::activeConnection();
        }
    }
    if (this->preload()) {
        return true;
    }
    return false;
}

/*!
 * \lang_en
 * \brief Function init () with load properties values on the given primary key.
 *
 *  If the object with such primary key did not exist, FALSE is return.
 * \param pk - primary key
 * \return bool
 * \endlang
 *
 * \lang_ru
 * \brief Функция init(), дополнительно загружающая значения свойств по заданному
 *  первичному ключу.
 *
 *  Если объекта с таким первичным ключом не существует, возвращается FALSE.
 * \param pk - первичный ключ
 * \return bool
 * \endlang
 */
bool EOrmActiveRecord::init(QVariant pk)
{
    if (this->init()) {
        if (this->load(pk)) {
            return true;
        }
    }
    return false;
}

/*!
 * \lang_en
 * \brief Function init () with the set database object.
 * \param db - a database object
 * \return
 * \endlang
 *
 * \lang_ru
 * \brief Функция init() с указанием объекта базы данных.
 * \param db - объект базы данных
 * \return
 * \endlang
 */
bool EOrmActiveRecord::init(QSqlDatabase db)
{
    this->m_db = db;
    if (this->init()) {
        return true;
    }
    return false;
}

/*!
 * \lang_en
 * \brief Function init () with the set database object and primary key.
 * \param db - a database object
 * \param pk - primary key
 * \return bool
 * \endlang
 *
 * \lang_ru
 * \brief Функция init() с указанием объекта базы данных и первичного ключа.
 * \param db - объект базы данных
 * \param pk - первичный ключ
 * \return bool
 * \endlang
 */
bool EOrmActiveRecord::init(QSqlDatabase db, QVariant pk)
{
    this->m_db = db;
    if (this->init(pk)) {
        return true;
    }
    return false;
}

/*!
 * \lang_en
 * \brief The virtual function. Returned the name of primary key.
 * \return QString
 * \endlang
 *
 * \lang_ru
 * \brief Виртуальная функция. Возвращает наименование первичного ключа.
 * \return QString
 * \endlang
 */
QString EOrmActiveRecord::primaryKeyName()
{
    return this->db().primaryIndex(this->tableName()).name();
}

/*!
 * \lang_en
 * \brief Returned a database object.
 * \return QSqlDatabase
 * \endlang
 *
 * \lang_ru
 * \brief Возвращает объект базы данных.
 * \return QSqlDatabase
 * \endlang
 */
QSqlDatabase EOrmActiveRecord::db()
{
    return this->m_db;
}

/*!
 * \lang_en
 * \brief Returned primary key.
 * \return QVariant
 * \endlang
 *
 * \lang_ru
 * \brief Возвращает первичный ключ.
 * \return QVariant
 * \endlang
 */
QVariant EOrmActiveRecord::pk()
{
    return this->property(qPrintable(this->primaryKeyName()));
}

/*!
 * \lang_en
 * \brief Function of preloading, call at initialization.
 *
 *  Set connection with the table of a database, selected fields of the table
 *  and create similar properties of object. Returned FALSE if missed
 *  connection, the table or fields in the table.
 * \return bool
 * \endlang
 *
 * \lang_ru
 * \brief Функция предзагрузки, вызываемая при инициализации.
 *
 *  Выполняет соединение с таблицей базы данных, выбирает поля таблицы и
 *  создает аналогичные свойства объекта. Возвращает FALSE, если отсутствует
 *  соединение, таблица или поля в таблице.
 * \return bool
 * \endlang
 */
bool EOrmActiveRecord::preload()
{
    if (this->db().isOpen()) {
        if (this->db().tables().indexOf(this->tableName()) > -1) {
            int fields_count = this->db().record(this->tableName()).count();
            if (fields_count > 0) {
                for (int i = 0; i < fields_count; i++) {
                    QSqlField fd = this->db().record(
                                       this->tableName()).field(i);
                    this->setProperty(fd.name().toUtf8(), fd.value());
                    this->m_properties << fd.name().toUtf8();
                    if (fd.requiredStatus() != 0) {
                        this->m_requiredProperties << fd.name().toUtf8();
                    }
                }
                return true;
            } else {
                EOrm::throwError(3, "Init: Object properties "
                                 "are missing in table");
            }
        } else {
            EOrm::throwError(2, "Init: Object table is missing in databse");
        }
    } else {
        EOrm::throwError(1, "Init: Database connection failed");
    }
    return false;
}

/*!
 * \lang_en
 * \brief Function load values of object properties from the main table.
 * \param primaryKey - primary key
 * \return bool
 * \endlang
 *
 * \lang_ru
 * \brief Функция загрузки, выбирающая значения свойств объекта из таблицы.
 * \param primaryKey - первичный ключ
 * \return bool
 * \endlang
 */
bool EOrmActiveRecord::load(QVariant primaryKey)
{
    if (primaryKey.isValid()) {
        QStringList prop = this->m_properties;
        prop << this->primaryKeyName();
        QStringList sql;
        sql << "SELECT";
        sql << prop.join(",");
        sql << "FROM";
        sql << this->tableName();
        sql << "WHERE " << this->primaryKeyName() << "= ?";
        QSqlQuery qr(this->db());
        if (qr.prepare(sql.join(" "))) {
            qr.addBindValue(primaryKey);
            if (qr.exec()) {
                if (qr.size() != 0) {
                    while (qr.next()) {
                        for (int i = 0; i < prop.size(); ++i) {
                            QByteArray name = prop.at(i).toLocal8Bit()
                                              .constData();
                            QVariant value = qr.value(qr.record()
                                                      .indexOf(name));
                            this->setProperty(name, value);
                        }
                    }
                    this->m_pk = this->property(
                                     qPrintable(this->primaryKeyName()));
                    return true;
                } else {
                    if (qr.size() > 1) {
                        EOrm::throwError(7, "Load: Try to load more "
                                         "than one objects");
                    } else {
                        EOrm::throwError(8, "Load: Inactive or "
                                         "undefined result");
                    }
                }
            } else {
                EOrm::throwError(6, "Load: Execute query failed");
            }
        } else {
            EOrm::throwError(5, "Load: Prepare query failed");
        }
    } else {
        EOrm::throwError(4, "Load: Invalid primary key");
    }
    return false;
}

/*!
 * \lang_en
 * \brief Function reset values of all object properties.
 * \return bool
 * \endlang
 *
 * \lang_ru
 * \brief Функция сброса значений всех свойств объекта.
 * \return bool
 * \endlang
 */
bool EOrmActiveRecord::clear()
{
    this->m_pk = QVariant();
    for (int i = 0; i < this->m_properties.count(); i++) {
        this->setProperty(this->m_properties.value(i).toUtf8(), QVariant());
    }
    this->m_properties = QStringList();
    this->m_requiredProperties = QStringList();
    return true;
}

/*!
 * \lang_en
 * \brief Function remove object.
 *
 *  Thus the object is removed only from a database. If updateProperties are
 *  equal TRUE, object properties force updated.
 * \param updateProperties - reload properties from database, TRUE by default
 * \return bool
 * \endlang
 *
 * \lang_ru
 * \brief Функция удаления объекта.
 *
 *  При этом объект удаляется только из базы данных. Если updateProperties равен
 *  TRUE, также обновляются свойства у объекта, вызвавшего данную функцию.
 * \param updateProperties - перезагрузка свойств с базы, TRUE по-умолчанию
 * \return bool
 * \endlang
 */
bool EOrmActiveRecord::remove(bool updateProperties)
{
    QStringList sql;
    sql << "DELETE FROM";
    sql << this->tableName();
    sql << "WHERE";
    sql << this->primaryKeyName() + "= ?";
    this->db().transaction();
    QSqlQuery qr(this->db());
    if (qr.prepare(sql.join(" "))) {
        qr.addBindValue(this->m_pk);
        if (qr.exec()) {
            if (qr.numRowsAffected() == 1) {
                if (updateProperties) {
                    this->clear();
                }
                this->db().commit();
                return true;
            } else {
                if (qr.numRowsAffected() > 1) {
                    qr.finish();
                    this->db().rollback();
                    EOrm::throwError(11, "Remove: Try to delete more "
                                     "than one object");
                } else {
                    qr.finish();
                    this->db().rollback();
                    EOrm::throwError(12, "Remove: Object deleting failed");
                }
            }
        } else {
            qr.finish();
            this->db().rollback();
            EOrm::throwError(10, "Remove: Execute query failed");
        }
    } else {
        qr.finish();
        this->db().rollback();
        EOrm::throwError(9, "Remove: Prepare query failed");
    }
    qr.finish();
    this->db().rollback();
    return false;
}

/*!
 * \lang_en
 * \brief Function save object state inot database.
 *
 *  If such object does not exist in database it formed. In the opposite a case
 *  the data of object is updated. If updateProperties parameter is equal TRUE,
 *  after saving of object it`s properties will be force reloaded.
 * \param updateProperties - update properties, TRUE by default
 * \return bool
 * \endlang
 *
 * \lang_ru
 * \brief Функция сохрания объекта.
 *
 *  Если такого объекта не существует в базе, то он создается. В противном
 *  случае данные объекта обновляются. Если параметр updateProperties равен
 *  TRUE, после сохранения свойства объекта тут же снова загружаются. Это
 *  необходимо,например, при замене первичного ключа.
 * \param updateProperties - нужно ли обновлять свойства, TRUE по-умолчанию
 * \return bool
 * \endlang
 */
bool EOrmActiveRecord::save(bool updateProperties)
{
    QHash<QString, QVariant> properties = this->properties();
    QStringList propList;
    QVariantList propValues;
    bool withPrimaryKey = false;
    if (this->m_pk != this->property(
            this->primaryKeyName().toUtf8())) {
        withPrimaryKey = true;
    }
    QHashIterator<QString, QVariant> i(properties);
    while (i.hasNext()) {
        i.next();
        if (i.key() == this->primaryKeyName() && withPrimaryKey == false) {
            continue;
        }
        //! \todo add exception throwing if required key is empty
        if (this->m_requiredProperties.contains(i.key())
            && i.value().isNull()) {
            continue;
        }
        propList << i.key();
        propValues << i.value();
    }
    if (this->m_pk.isValid()) {
        if (this->updateObject(propList, propValues, updateProperties)) {
            return true;
        }
    } else {
        if (this->insertObject(propList, propValues, updateProperties)) {
            return true;
        }
    }
    return false;
}

/*!
 * \lang_en
 * \brief Update of object.
 *
 *  This function is called by save() function if current object already exists.
 *  If it is necessary to update properties, updateProperties are expos in TRUE.
 * \param properties - the list of update properties
 * \param values - the list of values of properties
 * \param updateProperties - reload of properties, TRUE by default
 * \return bool
 * \endlang
 *
 * \lang_ru
 * \brief Функция обновления объекта.
 *
 *  Данная функция вызывается функцией save(),если данный объект уже существует.
 *  Если его свойства необходимо обновить, updateProperties выставляется в TRUE.
 * \param properties - список обновляемых свойств
 * \param values - список значений свойств
 * \param updateProperties - перезагрузка свойств с базы, TRUE по-умолчанию
 * \return bool
 * \endlang
 */
bool EOrmActiveRecord::updateObject(QStringList properties, QVariantList values,
                                    bool updateProperties)
{
    QStringList sql;
    sql << "UPDATE";
    sql << this->tableName();
    sql << "SET";
    for (int i = 0; i < properties.count(); i++) {
        sql << properties.value(i) + " = ?";
        sql << ", ";
    }
    sql.removeLast();
    sql << "WHERE";
    sql << this->primaryKeyName() + " = ?";
    this->db().transaction();
    QSqlQuery qr(this->db());
    if (qr.prepare(sql.join(" "))) {
        for (int i = 0; i < values.count(); i++) {
            qr.addBindValue(values.value(i));
        }
        qr.addBindValue(this->m_pk);
        if (qr.exec()) {
            if (qr.numRowsAffected() > 0) {
                if (updateProperties) {
                    if (this->load(this->property(
                                       qPrintable(this->primaryKeyName())))) {
                        this->db().commit();
                        return true;
                    } else {
                        qr.finish();
                        this->db().rollback();
                        EOrm::throwError(21, "Update: Can not update "
                                         "properties state");
                    }
                } else {
                    QVariant newPk = this->property(
                                     qPrintable(this->primaryKeyName()));
                    if (newPk.isValid() && !newPk.isNull()) {
                        this->m_pk = newPk;
                        this->db().commit();
                        return true;
                    } else {
                        qr.finish();
                        this->db().rollback();
                        EOrm::throwError(22, "Update: New primary key NULL or"
                                         " invalid");
                    }
                }
            } else {
                qr.finish();
                this->db().rollback();
                EOrm::throwError(15, "Update: Object updating failed");
            }
        } else {
            qr.finish();
            this->db().rollback();
            EOrm::throwError(14, "Update: Execute query failed");
        }
    } else {
        qr.finish();
        this->db().rollback();
        EOrm::throwError(13, "Update: Prepare query failed");
    }
    qr.finish();
    this->db().rollback();
    return false;
}

/*!
 * \lang_en
 * \brief Insert new object.
 *
 *  It is call from function save() if the object does not exists in database.
 * \param properties - the list of update properties
 * \param values - the list of values of properties
 * \param updateProperties - reload of properties, TRUE by default
 * \return bool
 * \endlang
 *
 * \lang_ru
 * \brief Функция добавления объекта.
 *
 *  Вызывается из функции save(), если сохраняемого объекта не существует в базе.
 * \param properties - список обновляемых свойств
 * \param values - список значений свойств
 * \param updateProperties - перезагрузка свойств с базы, TRUE по-умолчанию
 * \return bool
 * \endlang
 */
bool EOrmActiveRecord::insertObject(QStringList properties, QVariantList values,
                                    bool updateProperties)
{
    QStringList sql;
    sql << "INSERT INTO";
    sql << this->tableName();
    sql << "(" + properties.join(",") + ")";
    sql << "VALUES";
    sql << "(" + this->placeholders(values) + ")";
    this->db().transaction();
    QSqlQuery qr(this->db());
    if (qr.prepare(sql.join(" "))) {
        for (int i = 0; i < values.count(); i++) {
            qr.addBindValue(values.value(i));
        }
        if (qr.exec()) {
            if (qr.numRowsAffected()) {
                if (updateProperties) {
                    if (this->load(this->lastInsertId(&qr))) {
                        this->db().commit();
                        return true;
                    } else {
                        qr.finish();
                        this->db().rollback();
                        EOrm::throwError(23, "Insert: Can not update "
                                         "properties state");
                    }
                } else {
                     QVariant newPk = this->lastInsertId(&qr);
                    if (newPk.isValid() && !newPk.isNull()) {
                        this->m_pk = newPk;
                        this->db().commit();
                        return true;
                    } else {
                        qr.finish();
                        this->db().rollback();
                        EOrm::throwError(24, "Insert: New primary key NULL or"
                                         " invalid");
                    }
                }
            } else {
                qr.finish();
                this->db().rollback();
                EOrm::throwError(18, "Insert: Object inserting failed");
            }
        } else {
            qr.finish();
            this->db().rollback();
            EOrm::throwError(17, "Insert: Execute query failed");
        }
    } else {
        qr.finish();
        this->db().rollback();
        EOrm::throwError(16, "Insert: Prepare query failed");
    }
    qr.finish();
    this->db().rollback();
    return false;
}

/*!
 * \lang_en
 * \brief Function substitute variables with placeholders.
 *
 *  Returned a line from "?", enumerat through a comma, an amount equal
 *  to an amount of lines in the list. It are necessary for convenience of
 *  operation with a database.
 * \param list - the list (as a rule properties of object)
 * \return QString
 * \endlang
 *
 * \lang_ru
 * \brief Функция замещения переменных плейсхолдерами.
 *
 *  Возвращает строчку из "?", перечисленных через запятую, количеством, равным
 *  количеству строчек в списке. Нужна для удобства работы с базой данных.
 * \param list - список (как правило свойств объекта)
 * \return QString
 * \endlang
 */
QString EOrmActiveRecord::placeholders(QVariantList list)
{
    QStringList phList;
    for (int i = 0; i < list.count(); i++) {
        phList << "?";
    }
    return phList.join(",");
}

/*!
 * \lang_en
 * \brief Returned the last inserted primary key.
 *
 *  Generally similar function exists in Qt, however by operation with
 *  the QPSQL driver it returned a little not that it are expected.
 * \param insertQuery - the link to request
 * \return QVariant
 * \endlang
 *
 * \lang_ru
 * \brief Ворзвращает последний вставленный первичный ключ.
 *
 *  Вообще подобная функция есть и стреди стандартных в Qt, однако при работе с
 *  драйвером QPSQL она возвращает немного не то, что ожидается.
 * \param insertQuery - ссылка на запрос
 * \return QVariant
 * \endlang
 */
QVariant EOrmActiveRecord::lastInsertId(QSqlQuery *insertQuery)
{
    if (this->db().driverName() == "QPSQL") {
        QString sql = QString("SELECT MAX(%1) FROM %2").arg(
                          this->primaryKeyName()).arg(this->tableName());
        QSqlQuery qr(this->db());
        if (qr.exec(sql)) {
            if (qr.size() == 1) {
                qr.next();
                return qr.value(0);
            } else {
                EOrm::throwError(20, "Last insert ID for QPSQL: Empty result");
            }
        } else {
            EOrm::throwError(19, "Last insert ID for QPSQL: "
                             "Execute query failed");
        }
    } else {
        return insertQuery->lastInsertId();
    }
    return QVariant();
}

/*!
 * \lang_en
 * \brief Function returned hash of properties of object.
 * \return QHash <QString, QVariant>
 * \endlang
 *
 * \lang_ru
 * \brief Функция возвращает хэш свойств объекта.
 * \return QHash<QString, QVariant>
 * \endlang
 */
QHash<QString, QVariant> EOrmActiveRecord::properties()
{
    QHash<QString, QVariant> propList;
    if (this->m_properties.count() > 0) {
        foreach (QString prop, this->m_properties) {
            propList.insert(prop, this->property(prop.toUtf8()));
        }
    }
    return propList;
}

/*!
 * \lang_en
 * \brief Function of check, whether are property mandatory
 *
 *  Function checked could or not property to accept null value.
 * \param propertyName - the name of property
 * \return bool
 * \endlang
 *
 * \lang_ru
 * \brief Функция проверки, является ли свойство обязательным.
 *
 *  Функция проверяет, является ли свойство необходимым, т.е. может оно
 *  или нет принимать нулевое значение.
 * \param propertyName - наименование свойства
 * \return bool
 * \endlang
 */
bool EOrmActiveRecord::isRequired(QString propertyName)
{
    return !(this->m_requiredProperties.indexOf(propertyName) == -1);
}
