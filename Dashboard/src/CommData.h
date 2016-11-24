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

#ifndef COMMDATA_H
#define COMMDATA_H

#include <QVariant>

//This class used ints rather than Car::Sensor to avoid circular dependancy
//This class also uses a map for speed nad  since it can send less than all sensors

class CommData
{
public:   
   CommData();
   
   void setSensorValue(int, const QVariant& value);
   QVariant sensorValue(int sensor) const;
   QMap<int,QVariant> sensorMap() const;
   
private:
   QMap<int,QVariant> m_carData;
   
};
Q_DECLARE_METATYPE(CommData);

#endif //ECUCOMMDATA_H