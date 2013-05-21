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

#ifndef EORMMODEL_H
#define EORMMODEL_H

#include "eorm_global.h"
#include "eormactiverecord.h"

/*!
 * \class EOrmModel
 *
 * \lang_en
 * \brief Class, capable to create Qt-compatible data model (while only
 *  for reading).
 *
 *  For this purpose it is necessary function set data using setData() function
 *  with object list. Example:
 * \code
 *  QList<Test*> lst = EOrmFind::find()->all<Test>();
 *  EOrmModel *model = new EOrmModel;
 *  model->setData(lst);
 * \endcode
 * \endlang
 *
 * \lang_ru
 * \brief Класс, способный создавать Qt-совместимую модель данных (пока только
 *  для чтения).
 *
 *  Для этого необходимо в функцию setData() передать
 *  список объектов, реализующих ActiveRecord. Пример релизации:
 * \code
 *  QList<Test*> lst = EOrmFind::find()->all<Test>();
 *  EOrmModel *model = new EOrmModel;
 *  model->setData(lst);
 * \endcode
 * \endlang
 */
class EORMSHARED_EXPORT EOrmModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit EOrmModel(QObject *parent = 0);
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    template <typename T>
    void setData(QList<T*> objList);

private:
    QList<EOrmActiveRecord*> m_objList;
    QList<QString> m_fieldsList;

};

/*!
 * \lang_en
 * \brief Template function for loading of the object list in model for display
 * \endlang
 *
 * \lang_ru
 * \brief Шаблонная функция загрузки списка объектов в модель для отображения
 * \endlang
 */
template <typename T>
void EOrmModel::setData(QList<T*> objList)
{
    T *firstObj = objList.at(0);
    this->m_objList << firstObj;
    this->m_fieldsList = firstObj->properties().keys();
    this->m_fieldsList.removeAt(this->m_fieldsList.indexOf(firstObj->
                                                           primaryKeyName()));
    this->m_fieldsList.prepend(firstObj->primaryKeyName());
    for (int i = 1; i < objList.count(); i++) {
        T * obj = objList.at(i);
        this->m_objList << obj;
    }
}

#endif // EORMMODEL_H
