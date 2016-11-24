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

#ifndef __MP3_K
#define __MP3_K

#include <QAbstractListModel>

class Mp3 : public QObject
{
   Q_OBJECT

public:
   Mp3(QString title, QString artist = QString(""), QObject* parent = 0);

   QString title() const;
   QString artist() const;

signals:
   void callTitleChanged(const QString&);

private:
   QString m_title;
   QString m_artist;

};

class Mp3Model : public QAbstractListModel
{
   Q_OBJECT

public:
    enum AlbumRoles {
        TitleRole = Qt::UserRole + 1,
        ArtistRole
    };

   Mp3Model(QObject* parent = 0);

   int rowCount(const QModelIndex & parent = QModelIndex()) const;

   void addMp3(Mp3* mp3);

   QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
   bool removeRows(int row, int count, const QModelIndex & index = QModelIndex() );

private:
   QList<Mp3*> m_list;

};

#endif
