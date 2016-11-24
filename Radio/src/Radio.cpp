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

#include "Radio.h"

#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioDeviceInfo>
#include <QtDebug>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#ifdef RADIO_SHARK
#include <hid.h>
#endif //RADIO_SHARK

#define DEBUG false             /* Set true for copious debugging output */
#define SHARK_VENDID 0x077d     /* Griffin's Vendor ID */
#define SHARK_DEVID 0x627a      /* The radioSHARK's Device ID */

#define READ_EP 0x5             /* libhid read command? */
#define WRITE_EP 0x5            /* libhid write command? */
#define SEND_PACKET_LENGTH 7    /* size of an instruction packet: shark2=7 */

Radio::Radio(QObject* parent) :
   QObject(parent),
   m_mode(FM),
#ifdef DUBLIN
   m_freq("105.2"),
   m_freqDbl(105.2)
#elif defined(LAS_VEGAS)
   m_freq("107.5"),
   m_freqDbl(107.5)
#else
   m_freq("104.1"),
   m_freqDbl(104.1)
#endif
{
   QAudioFormat format;
   format.setByteOrder(QAudioFormat::LittleEndian);
   format.setChannels (2);
   format.setCodec ("audio/pcm");
   format.setFrequency (48000);
   format.setSampleSize(16);
   format.setSampleType(QAudioFormat::SignedInt);
   
   QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
   QAudioDeviceInfo shark;
   foreach(QAudioDeviceInfo info, devices)
   {
      if(info.deviceName() == "front:CARD=radioSHARK,DEV=0")
      {
         qDebug() << "Found shark";
         shark = info;  
      }
   }
   
   devices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
   QAudioDeviceInfo intel;
   foreach(QAudioDeviceInfo info, devices)
   {
      if(info.deviceName() == "front:CARD=Intel,DEV=0")
      {
	qDebug() << "Found intel";
         intel = info;  
      }
   }
   
   if (!shark.isFormatSupported(format)) {
       qWarning()<<"default format not supported by shark";
       format = shark.nearestFormat(format);
   }
/*   
#ifdef RADIO_SHARK
   m_input = new QAudioInput(shark, format, this);
   m_output = new QAudioOutput(intel, format, this);
#else
   m_input = new QAudioInput(QAudioFormat(), this);
   m_output = new QAudioOutput(QAudioFormat(),this);
#endif
*/   
#ifdef DUBLIN
   m_stations.insert(98.0, new Station("FM98", "98.0", "fm98.png", "fm98_pad.png"));
   m_stations.insert(98.3, new Station("Near FM", "98.3", "near.png", "near_pad.png"));
   m_stations.insert(100.0, new Station("Radio Nova", "100.0", "radionova.png", "radionova.png"));
   m_stations.insert(102.0, new Station("Q102", "102.0", "q102.png", "q102_pad.png"));
   m_stations.insert(104.0, new Station("FM104", "104.0", "fm104.png", "fm104_pad.png"));
   m_stations.insert(105.2, new Station("Phantom", "105.2", "phantom.png", "phantom_pad.png"));
   m_stations.insert(106.8, new Station("Sunshine", "106.8", "sunshine.png", "sunshine_pad.png"));
#elif defined(LAS_VEGAS)
   m_stations.insert(88.1, new Station("Power 88", "88.1", "KCEP.png", "KCEP_pad.png"));
   m_stations.insert(89.7, new Station("NPR", "89.7", "KCNV.png", "KCNV_pad.png"));
   m_stations.insert(88.5, new Station("K-Love", "88.5", "KEKL.png", "KEKL_pad.png"));
   m_stations.insert(104.3, new Station("Now", "104.3", "KFRH.png", "KFRH_pad.png"));
   m_stations.insert(103.5, new Station("La Nueva", "103.5", "KISF.png", "KISF_pad.png"));
   m_stations.insert(96.3, new Station("Classic Rock", "96.3", "KKLZ.png", "KKLZ_pad.png"));
   m_stations.insert(98.5, new Station("Hit Music", "98.5", "KLUC.png", "KLUC_pad.png"));
   m_stations.insert(88.9, new Station("NPR", "88.9", "KNPR.png", "KNPR_pad.png"));
   m_stations.insert(92.3, new Station("KOMP Rock", "92.3", "KOMP.png", "KOMP_pad.png"));
   m_stations.insert(93.1, new Station("The Party", "93.1", "KPLV.png", "KPLV_pad.png"));
   m_stations.insert(105.1, new Station("La Tricolor", "105.1", "KQRT.png", "KQRT_pad.png"));
   m_stations.insert(106.5, new Station("Sunny", "106.5", "KSNE.png", "KSNE_pad.png"));
   m_stations.insert(90.5, new Station("Christian", "90.5", "KSOS.png", "KSOS_pad.png"));
   m_stations.insert(91.5, new Station("UNLV Jazz", "91.5", "KUNV.png", "KUNV_pad.png"));
   m_stations.insert(97.5, new Station("Hot 97.5", "97.5", "KVEG.png", "KVEG_pad.png"));
   m_stations.insert(95.5, new Station("Country", "95.5", "KWNR.png", "KWNR_pad.png"));
   m_stations.insert(100.5, new Station("KXNT News", "100.5", "KXNT.png", "KXNT_pad.png"));
   m_stations.insert(97.1, new Station("The Point", "97.1", "KXPT.png", "KXPT_pad.png"));
   m_stations.insert(107.5, new Station("X-107.5", "107.5", "KXTE.png", "KXTE_pad.png"));

#else //Boston
   m_stations.insert(88.9, new Station("Emerson", "88.9", "wers.png", "wers_pad.png"));
   m_stations.insert(89.7, new Station("WGBH PBS", "89.7", "wgbh.png", "wgbh_pad.png"));
   m_stations.insert(90.9, new Station("WBUR NPR", "90.9", "wbur.png", "wbur_pad.png"));
   m_stations.insert(92.9, new Station("92-9 BOS", "92.9", "wbos.png", "wbos_pad.png"));
   m_stations.insert(94.5, new Station("JAM'N", "94.5", "wjmn.png", "wjmn_pad.png"));
   m_stations.insert(98.5, new Station("Sports Hub", "98.5", "wbz.png", "wbz_pad.png"));
   m_stations.insert(104.1, new Station("Mix 104.1", "104.1", "wbmx.png", "wbmx_pad.png"));
   m_stations.insert(105.7, new Station("ROR", "105.7", "wror.png", "wror_pad.png"));
   m_stations.insert(107.3, new Station("WAAF", "107.3", "waaf.png", "waaf_pad.png"));
   m_stations.insert(107.9, new Station("KISS 180", "107.9", "wxks.png", "wxks_pad.png"));
#endif

   
   foreach(Station* station, m_stations)
   {
      m_stationModel << station;
   }
   
#ifdef DUBLIN
   setFrequency("105.3");
#elif defined(LAS_VEGAS)
   setFrequency("107.5");
#else
   setFrequency("104.1");
#endif
   
}

Radio::~Radio()
{
   
}

QList<QObject*> Radio::stationModel() const
{
   return m_stationModel;
}
   
void Radio::setMode(Mode amfm)
{
   m_mode = amfm;
}

Radio::Mode Radio::mode() const
{
   return m_mode;
}
   
void Radio::setFrequency(const QString freqStr)
{
   m_freq = freqStr;
   m_freqDbl = m_freq.toDouble();
   emitAll();
   
   
   unsigned char PACKET[SEND_PACKET_LENGTH] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
   unsigned short encodedFreq;
   float freq;
   unsigned int intensity;
   /* Tune to an FM frequency */
   PACKET[0] = 0x81;
   encodedFreq = 0;
   freq = freqStr.toFloat();
   encodedFreq  = ((freq * 10 * 2) - 3 );
   PACKET[1] = (encodedFreq >> 8) & 0xFF;
   PACKET[2] = encodedFreq & 0xFF;
   PACKET[3] = 0x33;
   PACKET[4] = 0x04;
   PACKET[5] = 0x00;
   PACKET[6] = 0x28;
   
   sendSharkPacket(PACKET);
}

QString Radio::frequency() const
{
   return m_freq;
}

QString Radio::callSign() const
{
   if(0 != m_stations[m_freqDbl])
      return m_stations[m_freqDbl]->callSign();  
   else
      return QString();
}

QString Radio::stationArt() const
{
   return m_stations[m_freqDbl]->icon();
}

QString Radio::artist() const
{
   return m_artist;
}

QString Radio::song() const
{
   return m_song;
}
   
void Radio::start()
{
   m_input->start(m_output->start());
}

void Radio::stop()
{
   m_output->stop();
   m_input->stop();
}

void Radio::setPlaying(bool playing)
{
   if(true == playing)
   {
      start();
   }
   else
   {
      stop();
   }
}

bool Radio::playing() const
{
   return (m_input->state() == QAudio::ActiveState);
}

int Radio::sendSharkPacket(unsigned char* PACKET)
{
#ifdef RADIO_SHARK
   hid_return ret;
   HIDInterface* hid;
   HIDInterfaceMatcher matcher = { SHARK_VENDID, SHARK_DEVID, NULL, NULL, 0 };
   /* Turn libhid debugging on if requested.  See include/debug.h for possible values. */
   if (DEBUG) {
            hid_set_debug(HID_DEBUG_ALL);
            hid_set_debug_stream(stderr);
            hid_set_usb_debug(0);                   /* passed directly to libusb */
   }

   /* Initialize the hid library */
   ret = hid_init();
   if (ret != HID_RET_SUCCESS) {
            fprintf(stderr, "hid_init failed with return code %d\n", ret);
            return 1;
   }

   /* Initialize the hid object */
   hid = hid_new_HIDInterface();
   if (hid == 0) {
            fprintf(stderr, "hid_new_HIDInterface() failed, out of memory?\n");
            return 1;
   }

   /* Open the shark */
   ret = hid_force_open(hid, 2, &matcher, 3);
   if (ret != HID_RET_SUCCESS) {
            fprintf(stderr, "hid_force_open failed with return code %d\n", ret);
            return 1;
   }

   /* Send the instruction packet constructed above to the Shark */
   ret = hid_interrupt_write(hid, WRITE_EP, (char*)PACKET, SEND_PACKET_LENGTH, 10000);
   if (ret != HID_RET_SUCCESS) fprintf(stderr, "hid_interrupt_write failed with return code %d\n", ret);

   /* Close the shark */
   ret = hid_close(hid);
   if (ret != HID_RET_SUCCESS) {
            fprintf(stderr, "hid_close failed with return code %d\n", ret);
            return 1;
   }

   /* Delete the hid object */
   hid_delete_HIDInterface(&hid);

   /* Clean up the hid library */
   ret = hid_cleanup();
   if (ret != HID_RET_SUCCESS) {
            fprintf(stderr, "hid_cleanup failed with return code %d\n", ret);
            return 1;
   }
        
   return ret;
#else //NOT DEFINDED RADIO_SHARK
   return 0;
#endif // RADIO_SHARK
}

void Radio::emitAll()
{
   emit frequencyChanged(m_freq);
   emit callSignChanged(m_callSign);
   emit stationArtChanged(m_stationArt);
   emit artistChanged(m_artist);
   emit songChanged(m_song);
}
