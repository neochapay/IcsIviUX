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

#include "SensorInfo.h"

SensorInfo::SensorInfo(Car::Sensor sensor,
                        QVariant::Type dataType,
                        const QString& variableName,
                        const QString& readableName,
                        const QVariant& min,
                        const QVariant& max,
                        const QString& units)
{  
   this->sensor = sensor;
   this->dataType = dataType;
   this->variableName = variableName;
   this->readableName = readableName;
   this->min = min;
   this->max = max;
   this->units = units;
}