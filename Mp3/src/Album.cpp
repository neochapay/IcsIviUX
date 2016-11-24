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

#include "Album.h"

Album::Album(QString title, QString artist, QString artwork, QObject* parent) :
   QObject(parent),
   m_title(title),
   m_artist(artist),
   m_artwork(artwork)
{
}

QString Album::title() const
{
   return m_title;
}

QString Album::artist() const
{
   return m_artist;
}

QString Album::artwork() const
{
   return m_artwork;
}

void Album::addSong(Mp3* song)
{
   m_songList.append(song);
}

int Album::numSongs()
{
   return m_songList.size();
}

Mp3* Album::song(int index)
{
   if (index < m_songList.size())
      return m_songList.at(index);
   else
      return 0;
}

//Album::

AlbumModel::AlbumModel(QObject *parent)
    : QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[ArtistRole] = "artist";
    roles[ArtworkRole] = "artwork";
    setRoleNames(roles);
}

int AlbumModel::rowCount(const QModelIndex & parent) const
{
    return m_list.count();
}

QVariant AlbumModel::data(const QModelIndex & index, int role) const
{
    if (index.row() < 0 || index.row() > m_list.count())
        return QVariant();

    //const Animal &animal = m_animals[index.row()];
    Album* album = m_list[index.row()];

    if (role == TitleRole)
        return album->title();
    else if (role == ArtistRole)
        return album->artist();
    else if (role == ArtworkRole)
        return album->artwork();

    return QVariant();
}

void AlbumModel::addAlbum(Album* album)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_list.append(album);
    endInsertRows();
}

Album* AlbumModel::album(const QString& name)
{

   QList<Album*>::const_iterator i;
   for (i = m_list.constBegin(); i != m_list.constEnd(); ++i)
      if ( ((Album*)(*i))->title() == name )
         return *i;

   return 0;
}

bool AlbumModel::removeRows(int pos, int count, const QModelIndex & parent )
{
   beginRemoveRows(parent, pos, pos + count);

   qDebug( QString("RemoveRows %1 %2").arg(pos).arg(count).toLatin1());

    for (int row=0; row < count; ++row) {
       m_list.removeAt(pos);
       qDebug( QString("Remove %1").arg(row).toLatin1());
    }
    endRemoveRows();

   return true;
}

//AlbumModel::
