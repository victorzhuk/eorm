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

#include "eorm.h"

/*!
 * \lang_en
 * \brief Initialization of a name of connection with a database.
 * \endlang
 *
 * \lang_ru
 * \brief Инициализация имени соединения с базой данных.
 * \endlang
 */
QString EOrm::m_connectionName = QString();

/*!
 * \lang_en
 * \brief Function returned the set name of connection with a database.
 * \return QString
 * \endlang
 *
 * \lang_ru
 * \brief Функция возвращает заданное имя соединения с базой данных.
 * \return QString
 * \endlang
 */
QString EOrm::connectionName()
{
    return EOrm::m_connectionName;
}

/*!
 * \lang_en
 * \brief Installation of a name of connection with a database.
 * \param connectionName - name of connection
 * \endlang
 
 * \lang_ru
 * \brief Установка имени соединения с базой данных.
 * \param connectionName - имя соединения
 * \endlang
 */
void EOrm::setConnectionName(QString connectionName)
{
    EOrm::m_connectionName = connectionName;
}

/*!
 * \lang_en
 * \brief Function returned object of QSqlDatabase by name of connections.
 *
 *  The name of connection gave from function of EOrm::connectionName. If the name are not set, connection by default are use.
 * \return QSqlDatabase
 * \endlang
 *
 * \lang_ru
 * \brief Функция возвращает объект QSqlDatabase по имени соединения.
 *
 *  Имя соединения берется из функции EOrm::connectionName. Если имя не заданно,
 *  используется соединение по-умолчанию.
 * \return QSqlDatabase
 * \endlang
 */
QSqlDatabase EOrm::activeConnection()
{
    const char *connection_name = QSqlDatabase::defaultConnection;
    if (!EOrm::connectionName().isEmpty()) {
        connection_name = qPrintable(EOrm::connectionName());
    }
    if (QSqlDatabase::contains(connection_name)) {
        return QSqlDatabase::database(connection_name);
    } else {
        return QSqlDatabase();
    }
}

/*!
 * \lang_en
 * \brief Function of generation of errors.
 *
 *  As the notification about errors the mechanism of exceptions are use.
 * \param code - an error code
 * \param message - an error message, unessential parameter
 * \endlang
 *
 * \lang_ru
 * \brief Function of generation of errors.
 *
 *  В качестве оповещения об ошибках используется механизм исключений.
 * \param code - код ошибки
 * \param message - сообщение об ошибке, необязательный параметр
 * \endlang
 */
void EOrm::throwError(uint code, QString message)
{
    throw new EOrmException(code, message);
}
