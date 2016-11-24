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

#ifndef STATION_H
#define STATION_H

#include <QObject>
#include <QIcon>

class Station : public QObject
{
   Q_OBJECT
   Q_PROPERTY(QString callSign READ callSign NOTIFY callSignChanged);
   Q_PROPERTY(QString frequency READ frequency NOTIFY frequencyChanged);
   Q_PROPERTY(QString icon READ icon NOTIFY iconChanged);
   Q_PROPERTY(QString listIcon READ listIcon NOTIFY listIconChanged);
public:
   Station(const QString& callSign, const QString& frequency,
           const QString& icon, const QString& listIcon);

   QString callSign() const;
   QString frequency() const;
   QString icon() const;
   QString listIcon() const;
   
signals:
   void callSignChanged(const QString& callSign);
   void frequencyChanged(const QString& frequency);
   void iconChanged(const QString& icon);
   void listIconChanged(const QString& icon);
   
private:
   QString m_callSign;
   QString m_frequency;
   QString m_icon;
   QString m_listIcon;
   
};

#endif //STATION_H
