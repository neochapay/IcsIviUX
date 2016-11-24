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
        id:channel_guide_back
        source:"images/channel_guide_back.png"
        x:646
        y:8
        opacity:1

        SiriusStationList
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
        id:siriusnowplaying_back
        source:"images/siriusnowplaying_back.png"
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

/*
    Image {
        id:tack_sep_2
        source:"images/tack_sep.png"
        x:659
        y:115
        opacity:1
    }
    Image {
        id:tack_sep_3
        source:"images/tack_sep.png"
        x:659
        y:65
        opacity:1
    }
    Text {
        id:category
        text:"Category"
        font.pixelSize:18
        font.family:"Tahoma"
        color:Qt.rgba(255,255,255, 1.0)
        smooth:true
        x:673
        y:80.5
        opacity:1
    }
    Image {
        id:right_arrow_3
        source:"images/right_arrow.png"
        x:884
        y:82
        opacity:1
    }
    Text {
        id:back
        text:"Back"
        font.pixelSize:18
        font.family:"Tahoma"
        color:Qt.rgba(199.996948242188,199.996948242188,199.996948242188, 1.0)
        smooth:true
        x:699
        y:39.5
        opacity:1
    }
    Image {
        id:back_arrow
        source:"images/back_arrow.png"
        x:672
        y:41
        opacity:1
    }
    Image {
        id:right_arrow_2
        source:"images/right_arrow.png"
        x:884
        y:133
        opacity:1
    }
*/
    Text {
        id:channel_guide__categories
        text:"Channel Guide: Categories"
        font.pixelSize:16
        font.family:"Tahoma"
        color: "#747474"
        smooth:true
        x:689
        y:11
        opacity:1
    }
    PushButton {
        id: control_button
        x: 71
        y: 223
        imageSource: "images/control_button.png"
        imagePushedSource: "images/control_button_pushed.png"
        iconSource:  "images/backward.png"
        imageDisabledSource: "images/backward_disabled.png"
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
        }

    }
    PushButton {
        id: control_button_2
        x: 192
        y: 223
        imageSource: "images/control_button.png"
        imagePushedSource: "images/control_button_pushed.png"
        iconSource:  "images/forward.png"
        imageDisabledSource: "images/forward_disabled.png"
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
        id:sirius_xm_hits_top_40_hits
        text:"SIRIUS XM HITS Top 40 Hits"
        font.pixelSize:24
        font.family:"Tahoma"
        color:Qt.rgba(255,255,255, 1.0)
        smooth:true
        x:223
        y:50
        opacity:1
    }
    Text {
        id:songTitle
        text:"Franz Ferdinand - Take Me Out"
        font.pixelSize:18
        font.family:"Tahoma"
        color:Qt.rgba(203.000383079052,203.000383079052,203.000383079052, 1.0)
        smooth:true
        x:223
        y:85.5
        opacity:1
    }
    Text {
        id:music
        text:"Music"
        font.pixelSize:18
        font.family:"Tahoma"
        color:Qt.rgba(147.999444007874,147.999444007874,147.999444007874, 1.0)
        smooth:true
        x:224
        y:116.5
        opacity:1
    }
    Text {
        id:pop
        text:"Pop"
        font.pixelSize:18
        font.family:"Tahoma"
        color:Qt.rgba(147.999444007874,147.999444007874,147.999444007874, 1.0)
        smooth:true
        x:330
        y:116.5
        opacity:1
    }
    Text {
        id:indexOfList
        text:"1 / 220"
        font.pixelSize:18
        font.family:"Tahoma"
        color:Qt.rgba(147.999444007874,147.999444007874,147.999444007874, 1.0)
        smooth:true
        x:225
        y:145.5
        opacity:1
    }
    PushButton {
        id: control_button_3
        x: 244
        y: 223
        imageSource:  "images/control_button.png"
        imagePushedSource:  "images/control_button_pushed.png"
        iconSource:  "images/next.png"
    }
    Image {
        id:radio_logo_nowplaying_back
        source:"images/radio_logo_nowplaying_back.png"
        x:22
        y:44
        opacity:1
    }
    PushButton {
        id: control_button_4
        x: 20
        y: 223
        imageSource:  "images/control_button.png"
        imagePushedSource:  "images/control_button_pushed.png"
        iconSource:  "images/previous.png"
    }
    Image {
        id:volume_icon
        source:"images/volume_icon.png"
        x:601
        y:234
        opacity:1
    }
    HorizontalSlider {
        x:468
        y:233
        value: 50
        imageSource:  "images/volume_status_indicator.png"
        thumbSource:  "images/volume_status_drag.png"
    }
    Image {
        id:layer_2
        source:"images/layer_2.png"
        x:192
        y:55
        opacity:1
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
        id:star_on
        source:"images/star_on.png"
        x:189
        y:174
        opacity:1
    }
    Image {
        id:star_on_2
        source:"images/star_on.png"
        x:214
        y:174
        opacity:1
    }
    Image {
        id:star_off
        source:"images/star_off.png"
        x:239
        y:174
        opacity:1
    }
    Image {
        id:star_off_2
        source:"images/star_off.png"
        x:264
        y:174
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
    PushButton {
        id: allpresets_button
        x: 463
        y: 556
        imageSource:  "images/allpresets_button.png"
        imagePushedSource:  "images/allpresets_button_pushed.png"
        text: "all presets"
        font.family:  "Tahoma"
        font.pixelSize:14
    }
    PushButton {
        id: toprated_button
        x: 546
        y: 556
        imageSource:  "images/toprated_button.png"
        imagePushedSource:  "images/toprated_button_pushed.png"
        text: "top rated"
        font.family:  "Tahoma"
        font.pixelSize:14
    }
    PushButton {
        id: dynamicart_button
        x: 20
        y: 556
        imageSource:  "images/dynamicart_button.png"
        imagePushedSource:  "images/dynamicart_button_pushed.png"
        text: "dynamic art"
        font.family:  "Tahoma"
        font.pixelSize:14
    }
    Image {
        id:stations_icon
        source:"images/stations_icon.png"
        x:661
        y:556
        opacity:1
    }
    Image {
        id:stations_icon_pushed
        source:"images/stations_icon_pushed.png"
        x:661
        y:556
        opacity:0
    }
    Image {
        id:home_icon
        source:"images/home_icon.png"
        x:675
        y:566
        opacity:1
    }
    PushButton {
        id: stations_button
        x: 855
        y: 556
        imageSource:  "images/stations_button.png"
        imagePushedSource:  "images/stations_button_pushed.png"
        iconSource: "images/stations_icon.png"
    }
    PushButton {
        id: stations_button_2
        x: 812
        y: 556
        imageSource:  "images/stations_button.png"
        imagePushedSource:  "images/stations_button_pushed.png"
        iconSource: "images/genre_icon.png"
    }
    PushButton {
        id: stations_button_3
        x: 768
        y: 556
        imageSource:  "images/stations_button.png"
        imagePushedSource:  "images/stations_button_pushed.png"
        iconSource: "images/category_icon.png"
    }
    Image {
        id:category_icon_light
        source:"images/category_icon_light.png"
        x:191
        y:117
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
        id:station_preset
        source:"images/station_preset.png"
        x:65
        y:357
        opacity:1
    }
    Text {
        id:_station
        text:"Station"
        font.pixelSize:12
        font.family:"Tahoma"
        color:Qt.rgba(157.997999489307,157.997999489307,157.997999489307, 1.0)
        smooth:true
        x:81
        y:471
        opacity:1
    }
    Text {
        id:nowplaying
        text:"Nowplaying"
        font.pixelSize:14
        font.family:"Tahoma"
        color:Qt.rgba(158.00055295229,158.00055295229,158.00055295229, 1.0)
        smooth:true
        x:70
        y:488.5
        opacity:1
    }
    Text {
        id:category___genre
        text:"Category / Genre"
        font.pixelSize:12
        font.family:"Tahoma"
        color:Qt.rgba(157.997999489307,157.997999489307,157.997999489307, 1.0)
        smooth:true
        x:60
        y:455
        opacity:1
    }
    Image {
        id:star_sm_on
        source:"images/star_sm_on.png"
        x:65
        y:508
        opacity:1
    }
    Image {
        id:star_sm_on_2
        source:"images/star_sm_on.png"
        x:81
        y:508
        opacity:1
    }
    Image {
        id:star_sm_on_3
        source:"images/star_sm_on.png"
        x:97
        y:508
        opacity:1
    }
    Image {
        id:star_sm_off
        source:"images/star_sm_off.png"
        x:113
        y:508
        opacity:1
    }
    Image {
        id:scroll_indicator
        source:"images/scroll_indicator.png"
        x:22
        y:542
        opacity:1
    }
    Image {
        id:sirius_logo_nowplaying
        source:"images/sirius_logo_nowplaying.png"
        x:32
        y:75
        opacity:1
    }
    Image {
        id:genre_icon_light
        source:"images/genre_icon_light.png"
        x:295
        y:119
        opacity:1
    }
    Image {
        id:ch_icon_light
        source:"images/ch_icon_light.png"
        x:193
        y:148
        opacity:1
    }
/*
    Image {
        id:tack_sep
        source:"images/tack_sep.png"
        x:659
        y:165
        opacity:1
    }
    Text {
        id:genre
        text:"Genre"
        font.pixelSize:16
        font.family:"Tahoma"
        color:Qt.rgba(255,255,255, 1.0)
        smooth:true
        x:673
        y:132
        opacity:1
    }
    Image {
        id:tack_sep_4
        source:"images/tack_sep.png"
        x:659
        y:215
        opacity:1
    }
    Text {
        id:station
        text:"Station"
        font.pixelSize:16
        font.family:"Tahoma"
        color:Qt.rgba(255,255,255, 1.0)
        smooth:true
        x:673
        y:174
        opacity:1
    }
    Text {
        id:description
        text:"Description"
        font.pixelSize:14
        font.family:"Tahoma"
        color:Qt.rgba(158.00055295229,158.00055295229,158.00055295229, 1.0)
        smooth:true
        x:674
        y:192.5
        opacity:1
    }
    Text {
        id:ch_0
        text:"CH 0"
        font.pixelSize:12
        font.family:"Tahoma"
        color:Qt.rgba(158.00055295229,158.00055295229,158.00055295229, 1.0)
        smooth:true
        x:871
        y:178
        opacity:1
    }
*/
}
