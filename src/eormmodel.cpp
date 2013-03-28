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

#include "eormmodel.h"

/*!
 * \lang_en
 * \brief Default constructor, create empty object.
 * \param parent - parent QObject
 * \endlang
 *
 * \lang_ru
 * \brief Стандартный конструктор, создает пустой объект.
 * \param parent - родительский QObject
 * \endlang
 */
EOrmModel::EOrmModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

/*!
 * \lang_en
 * \brief Redefine function. Create an index on a line and a column.
 * \param row - row number
 * \param column - column number
 * \param parent - a parent index
 * \return QModelIndex
 * \endlang
 *
 * \lang_ru
 * \brief Переопределенная функция. Создает индекс по строке и столбцу.
 * \param row - номер строки
 * \param column - номер столбца
 * \param parent - родительский индекс
 * \return QModelIndex
 * \endlang
 */
QModelIndex EOrmModel::index(int row, int column,
                             const QModelIndex &parent) const
{
    return this->createIndex(row, column);
}

/*!
 * \lang_en
 * \brief Redefine function. Returned a parent index.
 * \param child - a child index
 * \return QModelIndex
 * \endlang
 *
 * \lang_ru
 * \brief Переопределенная функция. Возвращает родительский индекс.
 * \param child - дочерний индекс
 * \return QModelIndex
 * \endlang
 */
QModelIndex EOrmModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

/*!
 * \lang_en
 * \brief Redefine function. Returned rows count.
 * \param parent - a parent index
 * \return int
 * \endlang
 *
 * \lang_ru
 * \brief Переопределенная функция. Возвращает число срок.
 * \param parent - родительский индекс
 * \return int
 * \endlang
 */
int EOrmModel::rowCount(const QModelIndex &parent) const
{
    return this->m_objList.count();
}

/*!
 * \lang_en
 * \brief Redefine function. Returned columns count.
 * \param parent - a parent index
 * \return int
 * \endlang
 *
 * \lang_ru
 * \brief Переопределенная функция. Возвращает число столбцов.
 * \param parent - родительский индекс
 * \return int
 * \endlang
 */
int EOrmModel::columnCount(const QModelIndex &parent) const
{
    return this->m_fieldsList.count();
}

/*!
 * \lang_en
 * \brief Redefine function. Returned cell value by index.
 * \param index - an index
 * \param role - type of display
 * \return QVariant
 * \endlang
 *
 * \lang_ru
 * \brief Переопределенная функция. Возвращает значение ячейки по индексу.
 * \param index - индекс
 * \param role - тип отображения
 * \return QVariant
 * \endlang
 */
QVariant EOrmModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        if (index.row() < this->m_objList.size()) {
            if (role == Qt::DisplayRole) {
                EOrmActiveRecord *obj = this->m_objList.at(index.row());
                return obj->property(this->m_fieldsList.at(
                                         index.column()).toUtf8());
            }
        }
    }
    return QVariant();
}

/*!
 * \lang_en
 * \brief Redefine function. Returned a column header.
 * \param section - column number
 * \param orientation - a direction of an inscription
 * \param role - type of display
 * \return QVariant
 * \endlang
 *
 * \lang_ru
 * \brief Переопределенная функция. Возвращает заголовок столбца.
 * \param section - номер столбца
 * \param orientation - направление надписи
 * \param role - тип отображения
 * \return QVariant
 * \endlang
 */
QVariant EOrmModel::headerData(int section,
                               Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole) {
            return QString("%1").arg(this->m_fieldsList.at(section));
        }
    }
    return QVariant();
}
