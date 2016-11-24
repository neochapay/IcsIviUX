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

/*
Each sensor enum has a matching variable name but with a lower case 1st letter.
To bind to a senor value use the following syntax:
myProperty: sensorName.value
There are also properties for min and max values

   Sensor Enum          Variable Name
-------------------------------------------
   VehicleSpeed         vehicleSpeed
   RPM                  rpm
   CoolantTemperature   coolantTemperature
   AmbientTemperature   ambientTemperature
   MAF                  maf
   MAP                  map
   OilPressure          oilPressure
   Voltage              voltage
   Boost                boost
   FuelLevel            fuelLevel
   FuelPressure         fuelPressure
*/

Image {
    id: window
    width: 924
    height: 600

   Image {
        id:ics_logo
        source:"images/ics_logo.png"
        x:770
        y:513
        opacity:1
    }

   Dashboard {
      id: dash
      x: 0
      y: 0
      width: parent.width
      height: parent.height
   
      MouseArea {
         property real pressX;
         anchors.fill: parent
         onPressed: pressX = mouse.x
         onPositionChanged:{ if(mouse.x < pressX){ window.state = 'diagState'} }
      }
   }


   Diag {
      id: diag
      x: 925
      y: 0
      opacity: 0
      width: parent.width
      height: parent.height

      MouseArea {
         property real pressX;
         anchors.fill: parent
         onPressed: pressX = mouse.x
         onPositionChanged:{ if(mouse.x > pressX){ window.state = 'dashState'} }
      }
   }

   Image {
      id: toDiag
      source: "images/sensors_arrow.png"
      x: 685
      y: 10

      Text {
         id: toDiagText
         x:45
         y:12
         text: "Sensors"
         color: "#242424"
         font.family: "Tachoma"
         font.pixelSize: 30
      }

      MouseArea {
         anchors.fill: parent
         onClicked: window.state = 'diagState'
         onPressed:{ toDiag.source = "images/sensors_arrow_pushed.png"
                     toDiagText.x = 47
                     toDiagText.y = 14 
                   }
         onReleased:{ toDiag.source = "images/sensors_arrow.png"
                      toDiagText.x = 45
                      toDiagText.y = 12 
                    }
      }
   }

   Image {
      id: toDash
      source: "images/dashboard_arrow.png"
      x: 5
      y: 10
      opacity: 0

      Text {
         id: toDashText
         x:35
         y:12
         text: "Dashboard"
         color: "#242424"
         font.family: "Tachoma"
         font.pixelSize: 30
      }

      MouseArea {
         anchors.fill: parent
         onClicked: window.state = 'dashState'
         onPressed:{ toDash.source = "images/dashboard_arrow_pushed.png"
                     toDashText.x = 37
                     toDashText.y = 14 
                   }
         onReleased:{ toDash.source = "images/dashboard_arrow.png"
                      toDashText.x = 35
                      toDashText.y = 12 
                    }
         z:100
      }
   }

   states:[ State {
              name: "dashState"  
              PropertyChanges { target: dash; x: 0; opacity: 1 }
              PropertyChanges { target: diag; x: 925; opacity: 0 }
              PropertyChanges { target: toDiag; opacity: 1 }
              PropertyChanges { target: toDash; opacity: 0 }
            },
            State {
              name: "diagState"
              PropertyChanges { target: dash; x: -925; opacity: 0}
              PropertyChanges { target: diag; x: 0; opacity: 1}
              PropertyChanges { target: toDash; opacity: 1 }
              PropertyChanges { target: toDiag; opacity: 0 }
           } ]
     
   transitions: Transition {
         SequentialAnimation {
            ParallelAnimation {
               NumberAnimation { target: dash; properties: "opacity"; from: 0; to: 1; duration: 0 }
               NumberAnimation { target: daig; properties: "opacity"; from: 0; to: 1; duration: 0 }
            }
            ParallelAnimation {
               NumberAnimation { properties: "x,y"; duration: 1000; }
               NumberAnimation { target: toDiag; properties: "opacity"; duration: 500 }
               NumberAnimation { target: toDash; properties: "opacity"; duration: 500 }
            }
            ParallelAnimation {
               NumberAnimation { target: dash; properties: "opacity"; from: 1; to: 0; duration: 0 }
               NumberAnimation { target: daig; properties: "opacity"; from: 1; to: 0; duration: 0 }
            }
         }
         
     }
}