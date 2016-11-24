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
             width: 180; height: 120
             Row
             {
               spacing: 5
               Image {
                  id: drag
                  source: "images/track_drag.png"
                  }

               Column {
                  spacing: 5
      
                  Row
                  {
                     spacing: 5
                     Image {
                        source: "images/stations/" + icon
                     }

                     Column
                     {
                        spacing:5
                        Text { text: number + " " + shortName; color: "#EEEEEE"; font.family: "Tachoma"; font.pixelSize: 15 }
                        Text { text: category; color: "#EEEEEE"; font.family: "Tachoma"; font.pixelSize: 15 }
                     }

                  }

                  Column {
                     spacing: 5
                     Text { text: artist; color: "#EEEEEE"; font.family: "Tachoma"; font.pixelSize: 18  }
                     Text { text: song; color: "#EEEEEE"; font.family: "Tachoma"; font.pixelSize: 16  }
                  }
               }
            }

            MouseArea {
                  id: mr
                  anchors.fill: parent
                  onClicked: { siriusBackend.currentStation = number }
               }
         }
     }

   ListView {
      id: stationList
      clip: true
      anchors.fill: parent
      model: siriusStationModel
      delegate: stationDelegate
   }

}