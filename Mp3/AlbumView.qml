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

import Qt 4.7

Item {
   id: albumViewWrapper

   Component {
         id: mp3ListDelegate

         Item {
             id: albumToplevel
             width: 180; height: 20
 
             Text { text: title; color: "#EEEEEE"; font.family: "Tachoma"; font.pixelSize: 20 }

         }

   }

   ListView {
      id: albumDetailView
      clip: true
      anchors.fill: parent
      model: mp3Model
      delegate:  mp3ListDelegate
   }

}
