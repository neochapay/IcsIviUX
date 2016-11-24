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

/*
*
* Posted to the qml-interest mailing list
*
*/

/* A flickable map item.
 * TODO: - Should expose some more properties
 *       - Needs a offset correction. The map position is the center of
 *         the map but the x/y values of Flickable are the upper left corner.
 */

import Qt 4.7
import QtMobility.location 1.1


Item {
    id: container
    property alias zoomLevel: map.zoomLevel

    Map {
        id: map
        anchors.fill: parent
        zoomLevel: 15
        mapType: Map.TerrainMap
    }

    Flickable {
        id: flickable
        anchors.fill: parent
        contentWidth: Math.pow(2, map.zoomLevel) * 256
        contentHeight: contentWidth
        onContentXChanged: panMap(contentX, contentY)
        onContentYChanged: panMap(contentX, contentY)

        function panMap(contentX, contentY) {
            var lon = xToLon(contentX, map.zoomLevel);
            var lat = yToLat(flickable.contentHeight - contentY, map.zoomLevel);
            var coord = Qt.createQmlObject('import QtMobility.location 1.1; Coordinate{latitude:' + lat + ';longitude:' + lon + ';}', container, "coord");
            map.center = coord;
        }
    }

    // Public function to set the position
    function setPosition(lat, lon) {
        var coord = Qt.createQmlObject('import QtMobility.location 1.1; Coordinate{latitude:' + lat + ';longitude:' + lon + ';}', container, "coord");
        map.center = coord;
        flickable.contentX = lonToX(lon, map.zoomLevel);
        flickable.contentY = latToY(lat, map.zoomLevel);
    }

    // Defaults to ICS Office Bedford, MA, USA
    Component.onCompleted: {
        //var lat = 42.5145;
        //var lon = -71.2415;
        //Vegas
        var lat = 36.132025;
        var lon = -115.15214;
        setPosition(lat, lon);
    }

    /* Convert functions between lat/lon and x/y values. Should probably
     * be inside a script file...
     * Taken from:
     * http://www.maptiler.org/google-maps-coordinates-tile-bounds-projection
     */

    function resolution(zoom) {
        var initialResolution = 2 * Math.PI * 6378137 / 256;
        return initialResolution / Math.pow(2, zoom);
    }

    function xToLon(px, zoom) {
        var res = resolution(zoom);
        var originShift = 2 * Math.PI * 6378137 / 2.0;
        var mx = px * res - originShift;
        var lon = (mx / originShift) * 180.0;
        return lon;
    }

    function yToLat(py, zoom) {
        var res = resolution(zoom);
        var originShift = 2 * Math.PI * 6378137 / 2.0;
        var my = py * res - originShift;
        var lat = (my / originShift) * 180.0;
        lat = 180 / Math.PI * (2 * Math.atan( Math.exp ( lat * Math.PI / 180.0)) - Math.PI / 2.0);
        return lat;
    }

    function lonToX(lon, zoom) {
        var res = resolution(zoom);
        var originShift = 2 * Math.PI * 6378137 / 2.0;
        var mx = lon * originShift / 180.0;
        var px = Math.round ((mx + originShift) / res);
        return px;
    }

    function latToY(lat, zoom) {
        var res = resolution(zoom);
        var originShift = 2 * Math.PI * 6378137 / 2.0;
        var my = Math.log( Math.tan((90 - lat) * Math.PI / 360.0 )) / (Math.PI / 180.0);
        my = my * originShift / 180.0;
        var py = Math.round ((my + originShift) / res);
        return py;
    }

}
