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
   id:wrapper

   Component {
         id: stationDelegate
         Item {
             id:toplevel
             width: 180; height: 60
             Grid {
               columns: 3
               spacing: 5
   
               Image {
                 id: drag
                 anchors.verticalCenter: toplevel.vertcalCenter
                 source: "images/track_drag.png"
               }
               
               Image {
                 anchors.verticalCenter: drag.vertcalCenter
                 source: listIcon
               }
               Column {
                  Text { text: callSign; color: "#EEEEEE"; font.family: "Tachoma"; font.pixelSize: 20 }
                  Text { text: frequency; color: "#EEEEEE"; font.family: "Tachoma"; font.pixelSize: 15  }
               }
             }

             MouseArea {
                 id: mr
                 anchors.fill: parent
                 onClicked: { radioBackend.frequency = frequency }
             }
         }
     }

   ListView {
      id: stationList
      clip: true
      anchors.fill: parent
      model: fmStationModel
      delegate: stationDelegate
   }

}