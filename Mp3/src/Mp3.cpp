/*   
    Copyright (C) 2010,2011  Integrated Computer Solutions (ICS) www.ics.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Mp3.h"

Mp3::Mp3(QString title, QString artist, QObject* parent) :
   QObject(parent),
   m_title(title),
   m_artist(artist)
{
}

QString Mp3::title() const
{
   return m_title;
}

QString Mp3::artist() const
{
   return m_artist;
}

//Mp3::

Mp3Model::Mp3Model(QObject *parent)
    : QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[ArtistRole] = "artist";
    setRoleNames(roles);
}

int Mp3Model::rowCount(const QModelIndex & parent) const
{
    return m_list.count();
}

QVariant Mp3Model::data(const QModelIndex & index, int role) const
{
    if (index.row() < 0 || index.row() > m_list.count())
        return QVariant();

    Mp3* mp3 = m_list[index.row()];

    if (role == TitleRole)
        return mp3->title();
    else if (role == ArtistRole)
        return mp3->artist();

    return QVariant();
}

void Mp3Model::addMp3(Mp3* mp3)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    //m_list << station;
    m_list.append(mp3);
    endInsertRows();
}

bool Mp3Model::removeRows(int pos, int count, const QModelIndex & parent )
{
   beginRemoveRows(parent, pos, pos + count);

    for (int row=0; row < count; ++row) {
       m_list.removeAt(pos);
    }
    endRemoveRows();

   return true;
}

//Mp3Model::
