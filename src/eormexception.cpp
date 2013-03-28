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

#include "eormexception.h"

/*!
 * \lang_en
 * \brief Default constructor
 * \param message - error report
 * \param code - error code
 * \endlangg
 *
 * \lang_ru
 * \brief Стандартный конструктор исключения.
 * \param message - сообщение об ошибке
 * \param code - код ошибки
 * \endlang
 */
EOrmException::EOrmException(uint code, QString message)
{
    this->m_message = message;
    this->m_code = code;
}

/*!
 * \lang_en
 * \brief Function return error code
 * \return int
 * \endlang
 *
 * \lang_ru
 * \brief Функция возвращает код ошибки
 * \return int
 * \endlang
 */
int EOrmException::code()
{
    return this->m_code;
}

/*!
 * \lang_en
 * \brief Function return error message
 * \return QString
 * \endlang
 *
 * \lang_ru
 * \brief Функция возвращает сообщение об ошибки
 * \return QString
 * \endlang
 */
QString EOrmException::message()
{
    return this->m_message;
}
