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
import "TaskBar"
import "Radio"
import "Sirius"
import "Maps"
import "Dashboard"
import "Mp3"

Image {
   id: desktop
   width: 1024
   height: 600
   source: "background.png"
   state: "RadioState"

   ListModel {
      id: apps

     ListElement {
         name: "Radio"
         pixmap: "images/radio_icon.png"
         stateId: "RadioState" 
     }
     ListElement {
         name: "Sirius"
         pixmap: "images/sirius_icon.png"
         stateId: "SiriusState" 
     }
     ListElement {
         name: "Mp3 Player"
         pixmap: "images/mp3_icon.png"
         stateId: "Mp3State" 
     }
     ListElement {
         name: "Maps"
         pixmap: "images/map_icon.png"
         stateId: "MapsState" 
     }
     ListElement {
         name: "Dashboard"
         pixmap: "images/dashboard_icon.png"
         stateId: "DashboardState" 
     }

   }

   TaskBar {
      id: taskBar
      x: 0
      y: 0
      z: 100
      width: 100
      height: 600
      appModel: apps
   }

   Item {
      id: appWrapperScale
      width: 924
      height: 600

      Item {
         id: appWrapperYPos
         width: 924
         height: 600

         Item {
            id: radio
            x: 100
            y: 0
            width: 924
            height: 600

            Radio {
               anchors.centerIn: parent
               width: 924
               height: 600
            }
         }

         Item {
            id:sirius
            x: 100
            y: 600 * 1 + 1;
            width: 924
            height: 600
            
            Sirius {
               anchors.centerIn: parent
               width: 924
               height: 600
            }
         }

         Item {
            id: mp3
            x: 100;
            y: 600 * 2 + 1;
            width: 924
            height: 600
            
            Mp3 {
               anchors.centerIn: parent
               width: 924
               height: 600
            }
         } 

         Item {
            id: maps
            x: 100;
            y: 600 * 3 + 1;
            width: 924
            height: 600
            
            Maps {
               anchors.fill: parent
            }
         }

         Item {
            id: dashboard
            x: 100;
            y: 600 * 4 + 1
            width: 924
            height: 600
            
            MegaDash {
               anchors.fill: parent
            }

         }
      }
   }

   states:[ State {
              name: "RadioState"
              PropertyChanges { target: appWrapperYPos; y: 0 }
            },
            State {
              name: "SiriusState"
              PropertyChanges { target: appWrapperYPos; y: -600 }
           }, 
           State {
              name: "Mp3State"
              PropertyChanges { target: appWrapperYPos; y: -600*2 }
           },
           State {
              name: "MapsState"
              PropertyChanges { target: appWrapperYPos; y: -600*3 }
           },
           State {
              name: "DashboardState"
              PropertyChanges { target: appWrapperYPos; y: -600*4 }
           }]

   transitions: Transition {
      SequentialAnimation {
         NumberAnimation { target: appWrapperScale; property: "scale"; to: 0.5; duration: 250 }
         NumberAnimation { properties: "x,y"; duration: 250; }
         NumberAnimation { target: appWrapperScale; property: "scale"; to: 1; duration: 250 }
      }
   }
}
