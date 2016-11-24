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
    width:924
    height:600
    Image {
        id:background
        x:0
        y:0
    }
    Image {
        id:station_list_back
        source:"images/station_list_back.png"
        x:646
        y:8
        opacity:1

        StationList
        {
           id: stationList
           anchors.fill: parent
           anchors.topMargin: 33
           anchors.leftMargin: 20
           anchors.bottomMargin: 50
           anchors.rightMargin: 25
        }

    }
    Image {
        id:nowplaying_back
        source:"images/nowplaying_back.png"
        x:5
        y:8
        opacity:1
    }
    Image {
        id:presets_back
        source:"images/presets_back.png"
        x:5
        y:282
        opacity:1
    }
    Text {
        id:station_list
        text:"Station List"
        font.pixelSize:16
        font.family:"Tahoma"
        color: "#747474"
        smooth:true
        x:744
        y:11
        opacity:1
    }
    Image {
        id:volume_icon
        source:"images/volume_icon.png"
        x:608
        y:234
        opacity:1
    }
    HorizontalSlider {
        x:463
        y:233
        value: 50
        imageSource:  "images/volume_status_indicator.png"
        thumbSource:  "images/volume_status_drag.png"
    }

    Text {
        id:now_playing
        text:"Now Playing"
        font.pixelSize:16
        font.family:"Tahoma"
        color: "#747474"
        smooth:true
        x:282
        y:11
        opacity:1
    }
    Text {
        id:nowPlayingStation
        text: radioBackend.callSign
        font.pixelSize:24
        font.family:"Tahoma"
        color:Qt.rgba(255,255,255, 1.0)
        smooth:true
        x:223
        y:50
        opacity:1
    }
    Text {
        id:nowPlayingFreq
        text:{ radioBackend.frequency + " FM" }
        font.pixelSize:18
        font.family:"Tahoma"
        color:Qt.rgba(147.999444007874,147.999444007874,147.999444007874, 1.0)
        smooth:true
        x:225
        y:115.5
        opacity:1
    }
    Text {
        id:beastie_boys_intergalactic
        text:"Beastie Boys - Intergalactic"
        font.pixelSize:18
        font.family:"Tahoma"
        color:Qt.rgba(203.000383079052,203.000383079052,203.000383079052, 1.0)
        smooth:true
        x:224
        y:85.5
        opacity:1
    }
    Image {
        id:overflower
        source:"images/overflower.png"
        x:861
        y:60
        opacity:1
    }
    Image {
        id:radio_logo_nowplaying_back
        source:"images/radio_logo_nowplaying_back.png"
        x:22
        y:43
        opacity:1

        Image {
           id:radio_logo_nowplaying
           source:radioBackend.stationArt
           anchors.centerIn: parent
           opacity:1
        }
    }
    Image {
        id:station_icon
        source:"images/station_icon.png"
        x:191
        y:56
        opacity:1
    }
    Image {
        id:artisttrack_icon
        source:"images/artisttrack_icon.png"
        x:194
        y:87
        opacity:1
    }
    Image {
        id:scale_icon
        source:"images/scale_icon.png"
        x:192
        y:124
        opacity:1
    }
    Image {
        id:star_on
        source:"images/star_on.png"
        x:189
        y:145
        opacity:1
    }
    Image {
        id:star_on_2
        source:"images/star_on.png"
        x:214
        y:145
        opacity:1
    }
    Image {
        id:star_off
        source:"images/star_off.png"
        x:239
        y:145
        opacity:1
    }
    Image {
        id:star_off_2
        source:"images/star_off.png"
        x:264
        y:145
        opacity:1
    }
    Text {
        id:presets
        text:"Presets"
        font.pixelSize:16
        font.family:"Tahoma"
        color: "#747474"
        smooth:true
        x:300
        y:285
        opacity:1
    }
    Image {
        id:allpresets
        source:"images/allpresets.png"
        x:465
        y:556
        opacity:1

        Text {
          id:all_presets
          text:"all presets"
          font.pixelSize:14
          font.family:"Tahoma"
          color:"#060606"
          smooth:true
          anchors.centerIn: parent
          opacity:1
       }
    }
    Image {
        id:allpresets_pushed
        source:"images/allpresets_pushed.png"
        x:465
        y:556
        opacity: 0
    }
      Image {
         id:toprated
         source:"images/toprated.png"
         x:548
         y:556
         opacity:1

         Text {
         id:top_rated
         text:"top rated"
         font.pixelSize:14
         font.family:"Tahoma"
         color:"#060606"
         smooth:true
         anchors.centerIn: parent
         opacity:1
      }
    }
    Image {
        id:toprated_pushed
        source:"images/toprated_pushed.png"
        x:548
        y:556
        opacity:0
    }
    Image {
        id:amfm
        source:"images/amfm.png"
        x:814
        y:556
        opacity:1
    }
    Image {
        id:amfm_2
        source:"images/amfm.png"
        x:857
        y:556
        opacity:1
    }
    Image {
        id:amfm_pushed
        source:"images/amfm_pushed.png"
        x:857
        y:556
        opacity:0
    }
    Image {
        id:amfm_pushed_2
        source:"images/amfm_pushed.png"
        x:814
        y:556
        opacity:0
    }
    Image {
        id:fm
        source:"images/fm.png"
        x:867
        y:564
        opacity:1
    }
    Image {
        id:am
        source:"images/am.png"
        x:822
        y:564
        opacity:1
    }
    Image {
        id:radio_logo_bg
        source:"images/radio_logo_bg.png"
        x:32
        y:327
        opacity:1
    }
    Image {
        id:radio_logo
        source:"images/radio_logo.png"
        x:47
        y:369
        opacity:1
    }
    Image {
        id:scale_back
        source:"images/scale_back.png"
        x:19
        y:176
        opacity:1
    }
    Text {
        id:_radio_name
        text:"Emerson Radio"
        font.pixelSize:12
        font.family:"Tahoma"
        color: "#9E9E9E"
        smooth:true
        x:58
        y:471
        opacity:1
    }
    Text {
        id:nowplaying
        text:"Ben Fold's Five"
        font.pixelSize:14
        font.family:"Tahoma"
        color: "#EEEEEE"
        smooth:true
        x:55
        y:488.5
        opacity:1
    }
    Text {
        id:zero_fm
        text:"88.9 FM"
        font.pixelSize:12
        font.family:"Tahoma"
        color: "#9E9E9E"
        smooth:true
        x:80
        y:455
        opacity:1
    }
    Image {
        id:scale
        source:"images/scale.png"
        x:26
        y:182
        opacity:1
    }
    Image {
        id:scale_indicator
        source:"images/scale_indicator.png"
        x:434
        y:182
        opacity:1
    }
    Image {
        id:star_sm_on
        source:"images/star_sm_on.png"
        x:75
        y:508
        opacity:1
    }
    Image {
        id:star_sm_on_2
        source:"images/star_sm_on.png"
        x:91
        y:508
        opacity:1
    }
    Image {
        id:star_sm_on_3
        source:"images/star_sm_on.png"
        x:107
        y:508
        opacity:1
    }
    Image {
        id:star_sm_off
        source:"images/star_sm_off.png"
        x:123
        y:508
        opacity:1
    }
    Image {
        id:scroll_indicator
        source:"images/scroll_indicator.png"
        x:22
        y:542
        opacity:0
    }
    Image {
        id:scale_tune_bg
        source:"images/scale_tune_bg.png"
        x:307
        y:228
        opacity:1
    }
    Image {
        id:scale_tune_move
        source:"images/scale_tune_move.png"
        x:313
        y:234
        opacity:1
    }
    PushButton {
        id: play_pause_button
        x: 122
        y: 223
        imageSource: "images/play_pause_button.png"
        imagePushedSource: "images/play_pause_button_pushed.png"
        iconSource:  "images/pause.png"

        property bool playing;
        playing:  false

        onClicked: {
            if (playing == true)
              {
                iconSource = "images/pause.png"
                playing = false
              }
            else
              {
                iconSource = "images/play.png"
                playing = true
              }
        radioBackend.playing == true ? radioBackend.stop() : radioBackend.start()
        }
    }
    Image {
        id:control_button
        source:"images/control_button.png"
        x:192
        y:223
        opacity:1
    }
    Image {
        id:control_button_pushed
        source:"images/control_button_pushed.png"
        x:192
        y:223
        opacity:0
    }
    Image {
        id:forward
        source:"images/forward.png"
        x:204
        y:231
        opacity:1
    }
    Image {
        id:control_button_2
        source:"images/control_button.png"
        x:243
        y:223
        opacity:1
    }
    Image {
        id:control_button_pushed_2
        source:"images/control_button_pushed.png"
        x:243
        y:223
        opacity:0
    }
    Image {
        id:next
        source:"images/next.png"
        x:259
        y:231
        opacity:1
    }
    Image {
        id:control_button_3
        source:"images/control_button.png"
        x:71
        y:223
        opacity:1
    }
    Image {
        id:control_button_pushed_3
        source:"images/control_button_pushed.png"
        x:71
        y:223
        opacity:0
    }
    Image {
        id:backward
        source:"images/backward.png"
        x:81
        y:232
        opacity:1
    }
    Image {
        id:control_button_4
        source:"images/control_button.png"
        x:20
        y:223
        opacity:1
    }
    Image {
        id:control_button_pushed_4
        source:"images/control_button_pushed.png"
        x:20
        y:223
        opacity:0
    }
    Image {
        id:previous
        source:"images/previous.png"
        x:35
        y:231
        opacity:1
    }
}
