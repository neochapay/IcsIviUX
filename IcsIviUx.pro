TEMPALTE = app

QT += declarative network opengl

CONFIG += debug

CONFIG += mobility console
MOBILITY = multimedia

OBJ_DIR = obj
MOC_DIR = moc

RESOURCES += IcsIviUx.qrc

INCLUDEPATH += Dashboard/src \
               Mp3/src \
               Radio/src \
               Sirius/src
#LIBS += -lQtMultiMediaKit1

dublin {
   DEFINES += DUBLIN
}

vegas {
   DEFINES += LAS_VEGAS
}

fullscreen {
   DEFINES += FULL_SCREEN
}

sirius {
   CONFIG += serialio
   DEFINES += SCC1 SIRIUS
}

radioshark {
   CONFIG += libhid
   DEFINES += RADIO_SHARK
}

megasquirt {
   CONFIG += serialio
   DEFINES += MEGA_SQUIRT
   HEADERS += Dashboard/src/MSComm.h
   SOURCES += Dashboard/src/MSComm.cpp
}

elm327 {
   CONFIG += serialio
   DEFINES += ELM_327
   HEADERS += Dashboard/src/ElmObdiiComm.h
   SOURCES += Dashboard/src/ElmObdiiComm.cpp
}

serialio {
   INCLUDEPATH += ../qextserialport/src
   LIBS += -L../qextserialport/src/build -lqextserialport
}

libhid {
   LIBS += -lhid
}

HEADERS += Dashboard/src/AbstractComm.h \
           Dashboard/src/EmulatedComm.h \
           Dashboard/src/CommData.h \
           Dashboard/src/Car.h \
           Dashboard/src/SensorInfo.h \
           Dashboard/src/CarSensorProxy.h \
           Dashboard/src/NumberFormatter.h \
           Mp3/src/Album.h \
           Mp3/src/Mp3.h \
           Mp3/src/Mp3Player.h \
           Radio/src/Radio.h \
           Radio/src/Station.h \
           Sirius/src/Sirius.h \
           Sirius/src/SiriusStation.h \
           Sirius/src/SiriusStationModel.h

SOURCES += Dashboard/src/AbstractComm.cpp \
           Dashboard/src/EmulatedComm.cpp \
           Dashboard/src/CommData.cpp \
           Dashboard/src/Car.cpp \
           Dashboard/src/SensorInfo.cpp \
           Dashboard/src/CarSensorProxy.cpp \
           Dashboard/src/NumberFormatter.cpp \
           Mp3/src/Album.cpp \
           Mp3/src/Mp3.cpp \
           Mp3/src/Mp3Player.cpp \
           Radio/src/Radio.cpp \
           Radio/src/Station.cpp \
           Sirius/src/Sirius.cpp \
           Sirius/src/SiriusStation.cpp \
           Sirius/src/SiriusStationModel.cpp \
           main.cpp
