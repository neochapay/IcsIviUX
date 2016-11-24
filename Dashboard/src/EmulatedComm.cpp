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


#include "EmulatedComm.h"

#include <QTimer>
#include <QFile>
#include <QStringList>
#include <QtDebug>
#include "CommData.h"
#include "Car.h"

EmulatedComm::EmulatedComm(QObject* parent) :
   AbstractComm(parent)
{
   loadSensorLoop();
   QTimer::singleShot(500, this, SLOT(updateSensorData()));
}

QList<SensorInfo*> EmulatedComm::supportedSensors()
{
   return QList<SensorInfo*>();
}

void EmulatedComm::loadSensorLoop()
{
   m_sensorLoop.clear();
   
   //Read CSV File
   QFile file(":/data/SensorLoop.csv");
   if(!file.open(QIODevice::ReadOnly))
   {
      qDebug() << "Can open sensor file";
      return;
   }
   QString sensorLoopStr = file.readAll();
   file.close();
   
   QStringList sensorRuns = sensorLoopStr.split("\n");
   //Clip 1st row It's the header
   sensorRuns.removeAt(0);
   //Clip last row. It's blank
   sensorRuns.removeAt(sensorRuns.size()-1);
   //Each line is a set of sensors
   foreach(QString runStr, sensorRuns)
   {
      QVector<QVariant> sensorValues;
      sensorValues.fill(QVariant(), Car::NUM_SENSORS);
      
      QStringList run = runStr.split(",");
      //Each value is seperated by commas
      for(int i=0; i<Car::NUM_SENSORS; i++)
      {
         //Stop at end of sensors
         if(i >= run.size())
         {
            break;
         }
         
         if(i > 1)
         {
            sensorValues[i] = run[i].toDouble();
         }
         else
         {
            sensorValues[i] = run[i].toInt();
         }
      }
      m_sensorLoop << sensorValues;
   }
}

void EmulatedComm::updateSensorData()
{
   static int runNum = 0;
   if(runNum >= m_sensorLoop.size())
   {
      runNum =0;
   }
   
   CommData data;
   for(int i=0; i<m_sensorLoop[runNum].size(); i++)
   {
      data.setSensorValue((Car::Sensor)i, m_sensorLoop[runNum][i]);
   }
   emit sensorDataChanged(data);
   
    //Setup next run
   QTimer::singleShot(100, this, SLOT(updateSensorData()));
   runNum++;
}