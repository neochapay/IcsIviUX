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

#ifndef ELMOBDIICOMM_H
#define ELMOBDIICOMM_H

#include "AbstractComm.h"

#include <QTimer>
#include <QTime>
#include <QVector>
#include "qextserialport.h"

//Used for OBD-II accounting
class PidInfo
{
public:
   PidInfo() :
      dataSize(0)
   { 
   
   }
   
   PidInfo(const QString& pid, int dataSize)
   {
      this->pid = pid;
      this->dataSize = dataSize;
   }
   
   PidInfo(const PidInfo& o)
   {
      this->pid = o.pid;
      this->dataSize = o.dataSize;
   }
    
   PidInfo& operator= (const PidInfo& o)
   {
      this->pid = o.pid;
      this->dataSize = o.dataSize;
      return *this;
   }

   
   QString pid;
   int dataSize;
};

class ElmObdiiComm : public AbstractComm
{
   Q_OBJECT
public:
   ElmObdiiComm(QObject* parent=0);
   ~ElmObdiiComm();
   
   enum SensorFetchState
   {
      FuelSystemStatus=0.
      EngineLoad,
      CoolantTemp,
      ShortTermTrimBank1,
      LongTermTrimBank1,
      ShortTermTrimBank2,
      LongTermTrimBank2,
      FuelPressure,
      Map,
      Rpm,
      Vss,
      Timing,
      IntakeAirTemp,
      Maf,
      Tps,
      SecondaryAirStatus,
      OxygenSensor1Bank1,
      OxygenSensor2Bank1,
      OxygenSensor3Bank1,
      OxygenSensor4Bank1,
      OxygenSensor1Bank2,
      OxygenSensor2Bank2,
      OxygenSensor3Bank2,
      OxygenSensor4Bank2,
      AuxInputStatus,
      FuelRailPressure,
      OxygenSensor1Lamvda,
      OxygenSensor2Lamvda,
      OxygenSensor3Lamvda,
      OxygenSensor4Lamvda,
      OxygenSensor5Lamvda,
      OxygenSensor6Lamvda,
      OxygenSensor7Lamvda,
      OxygenSensor8Lamvda,
      Egr,
      EgrError,
      EvapPurge,
      FuelLevel,
      EvapPressure,
      BarometricPressure,
      CatTempSensor1Bank1,
      CatTempSensor1Bank2,
      CatTempSensor2Bank1,
      CatTempSensor2Bank2,
      Voltage,
      AbsoluteLoad,
      EquivRatio,
      RelativeTps,
      AmbientAirTemp,
      AbsoluteThrottlePosB,
      AbsoluteThrottlePosC,
      AccelPedalPosD,
      AccelPedalPosE,
      AccelPedalPosF,
      ThrottleActuator,
      FuelType,
      EthanolPercent,
      AbsoluteEvapPressure,
      NUM_SENSOR_FETCH_STATES
   };
   
   virtual void init();
   virtual void cleanup();
   
   virtual QList<SensorInfo*> supportedSensors();
   
   virtual void runCommand(Car::Command);
   
protected slots:
   void requestNewData();
   void handleNewData();
   void handleTimeout();
   
private:
   QextSerialPort* m_port;
   int m_fetchState;
   QByteArray incomingData;
   QTime frameTime;
   bool m_liveDataMode;
   QVector<PidInfo> m_pidInfos;
};

#endif //ELMOBDIICOMM_H
