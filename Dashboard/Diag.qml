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

Item {
    id: window

   Component {
         id: diagDelegate
         Rectangle
         {
            width: 695; height: 49
            color: { (index % 2) ? "#E0E0E0" : "#D6D6D6" }
            Text { 
                   text: readableName
                   color: (value > max || value < min) ? "#AA0000" : "#262626"
                   font.family: "Tachoma"
                   font.pixelSize: 30
                   verticalAlignment: Text.AlignVCenter
                   x: parent.x + 20
                   anchors.bottom: parent.bottom
                   anchors.top: parent.top
                 }
            Text { 
                   text: NumberFormatter.format(value, type, 1)
                   color: (value > max || value < min) ? "#AA0000" : "#262626"
                   font.family: "Tachoma"
                   font.pixelSize: 30
                   verticalAlignment: Text.AlignVCenter
                   horizontalAlignment: Text.AlignRight
                   x: parent.x + parent.width - 110
                   width: 90
                   anchors.bottom: parent.bottom
                   anchors.top: parent.top
            }
         }
     }

   Image {
      width: 712
      height: 404
      source: "images/box.png"
      z: 50
      clip: true
      smooth: true
      anchors.centerIn: parent

      Rectangle {
      x: 6
      y: 5
      width: 695
      height: 388
      color: "#E0E0E0"
      border.color: "#E0E0E0"
      border.width: 1
      radius: 5
      z: 50
      clip: true

         ListView {
            x: 1
            y: 1
            width: 694
            height: 387
            id: diagList
            clip: true
            model: sensorModel;
            delegate: diagDelegate 
         }
      }       
   }
}