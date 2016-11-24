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

#include <QApplication>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QGLWidget>
#include <QIcon>

#include "Car.h"
#include "EmulatedComm.h"
#include "CarSensorProxy.h"
#include "NumberFormatter.h"

#ifdef MEGA_SQUIRT
#include "MSComm.h"
#endif //MEGA_SQUIRT

#ifdef ELM_327
#include "ElmObdiiComm.h"
#endif //ELM_327

#include "Radio.h"
#include "Station.h"

#include "Sirius.h"

#include "Mp3Player.h"
#include "Album.h"
#include "Mp3.h"

#include <QtDebug>

int main(int argc, char** argv)
{
   QApplication app(argc, argv);

#ifdef MEGA_SQUIRT
   MSComm comm(true);
#elif defined(ELM_327)
   ElmObdiiComm comm;
#else
   EmulatedComm comm;
#endif //MEGA_SQUIRT
   comm.init();
   comm.runCommand(Car::StartLiveData);
   
   //Create Car using Commm
   Car car;
   car.addComm(&comm);
   
   //Create AM/FM Radio Backend
   Radio radio;
#ifdef RADIO_SHARK
   radio.start();
#endif
   
   //Create Sirius Radio
   Sirius sirius;

   // Create Mp3 Player;
   Mp3Player mp3Player;

   //Create QML View
   QDeclarativeView view;
   view.setViewport(new QGLWidget());
   
   view.rootContext()->setContextProperty("car", &car);
   NumberFormatter formatter;
   view.rootContext()->setContextProperty("NumberFormatter", &formatter);
   
   QList<QObject*> sensorModel;
   //Add each Car Sensor as a variable and populate the sensor model
   for(int i=0; i< Car::NUM_SENSORS; i++)
   {
      Car::Sensor sensor = static_cast<Car::Sensor>(i);
      QString sensorName = car.sensorVariableName(sensor);
      CarSensorProxy* proxy = new CarSensorProxy(&car, sensor, &view);
      sensorModel.append(proxy);
      view.rootContext()->setContextProperty(sensorName, proxy);
   }

   //Export the sensor model
   view.rootContext()->setContextProperty("sensorModel", QVariant::fromValue(sensorModel));
   
   //Export radio and station models
   view.rootContext()->setContextProperty("radioBackend", &radio);
   view.rootContext()->setContextProperty("fmStationModel", QVariant::fromValue(radio.stationModel()));
 
   //Export Sirius and station models
   view.rootContext()->setContextProperty("siriusBackend", &sirius);
   view.rootContext()->setContextProperty("siriusStationModel", sirius.stationModel()); 
 
   // Export mp3 models
   view.rootContext()->setContextProperty("mp3PlayerBackend", &mp3Player);
   view.rootContext()->setContextProperty("albumModel", mp3Player.albumModel() );
   view.rootContext()->setContextProperty("mp3Model", mp3Player.mp3Model() );

   //Use local version for dev (faster debug). Use resources for release(easy deploy)
   //view.setSource(QUrl("qrc:/qml/MegaDash.qml"));
   view.setSource(QUrl("IcsIviUx.qml"));

#ifdef FULL_SCREEN
   view.showFullScreen();
#else
   view.show();
#endif
   
   int retVal = app.exec();
   comm.cleanup();
   return retVal;
}
