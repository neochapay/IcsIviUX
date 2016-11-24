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

import "../Components"

Item {
        id:  pickerWrapper
        width:  parent.width
        clip:  true

        property alias pickerState:  pickerWrapper2.state

    Item {
        id:  pickerWrapper2
        height:  parent.height
        width:  albumListWrapper.width + songListWrapper.width
        clip:  true

        Rectangle {
           id:  albumListWrapper
           height:  parent.height
           width:  pickerWrapper.width
           color:  "black"
           //color:  "red"

           AlbumList
           {
              id: albumList
              anchors.fill: parent
           }

        Rectangle {
           id:  songListWrapper
           color:  "black"
           height:  parent.height
           width:  pickerWrapper.width
           anchors.left:  albumListWrapper.right
        }

        MouseArea {
              id: mouseArea
              anchors.fill:parent
              onClicked: {
                pickerWrapper2.state = 'SongListState'
                }
        }

        }

        states:[ State {
              name: "AlbumListState"
              PropertyChanges { target: pickerWrapper2; x: 0 }
            },
           State {
              name: "SongListState"
              PropertyChanges { target: pickerWrapper2; x: -albumListWrapper.width }
           }]

   transitions: Transition {
      SequentialAnimation {
         NumberAnimation { target: pickerWrapper2; properties: "x,y"; duration: 250; }
      }
   }

  }
}