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


#ifndef RADIO_H
#define RADIO_H

#include <QObject>
#include <QMap>
#include <QIcon>
#include <QAudioInput>
#include <QAudioOutput>

#include "Station.h"

class Radio : public QObject
{
   Q_OBJECT
   Q_PROPERTY(Mode mode READ mode WRITE setMode NOTIFY modeChanged)
   Q_PROPERTY(QString frequency READ frequency WRITE setFrequency NOTIFY frequencyChanged)
   Q_PROPERTY(QString callSign READ callSign NOTIFY callSignChanged)
   Q_PROPERTY(QString stationArt READ stationArt NOTIFY stationArtChanged)
   Q_PROPERTY(QString artist READ artist NOTIFY artistChanged)
   Q_PROPERTY(QString song READ song NOTIFY songChanged)
   Q_PROPERTY(bool playing READ playing NOTIFY playingChanged)
public:
   enum Mode {
               AM=0,
               FM
             };
   
   Radio(QObject* parent=0);
   ~Radio();
   
   QList<QObject*> stationModel() const;
   
   void setMode(Mode amfm);
   Mode mode() const;
   
   void setFrequency(const QString freq);
   QString frequency() const;
   
   QString callSign() const;
   QString stationArt() const;
   QString artist() const;
   QString song() const;
   
   void setPlaying(bool playing);
   bool playing() const;
   
   Q_INVOKABLE void start();
   Q_INVOKABLE void stop();
   
signals:
   void modeChanged(Mode mode);
   void frequencyChanged(const QString& frequency);
   void callSignChanged(const QString& callSign);
   void stationArtChanged(const QString& stationArt);
   void artistChanged(const QString& artist);
   void songChanged(const QString& song);
   
protected:
   int sendSharkPacket(unsigned char* PACKET);
   void emitAll();
   
private:
   Mode m_mode;
   QString m_freq;
   double m_freqDbl;
   QString m_callSign;
   QString m_stationArt;
   QString m_artist;
   QString m_song;
   
   QAudioInput* m_input;
   QAudioOutput* m_output;
   
   QList<QObject*> m_stationModel;
   QMap<double, Station*> m_stations;
};

#endif //RADIO_H
