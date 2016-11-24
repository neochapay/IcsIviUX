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

#ifndef CARSENSORPROXY_H
#define CARSENSORPROXY_H

#include <QObject>
#include <QVariant>
#include "Car.h"

class CarSensorProxy : public QObject
{
   Q_OBJECT
   Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
   Q_PROPERTY(QString readableName READ readableName NOTIFY unitsChanged)
   Q_PROPERTY(QString units READ units NOTIFY valueChanged)
   Q_PROPERTY(QVariant min READ min NOTIFY minChanged)
   Q_PROPERTY(QVariant max READ max NOTIFY maxChanged)
   Q_PROPERTY(int type READ type NOTIFY typeChanged)
public:   
   CarSensorProxy(Car* car, Car::Sensor sensor, QObject* parent=0);

   void setValue(const QVariant& value);
   QVariant value() const;
   
   QString readableName() const;
   QString units() const;
   QVariant min() const;
   QVariant max() const;
   int type() const;

signals:
   void valueChanged(const QVariant& value);
   void minChanged(const QVariant& value);
   void maxChanged(const QVariant& value);
   void unitsChanged(const QVariant& value);
   void typeChanged(int value);
   
protected slots:
   void handleSensorChanged(Car::Sensor sensor, const QVariant& value);
   
private:
   Car* m_car;
   Car::Sensor m_sensor;
};

#endif //CARSENSORPROXY_H