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
        id: hSlider

        property alias imageSource: base.source
        property alias thumbSource:  thumb.source
        property alias background:  container.color

        property int value;
        property int maximum;

        signal valueChanged(int v);

        value:  1
        maximum:  100

        Rectangle {
          id:  container

          height:  thumb.height
          width:  base.width + thumb.width

          Image {
                id: base
                x:  thumb.width / 2
                y:  (thumb.height - base.height) / 2
          }
          Image {
                id: thumb
                x:  hSlider.value * parent.width / (maximum + thumb.width)
          }

          MouseArea {
             anchors.fill:  parent
             onPositionChanged: {

                if (mouse.x > 0 && mouse.x < (parent.width - thumb.width) ) thumb.x = mouse.x

                value = (thumb.x * (maximum + thumb.width) / parent.width)
                if (value > maximum) value = maximum

                hSlider.valueChanged(value)
             }
          }

      }  // Rectangle
}
