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


#include "CommData.h"

#include "Car.h"

CommData::CommData()
{
   qRegisterMetaType<CommData>("CommData");
}

void CommData::setSensorValue(int sensor, const QVariant& value)
{
   m_carData[sensor] = value;
}

QVariant CommData::sensorValue(int sensor) const
{
   return m_carData.value(sensor);
}

QMap<int,QVariant> CommData::sensorMap() const
{
   return m_carData;
}
