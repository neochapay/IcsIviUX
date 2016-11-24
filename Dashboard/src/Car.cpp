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

#include "Car.h"

#include <limits.h>

#include <QDynamicPropertyChangeEvent>
#include <QDebug>

#include "SensorInfo.h"
#include "AbstractComm.h"

Car::Car(QObject* parent) :
   QObject(parent),
   m_settingDynProp(false)
{
   registerAllSensors();
}

Car::~Car()
{
   qDeleteAll(m_sensors);
}

void Car::addComm(AbstractComm* comm)
{
   if( 0 != comm &&
       false == m_comms.contains(comm) )
   {
      m_comms << comm;
      connect( comm, SIGNAL(sensorDataChanged(CommData)),
               this, SLOT(handleSensorDataChanged(CommData)) );
   }
}

void Car::removeComm(AbstractComm* comm)
{
   m_comms.removeAll(comm);
   disconnect( comm, SIGNAL(sensorDataChanged(CommData)),
               this, SLOT(handleSensorDataChanged(CommData)) );
}

void Car::handleSensorDataChanged(const CommData& data)
{
   QMapIterator<int,QVariant> it(data.sensorMap());
   while(it.hasNext())
   {
      it.next();
      setSensorValue((Sensor)it.key(), it.value());  
   }
}

void Car::setSensorValue(Sensor sensor, const QVariant& value)
{
   //Only do real changes
   if(m_sensors[sensor]->value != value)
   {
      m_sensors[sensor]->value = value;
      m_settingDynProp = true;
      setProperty(qPrintable(m_sensors[sensor]->variableName), m_sensors[sensor]->value);
      m_settingDynProp = false;
      emit sensorChanged(sensor, value);
   }
}

QVariant Car::sensorValue(Sensor sensor) const
{
   return m_sensors[sensor]->value;
}

QVariant::Type Car::sensorDataType(Sensor sensor)
{
   return m_sensors[sensor]->dataType;
}

QString Car::sensorVariableName(Sensor sensor)
{
   return m_sensors[sensor]->variableName;
}

QString Car::sensorReadableName(Sensor sensor)
{
   return m_sensors[sensor]->readableName;
}

QString Car::sensorUnits(Sensor sensor)
{
   return m_sensors[sensor]->units;
}

QVariant Car::sensorMin(Sensor sensor)
{
   return m_sensors[sensor]->min;
}

QVariant Car::sensorMax(Sensor sensor)
{
   return m_sensors[sensor]->max;
}

Car::Sensor Car::sensorFromVariableName(const QString& variableName)
{
   foreach(SensorInfo* info, m_sensors)
   {
      if(info->variableName == variableName)
      {
         return info->sensor;
      }
   }
   
   return NUM_SENSORS;
}

bool Car::event(QEvent* e)
{
   //Catch dynamic property changed
   if(e->type() == QEvent::DynamicPropertyChange&&
      false == m_settingDynProp)
   {
      QDynamicPropertyChangeEvent* dpe = static_cast<QDynamicPropertyChangeEvent*>(e);
      QString sensorName =  dpe->propertyName();
      Sensor sensor = sensorFromVariableName(sensorName);
      setSensorValue(sensor, property(qPrintable(sensorName)));
   }
   
   return QObject::event(e);
}

void Car::registerSensor(Sensor sensor, QVariant::Type type,
                        const QString& variableName, const QString& readableName,
                        const QVariant& min, const QVariant& max,
                        const QString& units)
{
   SensorInfo* info = new SensorInfo(sensor, type, variableName, readableName, min, max, units);
   info->value = QVariant(type); //Load with proper type
   m_sensors[sensor] = info;
   //Add dynamic property so things can be addressed as car.variableName
   //Does not work right now. Seems to not figure out the type at QML runtime
   m_settingDynProp = true;
   setProperty(qPrintable(variableName), info->value);
   m_settingDynProp = false;
}

void Car::registerAllSensors()
{
   if(!m_sensors.isEmpty())
      return;
   
   m_sensors.resize(NUM_SENSORS);
   //Add your new sensors here! Update Sensors Enum too!
   registerSensor(VehicleSpeed, QVariant::Int, "vehicleSpeed", "Speed", 0, INT_MAX, "MPH");
   registerSensor(Rpm, QVariant::Int, "rpm", "RPM", 0, 6000, "");
   registerSensor(CoolantTemperature, QVariant::Double, "coolantTemperature", "Coolant Temp", 0, 260, "degF");
   registerSensor(OilPressure, QVariant::Double, "oilPressure", "Oil Pressure", 10.0, 60, "Psi");
   registerSensor(Voltage, QVariant::Double, "voltage", "Voltage", 8.0, 16.0, "V");
   registerSensor(Boost, QVariant::Double, "boost", "Vacuum/Boost", 0.0, 20.0, "Psi");
   registerSensor(FuelLevel, QVariant::Double, "fuelLevel", "Fuel Level", 25, 100,"%");
   registerSensor(InjectorPulseWidthBank1, QVariant::Double, "injectorPulseWidthBank1", "Injector PW Bank 1", 0, 999, "s");
   registerSensor(InjectorPulseWidthBank2, QVariant::Double, "injectorPulseWidthBank2", "Injector PW Bank 2", 0, 999, "s");
   registerSensor(Advance, QVariant::Double, "advance", "Advance", -20, 50, "deg");
   registerSensor(InjectorStatus, QVariant::String, "injectorStatus", "Injector Status", 0, 255, "");
   registerSensor(EngineStatus, QVariant::String, "engineStatus", "Engine Status", 0, 255, "");
   registerSensor(AfrTargetBank1, QVariant::Double, "qfrTargetBank1", "AFR Target Bank 1", 0, 255, "AFR");
   registerSensor(AfrTargetBank2, QVariant::Double, "qfrTargetBank1", "AFR Target Bank 2", 0, 255, "AFR");
   registerSensor(WideBandValidBank1, QVariant::Double, "wideBandValidBank1", "Wideband O2 Bank 1", 0, 255, "");
   registerSensor(WideBandValidBank2, QVariant::Double, "wideBandValidBank2", "Wideband O2 Bank 2", 0, 255, "");
   registerSensor(Barometer, QVariant::Double, "barometer", "Barometer", 0, 255, "kPa");
   registerSensor(Map, QVariant::Double, "map", "Manifold Absolute Pressure", 0, 255, "kPa");
   registerSensor(Mat, QVariant::Double, "map", "Manifold Temperature", 0, 255, "degF");
   registerSensor(Tps, QVariant::Double, "tps", "Throttle Position", 0, 255, "%");
   registerSensor(AfrBank1, QVariant::Double, "afrBank1", "Air/Fuel Ratio Bank 1", 0, 999, "AFR");
   registerSensor(AfrBank2, QVariant::Double, "afrBank2", "Air/Fuel Ratio Bank 2", 0, 999, "AFR");
   registerSensor(Knock, QVariant::Double, "knock", "Knock Sensor", -100, 255, "V");
   registerSensor(ExhaustGasCorrectionBank1, QVariant::Double, "exhaustGasCorrectionBank1", "Exh Gas Correction Bank 1", -100, 999, "");
   registerSensor(ExhaustGasCorrectionBank2, QVariant::Double, "exhaustGasCorrectionBank2", "Exh Gas Correction Bank 2", -100, 999, "");
   registerSensor(AirCorrection, QVariant::Double, "airCorrection", "Air Correction", -100, 255, "");
   registerSensor(WarmupEnrich, QVariant::Double, "warmupEnrich", "Warmup Enrichment", -100, 255, "");
   registerSensor(AccelEnrich, QVariant::Double, "accelEnrich", "Acceleration Enrichment", -100, 255, "");
   registerSensor(TpsFuelCutOff, QVariant::Double, "tpsFuelCutOff", "Throttle Sensor Fuel Cut Off", -100, 255, "");
   registerSensor(BarometerCorrection, QVariant::Double, "varometerCorrection", "Barometer Correction", -100, 255, "");
   registerSensor(GammaEnrich, QVariant::Double, "gammaEnrich", "Gamma Enrichment", -100, 255, "");
   registerSensor(VeValueTable1, QVariant::Double, "veValueTable1", "Volumetric Efficiency Table 1", -100, 255, "");
   registerSensor(VeValueTable2, QVariant::Double, "veValueTable2", "Volumetric Efficiency Table 2", -100, 255, "");
   registerSensor(IacStep, QVariant::Double, "iacStep", "Idle Air Controller Step", -100, 255, "");
   registerSensor(ColdAdvance, QVariant::Double, "coldAdvance", "Cold Advance", -100, 255, "");
   registerSensor(TpsSlope, QVariant::Double, "Throttle Slope", "Throttle Slope", -100, 255, "");
   registerSensor(MapSlope, QVariant::Double, "Maifold Pressure Slope", "Manifold Pressure Slope", -100, 255, "");
   registerSensor(Dwell, QVariant::Double, "dwell", "Dwell", -100, 255, "");
   registerSensor(Maf, QVariant::Double, "maf", "Mass Air Flow", 1, 255, "");
   registerSensor(FuelLoad, QVariant::Double, "fuelLoad", "Fuel Load 1", -100, 255, "");
   registerSensor(FuelCorrection, QVariant::Double, "fuelCorrection", "Fuel Correction", -100, 255, "");
   registerSensor(KnockRetard, QVariant::Double, "knockRetard", "Knock Retard", -100, 255, "");
   registerSensor(EAEFuleCorr, QVariant::Double, "eaeFuleCorr", "Enhanced Accel Enrichment", -100, 255, "");
   registerSensor(EgoV, QVariant::Double, "egoV", "Oxygen Sensor Bank 1", -100, 255, "V");
   registerSensor(EgoV2, QVariant::Double, "egoV2", "Oxygen Sensor Bank 2", -100, 255, "V");
   registerSensor(FuelLoadBank2, QVariant::Double, "fuelLoadBank2", "Fuel Load 2", -100, 255, "");
   registerSensor(IgnitionLoadBank1, QVariant::Double, "ignitionLoadBank1", "Ignition Load Bank 1", -100, 255, "");
   registerSensor(IgnitionLoadBank2, QVariant::Double, "ignitionLoadBank2", "Ignition Load Bank 2", -100, 255, "");
}
