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
    width:924
    height:600
    Image {
        id:tacho_back
        source:"images/tacho_back.png"
        x:6
        y:100
        opacity:1
    }
    Image {
        id:tacho_gauge_ticks
        source:"images/tacho_gauge_ticks.png"
        x:25
        y:120
        opacity:1
    }
    Image {
        id:volt_needle_shadow
        smooth: true
        source:"images/volt_needle_shadow.png"
        x:157
        y:298
        opacity:0.8
        transform: Rotation {
            origin.x: 0; origin.y: 5
            angle: voltNeedleRotation.angle
        }
    }
    Image {
        id:tacho_needle_shadow
        smooth: true
        source:"images/tacho_needle_shadow.png"
        x:153
        y:134
        opacity:0.8
        transform: Rotation {
            origin.x: 10; origin.y: 120
            angle: tachoNeedleRotation.angle
        }
    }
    Image {
        id:volt_needle
        smooth: true
        source:"images/volt_needle.png"
        x:155
        y:296
        opacity:1
        transform: Rotation {
            id: voltNeedleRotation
            origin.x: 0; origin.y: 5
            angle: { -1*Math.min( 35, Math.max(-35, ( ((voltage.value-8) * (70/10)) - 35 ))) } //XXX Clean up
            Behavior on angle {
                SpringAnimation {
                    spring: 1.4
                    damping: .15
                }
            }
        }
    }
    Image {
        id:tacho_needle
        smooth: true
        source:"images/tacho_needle.png"
        x:152
        y:132
        opacity:1
        transform: Rotation {
            id: tachoNeedleRotation
            origin.x: 10; origin.y: 120
            angle: { Math.min( 83, Math.max(-117, ( (rpm.value * (200/8000)) - 117 ))) } //XXX Clean up
            Behavior on angle {
                SpringAnimation {
                    spring: 1.4
                    damping: .15
                }
            }
        }
    }
    Image {
        id:volt_needle_top
        source:"images/volt_needle_top.png"
        x:144
        y:282
        opacity:1
    }
    Image {
        id:tacho_needle_top
        source:"images/tacho_needle_top.png"
        x:136
        y:234
        opacity:1
    }
    Image {
        id:tacho_glare
        source:"images/tacho_glare.png"
        x:31
        y:125
        opacity:0.12156862745098
    }
    Image {
        id:third_gauge_back
        source:"images/third_gauge_back.png"
        x:605
        y:100
        opacity:1
    }
    Image {
        id:third_gauge_ticks
        source:"images/third_gauge_ticks.png"
        x:624
        y:120
        opacity:1
    }
    Image {
        id:temp_needle_shadow
        smooth: true
        source:"images/temp_needle_shadow.png"
        x:653
        y:253
        opacity:0.8
        transform: Rotation {
            origin.x: 90; origin.y: 5
            angle: tempNeedleRotation.angle
        }
    }
    Image {
        id:oil_needle_shadow
        smooth: true
        source:"images/oil_needle_shadow.png"
        x:759
        y:288
        opacity:0.8
        transform: Rotation {
            origin.x: 5; origin.y: 5
            angle: oilNeedleRotation.angle
        }
    }
    Image {
        id:turbo_needle_shadow
        smooth: true
        source:"images/turbo_needle_shadow.png"
        x:757
        y:150
        opacity:0.8
        transform: Rotation {
            origin.x: 5; origin.y: 65
            angle: boostNeedleRotation.angle
        }
    }
    Image {
        id:fuel_needle_shadow
        smooth: true
        source:"images/fuel_needle_shadow.png"
        x:795
        y:253
        opacity:0.8
        transform: Rotation {
            origin.x: 0; origin.y: 5
            angle: fuelNeedleRotation.angle
        }
    }
    Image {
        id:temp_needle
        smooth: true
        source:"images/temp_needle.png"
        x:649
        y:250
        opacity:1
        transform: Rotation {
            id: tempNeedleRotation
            origin.x: 90; origin.y: 5
            angle: { Math.min( 30, Math.max(-30, ( ((coolantTemperature.value-100) * (60/160)) - 30 ))) } //XXX Clean up
            Behavior on angle {
                SpringAnimation {
                    spring: 1.4
                    damping: .15
                }
            }
        }
    }
    Image {
        id:oil_needle
        smooth: true
        source:"images/oil_needle.png"
        x:756
        y:287
        opacity:1
        transform: Rotation {
            id: oilNeedleRotation
            origin.x: 5; origin.y: 5
            angle: { -1*Math.min( 30, Math.max(-30, ( ((oilPressure.value) * (60/80)) - 30 ))) } //XXX Clean up
            Behavior on angle {
                SpringAnimation {
                    spring: 1.4
                    damping: .15
                }
            }
        }
    }
    Image {
        id:fuel_needle
        smooth: true
        source:"images/fuel_needle.png"
        x:792
        y:250
        opacity:1
        transform: Rotation {
            id: fuelNeedleRotation
            origin.x: 0; origin.y: 5
            angle: { -1*Math.min( 30, Math.max(-30, ( ((fuelLevel.value) * (60/100)) - 30 ))) } //XXX Clean up
            Behavior on angle {
                SpringAnimation {
                    spring: 1.4
                    damping: .15
                }
            }
        }
    }
    Image {
        id:turbo_needle
        smooth: true
        source:"images/turbo_needle.png"
        x:756
        y:147
        opacity:1
        transform: Rotation {
            id: boostNeedleRotation
            origin.x: 5; origin.y: 65
            angle: { Math.min( 35, Math.max(-35, ( ((boost.value) * (70/20)) - 35 ))) } //XXX Clean up
            Behavior on angle {
                SpringAnimation {
                    spring: 1.4
                    damping: .15
                }
            }
        }
    }
    Image {
        id:oil_needle_top
        source:"images/oil_needle_top.png"
        x:746
        y:271
        opacity:1
    }
    Image {
        id:fuel_needle_top
        source:"images/fuel_needle_top.png"
        x:776
        y:241
        opacity:1
    }
    Image {
        id:temp_needle_top
        source:"images/temp_needle_top.png"
        x:713
        y:241
        opacity:1
    }
    Image {
        id:turbo_needle_top
        source:"images/turbo_needle_top.png"
        x:746
        y:191
        opacity:1
    }
    Image {
        id:third_gauge_glare
        source:"images/third_gauge_glare.png"
        x:630
        y:125
        opacity:0.12156862745098
    }
    Image {
        id:speedo_back
        source:"images/speedo_back.png"
        x:275
        y:145
        opacity:1
    }
    Image {
        id:speedo_ticks
        source:"images/speedo_ticks.png"
        x:296
        y:165
        opacity:1
    }
    Image {
        id:speedo_needle_shadow
        source:"images/speedo_needle_shadow.png"
        x:452
        y:174
        opacity:0.8
        transform: Rotation {
            origin.x: 10; origin.y: 160
            angle: needleRotation.angle
        }
    }
    Image {
        id:speedo_needle
        source:"images/speedo_needle.png"
        x:452
        y:172
        opacity:1
        smooth: true
        transform: Rotation {
            id: needleRotation
            origin.x: 10; origin.y: 160
            angle: { Math.min( 135, Math.max(-135, ( ((vehicleSpeed.value) * (270/120)) - 135 ))) } //XXX Clean up
            Behavior on angle {
                SpringAnimation {
                    spring: 1.4
                    damping: .15
                }
            }
        }
    }
    Image {
        id:speedo_needle_top
        source:"images/speedo_needle_top.png"
        x:433
        y:302
        opacity:1
    }
    Image {
        id:speedo_glare
        source:"images/speedo_glare.png"
        x:303
        y:172
        opacity:0.12156862745098
    }
    Image {
        id:tripometer_reset
        source:"images/tripometer_reset.png"
        x:404
        y:406
        opacity:1
    }
}
