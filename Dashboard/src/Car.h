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

#ifndef CAR_H
#define CAR_H

#include <QObject>
#include <QVector>
#include <QVariant>

#include "CommData.h"

class SensorInfo;
class AbstractComm;

class Car : public QObject
{
   Q_OBJECT
   Q_ENUMS(Sensor)
   Q_ENUMS(Command)
   
public:
   //Add your new sensors here! Update registerAllSensors() too!
   enum Sensor {
               /*For Dashboard*/
               VehicleSpeed=0,
               Rpm,
               CoolantTemperature,
               OilPressure,
               Voltage,
               Boost,
               FuelLevel,
               /*MegaSquirt Specific*/
               InjectorPulseWidthBank1,
               InjectorPulseWidthBank2,
               Advance,
               InjectorStatus,
               EngineStatus,
               AfrTargetBank1,
               AfrTargetBank2,
               WideBandValidBank1,
               WideBandValidBank2,
               Barometer,
               Map,
               Mat,
               Tps,
               AfrBank1,
               AfrBank2,
               Knock,
               ExhaustGasCorrectionBank1,
               ExhaustGasCorrectionBank2,
               AirCorrection,
               WarmupEnrich,
               AccelEnrich,
               TpsFuelCutOff,
               BarometerCorrection,
               GammaEnrich,
               VeValueTable1,
               VeValueTable2,
               IacStep,
               ColdAdvance,
               TpsSlope,
               MapSlope,
               Dwell,
               Maf,
               FuelLoad,
               FuelCorrection,
               KnockRetard,
               EAEFuleCorr,
               EgoV,
               EgoV2,
               FuelLoadBank2,
               IgnitionLoadBank1,
               IgnitionLoadBank2,    
               NUM_SENSORS
               };
               
   enum Command {
                StartLiveData=0,
                StopLiveData,
                GetTroubleCodes,
                ResetTroubleCodes,
                NUM_COMMANDS
                };
   
   Car(QObject* parent=0);
   ~Car();
   
   void addComm(AbstractComm* comm);
   void removeComm(AbstractComm* comm);
   
public slots: //All invokable
   //Variants are easy for everyone
   void setSensorValue(Sensor sensor, const QVariant& value);
   QVariant sensorValue(Sensor sensor) const;
   
   QVariant::Type sensorDataType(Sensor sensor);
   QString sensorVariableName(Sensor sensor);
   QString sensorReadableName(Sensor sensor);
   QString sensorUnits(Sensor sensor);
   QVariant sensorMin(Sensor sensor);
   QVariant sensorMax(Sensor sensor);
   
   Sensor sensorFromVariableName(const QString& variableName);
   
signals:
   void sensorChanged(Car::Sensor sensor, const QVariant& value);
   
protected:
   void registerAllSensors();
   void registerSensor(Sensor sensor, QVariant::Type type,
                       const QString& variableName, const QString& readableName,
                       const QVariant& min, const QVariant& max,
                       const QString& units);
   
   //Catch dynamic property changes
   virtual bool event(QEvent* e);
   
protected slots:
   void handleSensorDataChanged(const CommData& data);
   
private:
   QList<AbstractComm*> m_comms;
   QVector<SensorInfo*> m_sensors;
   bool m_settingDynProp;
   
};

#endif //CAR_H