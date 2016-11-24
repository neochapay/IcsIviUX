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

#include "NumberFormatter.h"

QString NumberFormatter::format(const QVariant& value, int type, int decimalPlaces)
{

   if( QVariant::Double == type || 
       QVariant::Int == type ||
       QVariant::UInt == type ||
       QVariant::LongLong == type ||
       QVariant::ULongLong == type )
   {
      QString format = QString::number(decimalPlaces);
      format.prepend("%.");
      format.append("f");
      QString str;
      str.sprintf(format.toLatin1(),value.toDouble());
      return str;
   }
   else
   {
      return value.toString();
   }
}