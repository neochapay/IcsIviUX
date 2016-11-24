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

#ifndef ABSTRACTCOMM_H
#define ABSTRACTCOMM_H

#include <QObject>

#include "CommData.h"
#include "Car.h"

class AbstractComm : public QObject
{
   Q_OBJECT
public:
   AbstractComm(QObject* parent=0);
   
   virtual void init()=0;
   virtual void cleanup()=0;
   
   virtual QList<SensorInfo*> supportedSensors()=0;
   
   virtual void runCommand(Car::Command command)=0;
   
signals:
   void sensorDataChanged(const CommData& data);
   
};

#endif //ABSTRACTCOMM_H