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
Rectangle {
    width:100
    height:600
    Image {
        id:toolbar_back
        source:"images/toolbar_back.png"
        x:0
        y:0
        opacity:1
    }
    Image {
        id:dashboard_icon
        source:"images/dashboard_icon.png"
        x:30
        y:376
        opacity:1
    }
    Image {
        id:sirius_icon
        source:"images/sirius_icon.png"
        x:30
        y:109
        opacity:1
    }
    Image {
        id:radio_icon
        source:"images/radio_icon.png"
        x:30
        y:20
        opacity:1
    }
    Text {
        id:radio
        text:"Radio"
        font.pixelSize:12
        font.family:"Tahoma"
        color:Qt.rgba(255,255,255, 1.0)
        smooth:true
        x:39
        y:69
        opacity:1
    }
    Text {
        id:sirius
        text:"Sirius"
        font.pixelSize:12
        font.family:"Tahoma"
        color:Qt.rgba(255,255,255, 1.0)
        smooth:true
        x:39
        y:159
        opacity:1
    }
    Text {
        id:mp3_player
        text:"MP3 Player"
        font.pixelSize:12
        font.family:"Tahoma"
        color:Qt.rgba(255,255,255, 1.0)
        smooth:true
        x:25
        y:247
        opacity:1
    }
    Text {
        id:map
        text:"Map"
        font.pixelSize:12
        font.family:"Tahoma"
        color:Qt.rgba(255,255,255, 1.0)
        smooth:true
        x:43
        y:337
        opacity:1
    }
    Text {
        id:dashboard
        text:"Dashboard"
        font.pixelSize:12
        font.family:"Tahoma"
        color:Qt.rgba(255,255,255, 1.0)
        smooth:true
        x:26
        y:425
        opacity:1
    }
    Image {
        id:mp3_icon
        source:"images/mp3_icon.png"
        x:30
        y:198
        opacity:1
    }
    Image {
        id:map_icon
        source:"images/map_icon.png"
        x:30
        y:287
        opacity:1
    }
}
