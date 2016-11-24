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
        id:mp3picker_back
        source:"images/mp3picker_back.png"
        x:646
        y:8
        opacity:1

        Mp3Picker {
        id:  mp3Picker
           anchors.fill: parent
           anchors.topMargin: 40
           anchors.leftMargin: 20
           anchors.bottomMargin: 50
           anchors.rightMargin: 25

        }

    }
    Image {
        id:mp3nowplaying_back
        source:"images/mp3nowplaying_back.png"
        x:5
        y:8
        opacity:1
    }
    Image {
        id:playlist_back
        source:"images/playlist_back.png"
        x:372
        y:282
        opacity:1
    }
    Image {
        id:lastfm_back
        source:"images/lastfm_back.png"
        x:5
        y:282
        opacity:1
    }
    Text {
        id:mp3_picker__all_songs
        text:"MP3 Picker: All Songs"
        font.pixelSize:16
        font.family:"Tahoma"
        color: "#747474"
        smooth:true
        x:707
        y:11
        opacity:1
    }
    Image {
        id:track_progress_bar
        source:"images/track_progress_bar.png"
        x:23
        y:191
        opacity:1
    }
    Image {
        id:track_progress
        source:"images/track_progress.png"
        x:23
        y:191
        opacity:1
    }
    Image {
        id:control_button
        source:"images/control_button.png"
        x:20
        y:223
        opacity:1
    }
    Image {
        id:control_button_pushed
        source:"images/control_button_pushed.png"
        x:20
        y:223
        opacity:0
    }
    PushButton {
        id: play_pause_button
        x: 71
        y: 223
        imageSource: "images/play_pause_button.png"
        imagePushedSource: "images/play_pause_button_copy.png"
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
    Image {
        id:previous
        source:"images/previous.png"
        x:35
        y:231
        opacity:1
    }
    Image {
        id:control_button_2
        source:"images/control_button.png"
        x:141
        y:223
        opacity:1
    }
    Image {
        id:control_button_copy_2
        source:"images/control_button_copy.png"
        x:141
        y:223
        opacity:0
    }
    Image {
        id:control_button_3
        source:"images/control_button.png"
        x:208
        y:223
        opacity:1
    }
    Image {
        id:control_button_copy_2_2
        source:"images/control_button_copy_2.png"
        x:208
        y:223
        opacity:0
    }
    Image {
        id:sh_rep_button
        source:"images/sh_rep_button.png"
        x:284
        y:226
        opacity:1
    }
    Image {
        id:sh_rep_button_pushed
        source:"images/sh_rep_button_pushed.png"
        x:284
        y:226
        opacity:0
    }
    Image {
        id:on
        source:"images/on.png"
        x:291
        y:234
        opacity:1
    }
    Image {
        id:off
        source:"images/off.png"
        x:291
        y:234
        opacity:0
    }
    Text {
        id:shuffle
        text:"shuffle"
        font.pixelSize:14
        font.family:"Tahoma"
        color: "#060606"
        smooth:true
        x:304
        y:231
        opacity:1
    }
    Image {
        id:sh_rep_button_2
        source:"images/sh_rep_button.png"
        x:365
        y:226
        opacity:1
    }
    Image {
        id:sh_rep_button_pushed_2
        source:"images/sh_rep_button_pushed.png"
        x:365
        y:226
        opacity:0
    }
    Image {
        id:on_2
        source:"images/on.png"
        x:372
        y:234
        opacity:1
    }
    Image {
        id:off_2
        source:"images/off.png"
        x:372
        y:234
        opacity:0
    }
    Text {
        id:repeat
        text:"repeat"
        font.pixelSize:14
        font.family:"Tahoma"
        color: "#060606"
        smooth:true
        x:386
        y:231
        opacity:1
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
        id:track_2
        text:"Track"
        font.pixelSize:24
        font.family:"Tahoma"
        color:Qt.rgba(255,255,255, 1.0)
        smooth:true
        x:222
        y:49
        opacity:1
    }
    Text {
        id:artist_2
        text:"Artist"
        font.pixelSize:18
        font.family:"Tahoma"
        color:Qt.rgba(203.000383079052,203.000383079052,203.000383079052, 1.0)
        smooth:true
        x:223
        y:86.5
        opacity:1
    }
    Text {
        id:album_2010
        text:"Album (2010)"
        font.pixelSize:18
        font.family:"Tahoma"
        color:Qt.rgba(147.999444007874,147.999444007874,147.999444007874, 1.0)
        smooth:true
        x:223
        y:115.5
        opacity:1
    }
    Image {
        id:tack_sep_2
        source:"images/tack_sep.png"
        x:385
        y:358
        opacity:1
    }
    Text {
        id:track_3
        text:"1. Track"
        font.pixelSize:16
        font.family:"Tahoma"
        color:Qt.rgba(255,255,255, 1.0)
        smooth:true
        x:416
        y:316
        opacity:1
    }
    Text {
        id:artist_3
        text:"Artist"
        font.pixelSize:14
        font.family:"Tahoma"
        color:Qt.rgba(158.00055295229,158.00055295229,158.00055295229, 1.0)
        smooth:true
        x:414
        y:335.5
        opacity:1
    }
    Text {
        id:time2
        text:"0:00"
        font.pixelSize:12
        font.family:"Tahoma"
        color:Qt.rgba(158.00055295229,158.00055295229,158.00055295229, 1.0)
        smooth:true
        x:598
        y:321
        opacity:1
    }
    Image {
        id:track_drag_2
        source:"images/track_drag.png"
        x:393
        y:331
        opacity:1
    }
    Text {
        id:playlist__further
        text:"Playlist: Further"
        font.pixelSize:16
        font.family:"Tahoma"
        color: "#747474"
        smooth:true
        x:454
        y:285
        opacity:1
    }
    Image {
        id:nowplaying_selection
        source:"images/nowplaying_selection.png"
        x:384
        y:359
        opacity:1
    }
    Image {
        id:playlist_play
        source:"images/playlist_play.png"
        x:608
        y:388
        opacity:0
    }
    Image {
        id:playlist_pause
        source:"images/playlist_pause.png"
        x:608
        y:388
        opacity:1
    }
    Image {
        id:tak_sep
        source:"images/tak_sep.png"
        x:385
        y:408
        opacity:1
    }
    Text {
        id:time3
        text:"00:00"
        font.pixelSize:12
        font.family:"Tahoma"
        color:Qt.rgba(158.00055295229,158.00055295229,158.00055295229, 1.0)
        smooth:true
        x:592
        y:371
        opacity:1
    }
    Image {
        id:track_drag_3
        source:"images/track_drag.png"
        x:393
        y:381
        opacity:1
    }
    Image {
        id:albumart
        source:"images/albumart.png"
        x:35
        y:45
        opacity:1
    }
    Image {
        id:cd
        source:"images/cd.png"
        x:25
        y:42
        opacity:1
    }
    Image {
        id:next
        source:"images/next.png"
        x:157
        y:231
        opacity:1
    }
    Image {
        id:progress_drag
        source:"images/progress_drag.png"
        x:580
        y:181
        opacity:1
    }
    Image {
        id:volume_icon
        source:"images/volume_icon.png"
        x:601
        y:234
        opacity:1
    }
    Image {
        id:volume_back
        source:"images/volume_back.png"
        x:468
        y:233
        opacity:1
    }
    Image {
        id:volume_status_indicator
        source:"images/volume_status_indicator.png"
        x:468
        y:233
        opacity:1
    }
    Image {
        id:volume_status_drag
        source:"images/volume_status_drag.png"
        x:577
        y:232
        opacity:1
    }
    Image {
        id:stop
        source:"images/stop.png"
        x:223
        y:231
        opacity:1
    }
    Text {
        id:twoTimes
        text:"0:35   6:21"
        font.pixelSize:15
        font.family:"Tahoma"
        color:Qt.rgba(134.999551177025,134.999551177025,134.999551177025, 1.0)
        smooth:true
        x:540
        y:160
        opacity:1
    }
    Image {
        id:music_icon_light
        source:"images/music_icon_light.png"
        x:192
        y:55
        opacity:1
    }
    Image {
        id:artist_icon_light
        source:"images/artist_icon_light.png"
        x:194
        y:87
        opacity:1
    }
    Image {
        id:album_icon_light
        source:"images/album_icon_light.png"
        x:192
        y:117
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
    Image {
        id:new_button
        source:"images/new_button.png"
        x:388
        y:557
        opacity:1
    }
    Image {
        id:new_button_pushed
        source:"images/new_button_pushed.png"
        x:388
        y:557
        opacity:0
    }
    Text {
        id:new1
        text:"new"
        font.pixelSize:14
        font.family:"Tahoma"
        color: "#060606"
        smooth:true
        x:393
        y:561
        opacity:1
    }
    Image {
        id:open_button
        source:"images/open_button.png"
        x:574
        y:557
        opacity:1
    }
    Image {
        id:open_button_pushed
        source:"images/open_button_pushed.png"
        x:574
        y:557
        opacity:0
    }
    Text {
        id:open
        text:"open"
        font.pixelSize:14
        font.family:"Tahoma"
        color: "#060606"
        smooth:true
        x:579
        y:561
        opacity:1
    }
    Image {
        id:save_button
        source:"images/save_button.png"
        x:528
        y:557
        opacity:1
    }
    Image {
        id:save_button_pushed
        source:"images/save_button_pushed.png"
        x:528
        y:557
        opacity:0
    }
    Text {
        id:save
        text:"save"
        font.pixelSize:14
        font.family:"Tahoma"
        color: "#060606"
        smooth:true
        x:532
        y:561
        opacity:1
    }
    Image {
        id:sort_button
        source:"images/sort_button.png"
        x:485
        y:557
        opacity:1
    }
    Image {
        id:sort_button_pushed
        source:"images/sort_button_pushed.png"
        x:485
        y:557
        opacity:0
    }
    Text {
        id:sort
        text:"sort"
        font.pixelSize:14
        font.family:"Tahoma"
        color: "#060606"
        smooth:true
        x:490
        y:561
        opacity:1
    }
    Text {
        id:lastfm
        text:"Last.fm"
        font.pixelSize:16
        font.family:"Tahoma"
        color: "#747474"
        smooth:true
        x:163
        y:285
        opacity:1
    }
    PushButton {
        id: biography_button
        x: 205
        y: 557
        imageSource:  "images/biography_button.png"
        imagePushedSource:  "images/biography_button_pushed.png"
        text: "biography"
        font.family:  "Tahoma"
        font.pixelSize:  14
    }
    PushButton {
        id: photos_button
        x: 287
        y: 557
        imageSource:  "images/photos_button.png"
        imagePushedSource:  "images/photos_button_pushed.png"
        text: "photos"
        font.family:  "Tahoma"
        font.pixelSize:  14
    }
    PushButton {
        id: picker_button
        x: 661
        y: 557
        imageSource:  "images/new_button.png"
        imagePushedSource:  "images/new_button_pushed.png"
        iconSource:  "images/home_icon.png"

        onClicked:  mp3Picker.pickerState = 'AlbumListState'
    }
    PushButton {
        id: picker_button_2
        x:  20
        y: 557
        imageSource:  "images/new_button.png"
        imagePushedSource:  "images/new_button_pushed.png"
        iconSource:  "images/home_icon.png"
    }
    Image {
        id:picker_button_3
        source:"images/picker_button.png"
        x:855
        y:557
        opacity:1
    }
    Image {
        id:picker_button_pushed_3
        source:"images/picker_button_pushed.png"
        x:855
        y:557
        opacity:0
    }
    PushButton {
        id: picker_button_4
        x: 812
        y: 557
        imageSource:  "images/picker_button.png"
        imagePushedSource:  "images/picker_button_pushed.png"
        iconSource:  "images/album_icon.png"
    }
    PushButton {
        id: picker_button_5
        x: 768
        y: 557
        imageSource:  "images/picker_button.png"
        imagePushedSource:  "images/picker_button_pushed.png"
        iconSource:  "images/artist_icon.png"
    }
    Image {
        id:track_icon
        source:"images/track_icon.png"
        x:867
        y:562
        opacity:1
    }
    Image {
        id:ontour
        source:"images/ontour.png"
        fillMode: Image.Stretch
        x:233
        y:315
        width:95
        height: 20
        opacity:1
    }
    Text {
        id:the_chemical_brothers__on_tour
        wrapMode: Text.Wrap
        text:"The Chemical Brothers  ON TOUR 32,535,760 plays (1,450,822 listeners) 135 plays in your library."
        font.pixelSize:16
        font.family:"Tahoma-Bold"
        font.bold:true
        color:Qt.rgba(255,255,255, 1.0)
        smooth:true
        x:25
        y:314.5
        width: 300
        height: 100
        opacity:1
    }
    Text {
        id:the_chemical_brothers__on_tour_2
        wrapMode: Text.Wrap
        text:"Manchester, England (1992 Ã¢ÂÂ present) The Chemical Brothers are a British electronic music duo comprising Tom Rowlands and Ed Simons, who met at the University of Manchester, England in 1992. Initially they called themselves The Dust Brothers."
        font.pixelSize:10
        font.family:"Tahoma-Bold"
        font.bold:true
        color:Qt.rgba(255,255,255, 1.0)
        smooth:true
        x:25
        y:480
        width: 300
        height: 200
        opacity:1
    }
    Image {
        id:img1
        source:"images/img1.png"
        x:27
        y:391
        opacity:1
    }
    Image {
        id:img2
        source:"images/img2.png"
        x:137
        y:391
        opacity:1
    }
    Image {
        id:img3
        source:"images/img3.png"
        x:208
        y:391
        opacity:1
    }
    Text {
        id:track2
        text:"2. Track"
        font.pixelSize:16
        font.family:"Tahoma"
        color:Qt.rgba(255,255,255, 1.0)
        smooth:true
        x:414
        y:366
        opacity:1
    }
    Text {
        id:artist_copy
        text:"Artist"
        font.pixelSize:14
        font.family:"Tahoma"
        color:Qt.rgba(158.00055295229,158.00055295229,158.00055295229, 1.0)
        smooth:true
        x:414
        y:385.5
        opacity:1
    }
}
