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

#include "Station.h"

Station::Station(const QString& callSign, const QString& frequency,
                 const QString& icon, const QString& listIcon) :
   m_callSign(callSign),
   m_frequency(frequency),
   m_icon(icon),
   m_listIcon(listIcon)
{
   
}

QString Station::callSign() const
{
   return m_callSign;
}

QString Station::frequency() const
{
   return m_frequency;
}

QString Station::icon() const
{
   return QString("callSignImages/")+m_icon;
}

QString Station::listIcon() const
{
   return QString("callSignImages/")+m_listIcon;
}