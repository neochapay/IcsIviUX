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

#ifndef __ALBUM_H
#define __ALBUM_H

#include <QAbstractListModel>

class Mp3;

class Album : public QObject
{
   Q_OBJECT

public:

   Album(QString title, QString artist, QString artwork = QString(""), QObject* parent = 0);

   void addSong(Mp3*);
   Mp3* song(int);
   int numSongs();

   QString title() const;
   QString artist() const;
   QString artwork() const;

signals:
   void callTitleChanged(const QString&);
   void callArtistChanged(const QString&);

private:
   QString m_title;
   QString m_artist;
   QString m_artwork;

   QList<Mp3*> m_songList;
};

class AlbumModel : public QAbstractListModel
{
   Q_OBJECT

public:
    enum AlbumRoles {
        TitleRole = Qt::UserRole + 1,
        ArtistRole,
        ArtworkRole
    };

   AlbumModel(QObject* parent = 0);

   int rowCount(const QModelIndex & parent = QModelIndex()) const;

   void addAlbum(Album*);

   QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
   bool removeRows(int row, int count, const QModelIndex & index = QModelIndex() );

   Album* album(const QString& name);

private:
   QList<Album*> m_list;

};

#endif
