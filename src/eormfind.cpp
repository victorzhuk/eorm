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

#include "eormfind.h"

/*!
 * \lang_en
 * \brief Default constructor, create empty object.
 * \endlang
 *
 * \lang_ru
 * \brief Стандартный конструктор, создает пустой объект.
 * \endlang
 */
EOrmFind::EOrmFind()
{
}

/*!
 * \lang_en
 * \brief Constructor with database object.
 * \param db - a database object
 * \param parent - parent object of QObject
 * \endlang
 *
 * \lang_ru
 * \brief Конструктор с указанием используемого объекта базы данных.
 * \param db - объект базы данных
 * \param parent - родительский объект QObject
 * \endlang
 */
EOrmFind::EOrmFind(QSqlDatabase db, QObject *parent) :
    QObject(parent)
{
    this->m_db = db;
    this->m_sqlQuery << "SELECT %1 FROM %2";
}

/*!
 * \lang_en
 * \brief Static function, create new EOrmFind object.
 * \return *EOrmFind
 * \endlang
 *
 * \lang_ru
 * \brief Статичная функция, предназначенная для того, чтобы не создавать каждый
 *  раз объект EOrmFind.
 * \return *EOrmFind
 * \endlang
 */
EOrmFind *EOrmFind::find()
{
    return new EOrmFind(EOrm::activeConnection());
}

/*!
 * \lang_en
 * \brief Function similar find(), but with database object.
 * \param db
 * \return *EOrmFind
 * \endlang
 *
 * \lang_ru
 * \brief Функция аналогичная find(), но с указанием используемого объекта базы
 *  данных.
 * \param db
 * \return *EOrmFind
 * \endlang
 */
EOrmFind *EOrmFind::find(QSqlDatabase db)
{
    return new EOrmFind(db);
}

/*!
 * \lang_en
 * \brief Function created sql-unit WHERE.
 *
 *  It are possible to call once before orderBy() and limit(). Otherwise empty
 *  EOrmFind () will be return.
 * \param sqlExpression - SQL expression WHERE
 * \return this
 * \endlang
 *
 * \lang_ru
 * \brief Функция создает sql-блок WHERE.
 *
 *  Можно вызвать единожды до вызова функций orderBy() и limit(). Иначе
 *  возвратится пустой EOrmFind().
 * \param sqlExpression - sql-выражение WHERE
 * \return this
 * \endlang
 */
EOrmFind *EOrmFind::where(QString sqlExpression)
{
    if (this->m_sqlQuery.count() == 1) {
        this->m_sqlQuery << QString("WHERE %1").arg(sqlExpression);
        return this;
    }
    return new EOrmFind();
}

/*!
 * \lang_en
 * \brief Function created sql-unit ORDER BY.
 *
 *  It are possible to call once before limit() and after a call of where().
 *  Otherwise empty EOrmFind() will be return.
 * \param sqlExpression - SQL expression ORDER BY
 * \return this
 * \endlang
 *
 * \lang_ru
 * \brief Функция создает sql-блок ORDER BY.
 *
 *  Можно вызвать единожды до вызова функций limit() и после вызова where().
 *  Иначе возвратится пустой EOrmFind().
 * \param sqlExpression - sql-выражение ORDER BY
 * \return this
 * \endlang
 */
EOrmFind *EOrmFind::orderBy(QString sqlExpression)
{
    if (this->m_sqlQuery.count() == 2) {
        this->m_sqlQuery << QString("ORDER BY %1").arg(sqlExpression);
        return this;
    }
    return new EOrmFind();
}

/*!
 * \lang_en
 * \brief Function created sql-unit limit().
 *
 *  It is possible to call once after a call of where() and orderBy(). Otherwise
 *  it will be return empty EOrmFind().
 * \param count - count of objects
 * \param offset - offset record number
 * \return this
 * \endlang
 *
 * \lang_ru
 * \brief Функция создает sql-блок limit().
 *
 *  Можно вызвать единожды после вызова where() и orderBy(). Иначе возвратится
 *  пустой EOrmFind().
 * \param count - колличество выбираемых объектов
 * \param offset - начиная с какой записи по счету выбирать объекты
 * \return this
 * \endlang
 */
EOrmFind *EOrmFind::limit(int count, int offset)
{
    if (this->m_sqlQuery.count() != 0) {
        this->m_sqlQuery << QString("LIMIT %1 OFFSET %2").arg(count).arg(offset);
        return this;
    }
    return new EOrmFind();
}
