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

#ifndef __MP3_PLAYER_H
#define __MP3_PLAYER_H

#include <QObject>

class Mp3Model;
class AlbumModel;
class Album;

class Mp3Player : public QObject
{
   Q_OBJECT
   Q_PROPERTY(QString album READ album WRITE setAlbum NOTIFY albumChanged)
   Q_PROPERTY(QString artwork READ artwork NOTIFY artworkChanged)

public:
   Mp3Player(QObject* parent = 0);

   AlbumModel* albumModel() const;
   Mp3Model*   mp3Model() const;

   QString album();
   void setAlbum(const QString album);

   QString artwork();

signals:
   void albumChanged(const QString& album);
   void artworkChanged(const QString& artwork);

protected:
   Mp3Model*    m_mp3Model;
   AlbumModel*  m_albumModel;

   Album* m_album;   // current album

};

#endif



 
