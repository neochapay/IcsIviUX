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

#include "ElmObdiiComm.h"

#include "CommData.h"
#include "Car.h"

#include <QTime>
#include <QStringList>
#include <QtDebug>

ElmObdiiComm::ElmObdiiComm(QObject* parent) :
   AbstractComm(parent),
   m_fetchState(FetchVss),
   m_liveDataMode(false)
{  
   frameTime.start();
   
   //Load From file?
   m_pidInfos.resize(NUM_SENSOR_FETCH_STATES);
   m_pidInfos[FuelSystemStatus] = PidInfo("03",3);
   m_pidInfos[EngineLoad] = PidInfo("04",1);
   m_pidInfos[CoolantTemp] = PidInfo("05",1);
   m_pidInfos[ShortTermTrimBank1] = PidInfo("06",1);
   m_pidInfos[LongTermTrimBank1] = PidInfo("07",1);
   m_pidInfos[ShortTermTrimBank2] = PidInfo("08",1);
   m_pidInfos[LongTermTrimBank2] = PidInfo("09",1);
   m_pidInfos[FuelPressure] = PidInfo("0A",1);
   m_pidInfos[Map] = PidInfo("0B",1);
   m_pidInfos[Rpm] = PidInfo("0C",2);
   m_pidInfos[Vss] = PidInfo("0D",1);
   m_pidInfos[Timing] = PidInfo("0E",1);
   m_pidInfos[IntakeAirTemp] = PidInfo("0F",1);
   m_pidInfos[Maf] = PidInfo("10",2);
   m_pidInfos[Tps] = PidInfo("11",1);
   m_pidInfos[SecondaryAirStatus] = PidInfo("12",1);
   m_pidInfos[OxygenSensor1Bank1] = PidInfo("14",2);
   m_pidInfos[OxygenSensor2Bank1] = PidInfo("15",2);
   m_pidInfos[OxygenSensor3Bank1] = PidInfo("16",2);
   m_pidInfos[OxygenSensor4Bank1] = PidInfo("17",2);
   m_pidInfos[OxygenSensor1Bank2] = PidInfo("18",2);
   m_pidInfos[OxygenSensor2Bank2] = PidInfo("19",2);
   m_pidInfos[OxygenSensor3Bank2] = PidInfo("1A",2);
   m_pidInfos[OxygenSensor4Bank2] = PidInfo("1B",2);
   m_pidInfos[AuxInputStatus] = PidInfo("1E",1);
   m_pidInfos[FuelRailPressure] = PidInfo("23",2);
   m_pidInfos[OxygenSensor1Lamvda] = PidInfo("24",4);
   m_pidInfos[OxygenSensor2Lamvda] = PidInfo("25",4);
   m_pidInfos[OxygenSensor3Lamvda] = PidInfo("26",4);
   m_pidInfos[OxygenSensor4Lamvda] = PidInfo("27",4);
   m_pidInfos[OxygenSensor5Lamvda] = PidInfo("28",4);
   m_pidInfos[OxygenSensor6Lamvda] = PidInfo("29",4);
   m_pidInfos[OxygenSensor7Lamvda] = PidInfo("2A",4);
   m_pidInfos[OxygenSensor8Lamvda] = PidInfo("2B",4);
   m_pidInfos[Egr] = PidInfo("2C",1);
   m_pidInfos[EgrError] = PidInfo("2D",1);
   m_pidInfos[EvapPurge] = PidInfo("2E",1);
   m_pidInfos[FuelLevel] = PidInfo("2F",1);
   m_pidInfos[EvapPressure] = PidInfo("32",2);
   m_pidInfos[BarometricPressure] = PidInfo("33",1);
   m_pidInfos[CatTempSensor1Bank1] = PidInfo("3C",2);
   m_pidInfos[CatTempSensor1Bank2] = PidInfo("3D",2);
   m_pidInfos[CatTempSensor2Bank1] = PidInfo("3E",2);
   m_pidInfos[CatTempSensor2Bank2] = PidInfo("3F",2);
   m_pidInfos[Voltage] = PidInfo("42",2);
   m_pidInfos[AbsoluteLoad] = PidInfo("43",2);
   m_pidInfos[EquivRatio] = PidInfo("44",2);
   m_pidInfos[RelativeTps] = PidInfo("45",1);
   m_pidInfos[AmbientAirTemp] = PidInfo("46",1);
   m_pidInfos[AbsoluteThrottlePosB] = PidInfo("47",1);
   m_pidInfos[AbsoluteThrottlePosC] = PidInfo("48",1);
   m_pidInfos[AccelPedalPosD] = PidInfo("49",1);
   m_pidInfos[AccelPedalPosE] = PidInfo("4A",1);
   m_pidInfos[AccelPedalPosF] = PidInfo("4B",1);
   m_pidInfos[ThrottleActuator] = PidInfo("4C",1);
   m_pidInfos[FuelType] = PidInfo("51",1);
   m_pidInfos[EthanolPercent] = PidInfo("52",1);
   m_pidInfos[AbsoluteEvapPressure] = PidInfo("53",2);
}

ElmObdiiComm::~ElmObdiiComm()
{
   //Close Comm with MegaSquirt
   if(true == m_port->isOpen())
      m_port->close();
   
   delete m_port;
}

void ElmObdiiComm::init()
{
   PortSettings settings;
   settings.BaudRate = BAUD115200;
   //settings.BaudRate = BAUD9600;
   settings.DataBits = DATA_8;
   settings.FlowControl = FLOW_OFF;
   //settings.FlowControl = FLOW_HARDWARE;
   settings.Parity = PAR_NONE;
   settings.StopBits = STOP_1;
   settings.Timeout_Millisec = 1000;
   
   m_port = new QextSerialPort("/dev/ttyUSB0",
                              settings);
   connect(m_port, SIGNAL(readyRead()), this, SLOT(handleNewData()));
   
   //Open comm to ELM 327
   if(m_port->open(QIODevice::ReadWrite))
   {
      qDebug() << "Opened comm with ELM 327 on" << "/dev/ttyUSB0";
   }
   else
   {
      qDebug() << "Cannot open comm with ELM 327 on" << "/dev/ttyUSB0";
   }
}

void ElmObdiiComm::cleanup()
{
   m_port->close();
}

QList<SensorInfo*> ElmObdiiComm::supportedSensors()
{
   return QList<SensorInfo*>();
}

void ElmObdiiComm::runCommand(Car::Command command)
{
   switch(command)
   {
   case Car::StartLiveData:
      m_liveDataMode = true;
      //Start Real Time Comm
      QTimer::singleShot(1000, this, SLOT(requestNewData()));
      break;
   case Car::StopLiveData:
      m_liveDataMode = false;
      break;
   default:
      qDebug() << "Unsupported Command";
      break;
   }
}

void ElmObdiiComm::requestNewData()
{
   if( true == m_port->isOpen())
   { 
     //Get data for current state
     QString command = QString("01 ") + m_pidInfos[m_fetchState].pid;
     m_port->write(command.toLatin1());
   }
   else
   {
      qDebug() << "ELM 327 port closed unexpectedly";
   }
}

void ElmObdiiComm::handleNewData()
{ 
   //Check for timeout from ELM
   if(QString(incomingData.data()) == QString("NO DATA"))
   {
      handleTimeout();
   }
   
   //Make sure we have enough data for current state
   if(incomingData.size() == m_pidInfos[m_fetchState].dataSize)
   {
      CommData data;
      //Decode current state data
      qDebug() << "Got full value for" << m_fetchState << incomingData;
      QStringList dataPacket = QString(incomingData).split("");
      qDebug() << "Packet Data" << dataPacket;
      
      //Make sure this is the packet we are looking for?
      bool ok = false;
      switch(m_fetchState)
     {
      case FetchVss:
      {
         //One hex value in kph. Convert to mph
         int speed = dataPacket[2].toInt(&ok, 16) * 0.6214;
         data.setSensorValue(Car::VehicleSpeed, speed);
         break;
      }
      case FetchRpm:
      {
         //Two string hex values
         int rpm = (dataPacket[2] + dataPacket[3]).toInt(&ok, 16);
         data.setSensorValue(Car::Rpm, rpm);
         break;
      }
      default:
           //Will also get un implemented pids
           //Skip accounting enums
           break;
     }
      emit sensorDataChanged(data);
      
      //Clear incoming data buffer
      incomingData.clear();
      
      //Increment fetch state
      m_fetchState ++;
      if(m_fetchState == m_pidInfos.size())
      {
         m_fetchState = 0;
         qDebug() << "Full Frame Complete. Time Since last Full Frame" << frameTime.restart();
      }
      
      //Get next sensor, but cool off after each full frame
      if(m_fetchState == 0)
         QTimer::singleShot(75, this, SLOT(requestNewData()));
      else
         QTimer::singleShot(0, this, SLOT(requestNewData()));
   }
   else if(incomingData.size() > m_pidInfos[m_fetchState].dataSize)
   {
      //Handle data corruption by trying again
      handleTimeout();
   }
   
   //If we get this far we are still waiting for data.
   //That's fine readyRead() will fire when there is more
}

void ElmObdiiComm::handleTimeout()
{
   qDebug() << "Comm error. Re-attempting connection";
   //Try again
   incomingData.clear();
   QTimer::singleShot(75, this, SLOT(requestNewData()));
}