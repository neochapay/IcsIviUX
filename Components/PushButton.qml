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
        id: pushable

        property alias imageSource: base.source
        property alias imagePushedSource: pressed.source
        property alias imageDisabledSource: disabled.source
        property alias iconSource:  icon.source
        property alias text:  text.text
        property alias font:  text.font

        property bool pressed;
        property bool enabled;

        enabled:  true

        signal clicked()

        Rectangle {
          id:  container

          height:  base.height
          width:  base.width

          Image {
                id: disabled
                opacity:  0
          }
          Image {
                id: base
          }
          Image {
                id: pressed
          }
          Image {
                id:  icon
                x:  base.width / 2 - icon.width / 2
                y:  base.height / 2 - icon.height / 2
          }
          Text {
               id:  text
               x:  base.width / 2 - text.width / 2
               y:  base.height / 2 - text.height / 2
          }
          MouseArea {
                id: mouseArea
                anchors.fill:  parent
                onClicked:  pushable.clicked()
           }

        }

       states {
          State {
             name:  "base"
             when: mouseArea.pressed == false
             PropertyChanges { target: base; opacity:  1; }
             PropertyChanges { target: pressed; opacity:  0; }
             PropertyChanges { target: pushable; pressed:  0 }
          }
          State {
             name:  "pressed"
             when: mouseArea.pressed == true && pushable.enabled == true
             PropertyChanges { target: base; opacity:  0; }
             PropertyChanges { target: pressed; opacity:  1; }
             PropertyChanges { target: pushable; pressed:  1 }
          }
          State {
             name:  "disabled"
             when: mouseArea.pressed == true
             PropertyChanges { target: base; opacity:  0; }
             PropertyChanges { target: pressed; opacity:  1; }
             PropertyChanges { target: pushable; pressed:  1 }
          }
       }
}
