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

#include "Mp3Player.h"
#include "Mp3.h"
#include "Album.h"

#include <QtDebug>

Mp3Player::Mp3Player(QObject* parent) :
   QObject(parent)
{
   m_albumModel = new AlbumModel();
   m_mp3Model = new Mp3Model( );

   // Test data
   Album* album = new Album("Unforgettable Fire", "U2", "images/UnforgettableFire.jpg");
   album->addSong(new Mp3("A Sort of Homecoming"));
   album->addSong(new Mp3("Pride (In the Name of Love)"));

   Album* album2 = new Album("The Joshua Tree", "U2", "images/JoshuaTree.jpg");
   album2->addSong(new Mp3("Where the Streets Have No Name"));
   album2->addSong(new Mp3("With or Without You"));

   m_albumModel->addAlbum(album);
   m_albumModel->addAlbum(album2);


   setAlbum("The Joshua Tree");

}


AlbumModel* Mp3Player::albumModel() const
{
   return m_albumModel;
}

Mp3Model* Mp3Player::mp3Model() const
{
   return m_mp3Model;
}

QString Mp3Player::album()
{

   if (m_album)
      return m_album->title();
   else
      return QString("");
}

QString Mp3Player::artwork()
{
   if (m_album)
      return m_album->artwork();
   else
      return QString("");
}

void Mp3Player::setAlbum(const QString album)
{

   m_album = m_albumModel->album(album);

   if (m_album)
      {
         m_mp3Model->removeRows(0, m_mp3Model->rowCount() );

         for (int i = 0; i < m_album->numSongs(); i++)
            {
               Mp3* mp3 = m_album->song(i);
               m_mp3Model->addMp3(mp3);
            }

         emit albumChanged(m_album->title());
         emit artworkChanged(m_album->artwork());
      }
}

//Mp3Player::
