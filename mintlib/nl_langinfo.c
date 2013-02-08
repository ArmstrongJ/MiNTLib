/* nl_langinfo() replacement: query locale dependent information.

   Copyright (C) 2007-2009 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */


/* Specification.  */
#include <langinfo.h>

# include <locale.h>

char *
nl_langinfo (nl_item item)
{
  switch (item)
    {
    /* nl_langinfo items of the LC_CTYPE category */
    case CODESET:
        return "UTF-8";
        /* nl_langinfo items of the LC_NUMERIC category */
    case RADIXCHAR:
      return localeconv () ->decimal_point;
    case THOUSEP:
      return localeconv () ->thousands_sep;
    /* nl_langinfo items of the LC_TIME category.
       TODO: Really use the locale.  */
    case D_T_FMT:
    case ERA_D_T_FMT:
      return "%a %b %e %H:%M:%S %Y";
    case D_FMT:
    case ERA_D_FMT:
      return "%m/%d/%y";
    case T_FMT:
    case ERA_T_FMT:
      return "%H:%M:%S";
    case T_FMT_AMPM:
      return "%I:%M:%S %p";
    case AM_STR:
      return "AM";
    case PM_STR:
      return "PM";
    case DAY_1:
      return "Sunday";
    case DAY_2:
      return "Monday";
    case DAY_3:
      return "Tuesday";
    case DAY_4:
      return "Wednesday";
    case DAY_5:
      return "Thursday";
    case DAY_6:
      return "Friday";
    case DAY_7:
      return "Saturday";
    case ABDAY_1:
      return "Sun";
    case ABDAY_2:
      return "Mon";
    case ABDAY_3:
      return "Tue";
    case ABDAY_4:
      return "Wed";
    case ABDAY_5:
      return "Thu";
    case ABDAY_6:
      return "Fri";
    case ABDAY_7:
      return "Sat";
    case MON_1:
      return "January";
    case MON_2:
      return "February";
    case MON_3:
      return "March";
    case MON_4:
      return "April";
    case MON_5:
      return "May";
    case MON_6:
      return "June";
    case MON_7:
      return "July";
    case MON_8:
      return "August";
    case MON_9:
      return "September";
    case MON_10:
      return "October";
    case MON_11:
      return "November";
    case MON_12:
      return "December";
    case ABMON_1:
      return "Jan";
    case ABMON_2:
      return "Feb";
    case ABMON_3:
      return "Mar";
    case ABMON_4:
      return "Apr";
    case ABMON_5:
      return "May";
    case ABMON_6:
      return "Jun";
    case ABMON_7:
      return "Jul";
    case ABMON_8:
      return "Aug";
    case ABMON_9:
      return "Sep";
    case ABMON_10:
      return "Oct";
    case ABMON_11:
      return "Nov";
    case ABMON_12:
      return "Dec";
    case ERA:
      return "";
    case ALT_DIGITS:
      return "\0\0\0\0\0\0\0\0\0\0";
    /* nl_langinfo items of the LC_MONETARY category
       TODO: Really use the locale. */
    case CRNCYSTR:
      return "-";
    /* nl_langinfo items of the LC_MESSAGES category
       TODO: Really use the locale. */
    case YESEXPR:
      return "^[yY]";
    case NOEXPR:
      return "^[nN]";
    default:
      return "";
    }
}



