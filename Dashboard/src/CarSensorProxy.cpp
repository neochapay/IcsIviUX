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

#include "CarSensorProxy.h"

#include <QtDebug>

CarSensorProxy::CarSensorProxy(Car* car, Car::Sensor sensor, QObject* parent) :
   QObject(parent),
   m_car(car),
   m_sensor(sensor)
{
   connect(m_car, SIGNAL(sensorChanged(Car::Sensor, QVariant)),
           this, SLOT(handleSensorChanged(Car::Sensor, QVariant)));
}

void CarSensorProxy::setValue(const QVariant& value)
{
   m_car->setSensorValue(m_sensor, value);
}

QVariant CarSensorProxy::value() const
{
   return m_car->sensorValue(m_sensor);
}

int CarSensorProxy::type() const
{
   return m_car->sensorDataType(m_sensor);
}

QString CarSensorProxy::units() const
{
   return m_car->sensorUnits(m_sensor);
}

QString CarSensorProxy::readableName() const
{
   return m_car->sensorReadableName(m_sensor);
}

QVariant CarSensorProxy::min() const
{
   return m_car->sensorMin(m_sensor);
}

QVariant CarSensorProxy::max() const
{
   return m_car->sensorMax(m_sensor);
}

void CarSensorProxy::handleSensorChanged(Car::Sensor sensor, const QVariant& value)
{
   if(m_sensor == sensor)
   {
      emit valueChanged(value);
   }
}