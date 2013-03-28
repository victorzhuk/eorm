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

#ifndef EORMFIND_H
#define EORMFIND_H

#include "eormactiverecord.h"

/*!
 * \class EOrmFind
 *
 * \lang_en
 * \brief Carry out search and select from database a collection of the given
 *  objects or the unique object by criterias.
 *
 *  That was release using template functions EOrmFind::all() and
 *  EOrmFind::one(). For example, we have a class "Test" inherited from
 *  EOrmActiveRecord. Then select of several objects of the "Test" type are
 *  carry out approximately so:
 * \code
 *  // set of objects
 *  QList<Test*> lst = EOrmFind::find()->where("id > 0 AND name = 'Victor'")
 *                                     ->orderBy("name, id DESC")
 *                                     ->limit(10)
 *                                     ->all<Test>();
 *
 *  // one object
 *  Test *testObj = EOrmFind::find()->where("othertable_id = 1")->one<Test>();
 * \endcode
 * \endlang
 *
 * \lang_ru
 * \brief Данный класс осуществляет поиск и выборку из базы коллекцию заданных
 *  объектов либо один единственный объект по критериям.
 *
 *  Реализуется данная возможность с помощью шаблонных функций EOrmFind::all() и EOrmFind::one().
 *  Например, у нас есть класс Test, который унаследован от EOrmActiveRecord.
 *  Тогда выбор нескольких объектов данного типа осуществляется примерно так:
 * \code
 *  // множество объектов
 *  QList<Test*> lst = EOrmFind::find()->where("id > 0 AND name = 'Victor'")
 *                                     ->orderBy("name,id DESC")
 *                                     ->limit(10)
 *                                     ->all<Test>();
 *
 *  // один объект
 *  Test *testObj = EOrmFind::find()->where("linkedtable_id = 1")->one<Test>();
 * \endcode
 * \endlang
 */
class EOrmFind : public QObject
{
    Q_OBJECT

public:
    explicit EOrmFind();
    explicit EOrmFind(QSqlDatabase db, QObject *parent = 0);
    template <typename T>
    QList<T*> all();
    template <typename T>
    T *one();
    static EOrmFind *find();
    static EOrmFind *find(QSqlDatabase db);
    EOrmFind *where(QString sqlExpression);
    EOrmFind *orderBy(QString sqlExpression);
    EOrmFind *limit(int count, int offset = 0);

private:
    QSqlDatabase m_db;
    QStringList m_sqlQuery;

};

/*!
 * \lang_en
 * \brief Template function, select objects list.
 *
 *  Execute generated SQL code, substitut a name of the table and
 *  primary key. Using for select multiple objects.
 * \return QList<T*>
 * \endlang
 *
 * \lang_ru
 * \brief Шаблонная функция выборки множества объектов.
 *
 *  Запускает сформированный SQL-код на выполнение, подставляя имя таблицы и
 *  первичный ключ. Используется для выборки множества объектов.
 * \return QList<T*>
 * \endlang
 */
template <typename T>
QList<T*> EOrmFind::all()
{
    QList<T*> objList;
    QString sql = this->m_sqlQuery.join(" ");
    if (sql.count() > 0) {
        T *obj = new T();
        if (obj->inherits("EOrmActiveRecord")) {
            QString pkName = obj->primaryKeyName();
            QString tableName = obj->tableName();
            delete obj;
            if (!pkName.isEmpty() && !tableName.isEmpty()) {
                QSqlQuery qr(sql.arg(pkName).arg(tableName), this->m_db);
                if (qr.isActive()) {
                    while (qr.next()) {
                        T *obj = new T(qr.record().value(pkName));
                        objList.append(obj);
                    }
                }
            }
        }
    }
    return objList;
}

/*!
 * \lang_en
 * \brief Template function, select one object.
 *
 *  Execute generated SQL code, substitut a name of the table and primary key.
 *  It is used for select of object, return the first satisfacted to conditions.
 * \return *T
 * \endlang
 *
 * \lang_ru
 * \brief Шаблонная функция выборки одного объекта.
 *
 *  Запускает сформированный SQL-код на выполнение, подставляя имя таблицы и
 *  первичный ключ. Используется для выборки одного объекта, возвращая первый
 *  удовлетворяющий условиям.
 * \return *T
 * \endlang
 */
template <typename T>
T *EOrmFind::one()
{
    QString sql = this->m_sqlQuery.join(" ");
    if (sql.count() > 0) {
        T *obj = new T();
        if (obj->inherits("EOrmActiveRecord")) {
            QString pkName = obj->primaryKeyName();
            QString tableName = obj->tableName();
            delete obj;
            if (!pkName.isEmpty() && !tableName.isEmpty()) {
                QSqlQuery qr(sql.arg(pkName).arg(tableName), this->m_db);
                if (qr.isActive() && qr.next()) {
                    T *obj = new T(qr.record().value(pkName));
                    return obj;
                }
            }
        }
    }
    return new T();
}

#endif // EORMFIND_H
