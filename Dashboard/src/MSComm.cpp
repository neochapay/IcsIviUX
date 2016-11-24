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

#include "MSComm.h"

#include "CommData.h"
#include "Car.h"

#include <QTime>
#include <QtDebug>

MSComm::MSComm(bool emulateMissingSensors, QObject* parent) :
   AbstractComm(parent),
   m_emulateMissingSensors(emulateMissingSensors)
{
   m_refreshTimeout = new QTimer(this);
   m_refreshTimeout->setInterval(500);
   connect(m_refreshTimeout, SIGNAL(timeout()), this, SLOT(handleTimeout()));
   
   frameTime.start();
   
   PortSettings settings;
   settings.BaudRate = BAUD115200;
   //settings.BaudRate = BAUD9600;
   settings.DataBits = DATA_8;
   settings.FlowControl = FLOW_OFF;
   settings.Parity = PAR_NONE;
   settings.StopBits = STOP_1;
   settings.Timeout_Millisec = 1000;
   
   m_port = new QextSerialPort("/dev/ttyUSB0",
                              settings);
   connect(m_port, SIGNAL(readyRead()), this, SLOT(handleNewData()));

   //Open comm to MegaSquirt
   if(m_port->open(QIODevice::ReadWrite))
   {
      qDebug() << "Opened comm with Megasquirt on" << "/dev/ttyUSB0";
      //Start Real Time Comm
      QTimer::singleShot(1000, this, SLOT(requestNewData()));
      m_refreshTimeout->start();
   }
   else
   {
      qDebug() << "Cannot open comm with Megasquirt on" << "/dev/ttyUSB0";
   }
}

MSComm::~MSComm()
{
   //Close Comm with MegaSquirt
   if(true == m_port->isOpen())
      m_port->close();
   
   delete m_port;
}

void MSComm::init()
{
   
}

void MSComm::cleanup()
{
   
}

QList<SensorInfo*> MSComm::supportedSensors()
{
   return QList<SensorInfo*>();
}

void MSComm::requestNewData()
{
   if( true == m_port->isOpen())
   {  
     //Get all Data 145Bytes
      m_port->write("A", 1);
   }
   else
      qDebug() << "Megasquirt port closed unexpectedly";
}

void MSComm::handleNewData()
{   
   incomingData.append(m_port->readAll());
   
   if(incomingData.size() > 145)
   {
      //Bad things. Call timeout handler
      //qDebug() << "(Data Size > Frame Size) Possible Corruption";
      handleTimeout();
      
   }
   else if(incomingData.size() == 145)
   {  
      //Stop Timeout
      m_refreshTimeout->stop();
      
      //Fetch Bytes;      
      // Convert bytes into real values
      int rpm = (incomingData[6] << 8) + incomingData[7];

      int coolantTempInt = (incomingData[22] << 8) + incomingData[23];
      double coolantTemp = (double)coolantTempInt * 0.1;
      
      quint16 voltsInt = (incomingData[26] << 8) + incomingData[27];
      double volts = (double)voltsInt * 0.1;
      
      quint16 injectorPulseWidthBank1Int = (incomingData[2] << 8) + incomingData[3];
      double injectorPulseWidthBank1 = injectorPulseWidthBank1Int * 0.000666;
      
      quint16 injectorPulseWidthBank2Int = (incomingData[4] << 8) + incomingData[5];
      double injectorPulseWidthBank2 = injectorPulseWidthBank2Int * 0.000666;
      
      qint16 advanceInt = (incomingData[6] << 8) + incomingData[7];
      double advance = advanceInt * 0.01;
      
      quint8 injectorStatusInt = incomingData[8];
      QString injectorStatus;
      switch(injectorStatusInt)
      {
      case 0:
         injectorStatus = "Firing 1";
         break;
      case 1:
         injectorStatus = "Firing 2";
         break;
      case 2:
         injectorStatus = "Scheduled 1";
         break;
      case 3:
         injectorStatus = "Injecting 1";
         break;
      case 4:
         injectorStatus = "Scheduled 2";
         break;
      case 5:
         injectorStatus = "Injecting 2";
         break;
      case 6:
         injectorStatus = "Boost Ctl Off";
      default:
         break;
      }
      
      quint8 engineStatusInt = incomingData[8];
      QString engineStatus;
      switch(engineStatusInt)
      {
      case 0:
         engineStatus = "Running";
         break;
      case 1:
         engineStatus = "Cranking";
         break;
      case 2:
         engineStatus = "ASE";
         break;
      case 3:
         engineStatus = "Warmup";
         break;
      case 4:
         engineStatus = "Acceleration";
         break;
      case 5:
         engineStatus = "Deceleration";
         break;
      case 6:
         engineStatus = "";
      case 7:
         engineStatus = "Idle";
      default:
         break;
      }
      
      quint8 afrTargetBank1Int = incomingData[12];
      double afrTargetBank1 = afrTargetBank1Int * 0.1;
      
      quint8 afrTargetBank2Int = incomingData[13];
      double afrTargetBank2 = afrTargetBank2Int * 0.1;
      
      quint8 wideBandValidBank1Int = incomingData[14];
      double wideBandValidBank1 = wideBandValidBank1Int * 10.0;
      
      quint8 wideBandValidBank2Int = incomingData[15];
      double wideBandValidBank2 = wideBandValidBank2Int * 10.0;
      
      qint16 barometerInt = (incomingData[16] << 8) + incomingData[17];
      double barometer = barometerInt * 0.1;
      
      qint16 mapInt = (incomingData[18] << 8) + incomingData[19];
      double map = mapInt * 0.1;
      
      qint16 matInt = (incomingData[20] << 8) + incomingData[21];
      double mat = matInt * 0.1;
      
      qint16 tpsInt = (incomingData[24] << 8) + incomingData[25];
      double tps = tpsInt * 0.1;
      
      qint16 afrBank1Int = (incomingData[28] << 8) + incomingData[29];
      double afrBank1 = afrBank1Int * 0.1;
      
      qint16 afrBank2Int = (incomingData[30] << 8) + incomingData[31];
      double afrBank2 = afrBank2Int * 0.1;
      
      qint16 knockInt = (incomingData[32] << 8) + incomingData[33];
      double knock = knockInt * 0.1;
      
      qint16 exhaustGasCorrectionBank1Int = (incomingData[34] << 8) + incomingData[35];
      double exhaustGasCorrectionBank1 = exhaustGasCorrectionBank1Int;
      
      qint16 exhaustGasCorrectionBank2Int = (incomingData[36] << 8) + incomingData[37];
      double exhaustGasCorrectionBank2 = exhaustGasCorrectionBank2Int;
      
      qint16 airCorrectionInt = (incomingData[38] << 8) + incomingData[39];
      double airCorrection = airCorrectionInt;
   
      qint16 warmupEnrichInt = (incomingData[40] << 8) + incomingData[41];
      double warmupEnrich = warmupEnrichInt;
      
      qint16 accelEnrichInt = (incomingData[42] << 8) + incomingData[43];
      double accelEnrich = accelEnrichInt * 0.1;
      
      qint16 tpsFuelCutOffInt = (incomingData[44] << 8) + incomingData[44];
      double tpsFuelCutOff = tpsFuelCutOffInt;
      
      qint16 barometerCorrectionInt = (incomingData[46] << 8) + incomingData[47];
      double barometerCorrection = barometerCorrectionInt;
      
      qint16 gammaEnrichInt = (incomingData[48] << 8) + incomingData[49];
      double gammaEnrich = gammaEnrichInt;
      
      qint16 veValueTable1Int = (incomingData[50] << 8) + incomingData[51];
      double veValueTable1 = veValueTable1Int * 0.1;
      
      qint16 veValueTable2Int = (incomingData[52] << 8) + incomingData[53];
      double veValueTable2 = veValueTable2Int* 0.1;
      
      qint16 iacStepInt = (incomingData[54] << 8) + incomingData[55];
      double iacStep = iacStepInt;
   
      qint16 coldAdvanceInt = (incomingData[56] << 8) + incomingData[57];
      double coldAdvance = coldAdvanceInt* 0.1;
      
      qint16 tpsSlopeInt = (incomingData[58] << 8) + incomingData[59];
      double tpsSlope = tpsSlopeInt* 0.1;
      
      qint16 mapSlopeInt = (incomingData[60] << 8) + incomingData[61];
      double mapSlope = mapSlopeInt* 0.1;
      
      quint16 dwellInt = (incomingData[62] << 8) + incomingData[63];
      double dwell = dwellInt* 0.0666;
      
      qint16 mafInt = (incomingData[64] << 8) + incomingData[65];
      double maf = mafInt* 0.1;
      
      qint16 fuelLoadInt = (incomingData[66] << 8) + incomingData[66];
      double fuelLoad = fuelLoadInt* 0.1;
      
      qint16 fuelCorrectionInt = (incomingData[68] << 8) + incomingData[69];
      double fuelCorrection = fuelCorrectionInt* 0.1;
      
      quint8 knockRetardInt = incomingData[71];
      double knockRetard = knockRetardInt * 0.1;
      
      quint16 eAEFuleCorrInt = (incomingData[72] << 8) + incomingData[73];
      double eAEFuleCorr = eAEFuleCorrInt;
      
      qint16 egoVInt = (incomingData[74] << 8) + incomingData[75];
      double egoV = egoVInt* 0.01;
      
      qint16 egoV2Int = (incomingData[76] << 8) + incomingData[77];
      double egoV2 = egoV2Int* 0.01;
      
      quint16 fuelLoadBank2Int = (incomingData[88] << 8) + incomingData[89];
      double fuelLoadBank2 = fuelLoadBank2Int* 0.01;
      
      quint16 ignitionLoadBank1Int = (incomingData[90] << 8) + incomingData[91];
      double ignitionLoadBank1 = ignitionLoadBank1Int* 0.01;
      
      quint16 ignitionLoadBank2Int = (incomingData[92] << 8) + incomingData[93];
      double ignitionLoadBank2 = ignitionLoadBank2Int* 0.01;
      
      //Send values to Views
      CommData data;
      data.setSensorValue(Car::Rpm, rpm);
      data.setSensorValue(Car::CoolantTemperature, coolantTemp);
      data.setSensorValue(Car::Voltage, volts);
      data.setSensorValue(Car::InjectorPulseWidthBank1, injectorPulseWidthBank1);
      data.setSensorValue(Car::InjectorPulseWidthBank2, injectorPulseWidthBank2);
      data.setSensorValue(Car::Advance, advance);
      data.setSensorValue(Car::InjectorStatus, injectorStatus);
      data.setSensorValue(Car::EngineStatus, engineStatus);
      data.setSensorValue(Car::AfrTargetBank1, afrTargetBank1);
      data.setSensorValue(Car::AfrTargetBank2, afrTargetBank2);
      data.setSensorValue(Car::WideBandValidBank1, wideBandValidBank1);
      data.setSensorValue(Car::WideBandValidBank2, wideBandValidBank2);
      data.setSensorValue(Car::Barometer, barometer);
      data.setSensorValue(Car::Map, map);
      data.setSensorValue(Car::Mat, mat);
      data.setSensorValue(Car::Tps, tps);
      data.setSensorValue(Car::AfrBank1, afrBank1);
      data.setSensorValue(Car::AfrBank2, afrBank2);
      data.setSensorValue(Car::Knock, knock);
      data.setSensorValue(Car::ExhaustGasCorrectionBank1, exhaustGasCorrectionBank1);
      data.setSensorValue(Car::ExhaustGasCorrectionBank2, exhaustGasCorrectionBank2);
      data.setSensorValue(Car::AirCorrection, airCorrection);
      data.setSensorValue(Car::WarmupEnrich, warmupEnrich);
      data.setSensorValue(Car::AccelEnrich, accelEnrich);  
      data.setSensorValue(Car::TpsFuelCutOff, tpsFuelCutOff);
      data.setSensorValue(Car::BarometerCorrection, barometerCorrection);
      data.setSensorValue(Car::GammaEnrich, gammaEnrich);
      data.setSensorValue(Car::VeValueTable1, veValueTable1);
      data.setSensorValue(Car::VeValueTable2, veValueTable2);
      data.setSensorValue(Car::IacStep, iacStep);
      data.setSensorValue(Car::ColdAdvance, coldAdvance);
      data.setSensorValue(Car::TpsSlope, tpsSlope);
      data.setSensorValue(Car::MapSlope, mapSlope);
      data.setSensorValue(Car::Dwell, dwell);
      data.setSensorValue(Car::Maf, maf);
      data.setSensorValue(Car::FuelLoad, fuelLoad);
      data.setSensorValue(Car::FuelCorrection, fuelCorrection);
      data.setSensorValue(Car::KnockRetard, knockRetard);
      data.setSensorValue(Car::EAEFuleCorr, eAEFuleCorr);
      data.setSensorValue(Car::EgoV, egoV);
      data.setSensorValue(Car::EgoV2, egoV2);
      data.setSensorValue(Car::FuelLoadBank2, fuelLoadBank2);
      data.setSensorValue(Car::IgnitionLoadBank1, ignitionLoadBank1);
      data.setSensorValue(Car::IgnitionLoadBank2, ignitionLoadBank2);
      
      if(m_emulateMissingSensors)
      {
         static int run = 0;
         
         //Vehicle speed as function of RPM. Assume 1:1 trans and 2.56 rear and 9'' radius wheels
         double speed = (0.00595) * ((double)rpm * 9.0) / (1.0 * 2.56);
         data.setSensorValue(Car::VehicleSpeed, (int)speed);
         
         //Boost as function of RPM
         double boost = 0;
         if(rpm >2500)
         {
            //1lb of boost per 200 RPM after 2500 to max of 15
            boost = qMin(15, (rpm -2500)/100);
         }
         data.setSensorValue(Car::Boost, boost);
         
         //Oil Pressure as function of RPM. 10psi for every 1000RPM. Min 20 Max 50
         double oilPressure = qMax(20, qMin(50, rpm/100));
         data.setSensorValue(Car::OilPressure, oilPressure);
         
         //Count down fuel
         double fuel = 100 - run/10; 
         data.setSensorValue(Car::FuelLevel, fuel);
         
         run++;
         if(run > 999)
         {
            run = 0;
         }
      }
      
      
      emit sensorDataChanged(data);
      
      //Reset incomingData
      incomingData.clear();
      
      //Get next frame
      QTimer::singleShot(75, this, SLOT(requestNewData()));
      m_refreshTimeout->start();
   }
}

void MSComm::handleTimeout()
{
   //qDebug() << "Comm error. Re-attempting connection";
   //Try again
   incomingData.clear();
   m_refreshTimeout->stop();
   QTimer::singleShot(75, this, SLOT(requestNewData()));
   m_refreshTimeout->start();
}
   
   