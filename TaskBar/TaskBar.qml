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

Image {
   id: taskbar
   source: "images/toolbar_back.png"
   property alias appModel: appView.model
   property bool expanded: true
   state: "Expanded"

   Item
   {
      id: appMenuButton
      height: 50
      anchors.left: parent.left
      anchors.right: parent.right
      z: 1

      Image {
         anchors.centerIn: parent  
      }
   }

   Component {
         id: taskDelegate
         Item
         {
            id: delegate
            width: 100; height: 100

            Image {
               width: 48
               height: 48
               anchors.centerIn: parent
               source: pixmap
            }

            Text { 
                   text: name
                   color: "white"
                   font.family: "Tachoma"
                   font.pixelSize: 10
                   verticalAlignment: Text.AlignBottom
                   horizontalAlignment: Text.AlignHCenter
                   anchors.fill: parent
            }

            MouseArea {
               anchors.fill: parent;
               onClicked: { delegate.ListView.view.currentIndex = index; 
                            delegate.ListView.view.clicked(stateId) }
            }
         }
     }

      Component {
         id: highlight
         Item {
            width: 100; height: 100
            Image {
               id: highlightRect
               width: 100; height: 100
               anchors.fill: parent
               anchors.topMargin: 10
               anchors.bottomMargin: -10
               source: "images/selector.png"
            }
         }
 }

   ListView {
      id: appView
      signal clicked( string stateId )
      height: 500
      anchors.top: appMenuButton.bottom
      anchors.left: parent.left
      anchors.right: parent.right
      delegate: taskDelegate
      highlight: highlight
      highlightMoveDuration: 1000
      highlightMoveSpeed: -1
      highlightFollowsCurrentItem: true
      focus: true
      clip: true
      onClicked: { if(desktop.state != stateId) desktop.state = stateId }
   }

   Item {
      id: closeButton
      height: 50
      anchors.bottom: parent.bottom
      anchors.left: parent.left
      anchors.right: parent.right

      Image {
         anchors.centerIn: parent
      }
   }

   MouseArea {
      anchors.top: parent.top
      anchors.bottom: parent.bottom
      anchors.left: parent.left
      width: 10
      z: 200
      onClicked: {   if(taskbar.state == "Expanded")
                     {
                        mouse.accepted = true;
                        taskbar.state = "Collapsed" 
                     }
                 }
   }

   MouseArea {
      anchors.top: parent.top
      anchors.bottom: parent.bottom
      anchors.right: parent.right
      width: 10
      z: 200
      onClicked: {   if(taskbar.state == "Collapsed")
                     {
                        mouse.accepted = true;
                        taskbar.state = "Expanded" 
                     }
                 }
   }

   states:[ State {
              name: "Expanded"
              PropertyChanges { target: taskbar; x: 0 }
            },
            State {
              name: "Collapsed"
              PropertyChanges { target: taskbar; x: -90 }
           }]

      transitions: Transition {
         NumberAnimation { properties: "width,height,x,y"; duration: 1000; }
         NumberAnimation { properties: "opacity"; duration: 500 }
      }
}