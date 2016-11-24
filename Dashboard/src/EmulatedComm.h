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

#ifndef EMULATEDCOMM_H
#define EMULATEDCOMM_H

#include "AbstractComm.h"
#include "Car.h"

#include <QList>
#include <QVector>

class EmulatedComm : public AbstractComm
{
   Q_OBJECT
public:
   EmulatedComm(QObject* parent=0);
   
   virtual void init() { }
   virtual void cleanup() { }
   
   virtual QList<SensorInfo*> supportedSensors();
   
   virtual void runCommand(Car::Command) { };
   
protected slots:
   void updateSensorData();
   
   void loadSensorLoop();
   
private:   
QList<Car::Sensor> m_emulatedSensors;
QList< QVector<QVariant> > m_sensorLoop;
   
};

#endif //EMULATEDCOMM_H