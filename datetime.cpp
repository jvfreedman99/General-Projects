#include <iostream>
#include <iomanip>
#include "datetime.h"
#include<string>
#include <sstream>
#include <ctime>
#include "util.h"

using namespace std;

DateTime::DateTime() {
	time_t rawtime;
 	struct tm * timeinfo;
  	time (&rawtime);
  	timeinfo = localtime(&rawtime);
	hour=timeinfo->tm_hour;
	min= timeinfo->tm_min;
	sec= timeinfo->tm_sec;
	year= timeinfo->tm_year+1900;
	month= timeinfo->tm_mon +1;
	day= timeinfo->tm_mday;

}
//initialize all time variables
DateTime::DateTime(int hh, int mm, int ss, int year, int month, int day) 
: hour(hh), min(mm), sec(ss), year(year), month(month), day(day) {

}

bool DateTime::operator<(const DateTime& other) const {
	//if stmts that determine which date is smaller going inward from year
	if(year < other.year) {
		return true;
	}
	else if (year > other.year) {
		return false;
	}
	else {
		if (month < other.month) {
			return true;
		}
		else if (month > other.month) {
			return false;
		}
		else {
			if (day < other.day) {
				return true;
			}
			else if (day > other.day) {
				return false;
			}
			else { 
				if (hour < other.hour) {
					return true;
				}
				else if (hour > other.hour) {
					return false;
				}
				else {
					if (min < other.min) {
						return true;
					}
					else if (min > other.min) {
						return false;
					}
					else {
						if (sec < other.sec) {
							return true;
						}
						else  {
							return false;
						}
					}
				}
			}
		}
	}
}

ostream& operator<<(ostream& os, const DateTime& other) {
	//prints out each variable with appropiate leading 0s
	os << other.year << '-';

	if (other.month < 10) {
		os << setw(2) << setfill('0');
	}
	os << other.month<< '-';

	if (other.day < 10) {
		os << setw(2) << setfill('0');
	}
	os << other.day << ' ';

	if (other.hour < 10) {
		os << setw(2) << setfill('0');
	}
	os << other.hour << ':';

	if (other.min < 10) {
		os << setw(2) << setfill('0');
	}
	os << other.min << ':';

	if (other.sec < 10) {
		os << setw(2) << setfill('0');
	}
	os << other.sec;
	return os;
}
//need to do this istream function
istream& operator>>(std::istream& is, DateTime& dt) {
	//gets input of each variable using delimeter
	string buffer1;
	getline(is, buffer1, '-');
	stringstream ss(trim(buffer1));
	ss >> dt.year;
	//if the input fails we just make the date the current time
	if(ss.fail()) {
		time_t rawtime;
 		struct tm * timeinfo;
  		time (&rawtime);
  		timeinfo = localtime(&rawtime);
  		dt.hour= timeinfo->tm_hour;
  		dt.min=timeinfo->tm_min;
  		dt.sec= timeinfo->tm_sec;
  		dt.year= timeinfo->tm_year+1900;
		dt.month= timeinfo->tm_mon +1;
		dt.day= timeinfo->tm_mday;
		return is;
	}
	getline(is,buffer1, '-');
	stringstream ss2(trim(buffer1));
	ss2 >> dt.month;
	if(ss2.fail()) {
		time_t rawtime;
 		struct tm * timeinfo;
  		time (&rawtime);
  		timeinfo = localtime(&rawtime);
  		dt.hour= timeinfo->tm_hour;
  		dt.min=timeinfo->tm_min;
  		dt.sec= timeinfo->tm_sec;
  		dt.year= timeinfo->tm_year+1900;
		dt.month= timeinfo->tm_mon +1;
		dt.day= timeinfo->tm_mday;
		return is;
	}
	getline(is, buffer1, ' ');
	stringstream ss3(trim(buffer1));
	ss3 >> dt.day;

	if(ss3.fail()) {
		time_t rawtime;
 		struct tm * timeinfo;
  		time (&rawtime);
  		timeinfo = localtime(&rawtime);
  		dt.hour= timeinfo->tm_hour;
  		dt.min=timeinfo->tm_min;
  		dt.sec= timeinfo->tm_sec;
  		dt.year= timeinfo->tm_year+1900;
		dt.month= timeinfo->tm_mon +1;
		dt.day= timeinfo->tm_mday;
		return is;
	}
	getline(is,buffer1, ':');
	stringstream ss4(trim(buffer1));
	ss4 >> dt.hour;

	if(ss4.fail()) {
		time_t rawtime;
 		struct tm * timeinfo;
  		time (&rawtime);
  		timeinfo = localtime(&rawtime);
  		dt.hour= timeinfo->tm_hour;
  		dt.min=timeinfo->tm_min;
  		dt.sec= timeinfo->tm_sec;
  		dt.year= timeinfo->tm_year+1900;
		dt.month= timeinfo->tm_mon +1;
		dt.day= timeinfo->tm_mday;
		return is;
	}
	getline(is,buffer1, ':');
	stringstream ss5(trim(buffer1));
	ss5 >> dt.min;

	if(ss5.fail()) {
		time_t rawtime;
 		struct tm * timeinfo;
  		time (&rawtime);
  		timeinfo = localtime(&rawtime);
  		dt.hour= timeinfo->tm_hour;
  		dt.min=timeinfo->tm_min;
  		dt.sec= timeinfo->tm_sec;
  		dt.year= timeinfo->tm_year+1900;
		dt.month= timeinfo->tm_mon +1;
		dt.day= timeinfo->tm_mday;
		return is;
	}
	getline(is,buffer1, ' ');
	stringstream ss6(trim(buffer1));
	ss6 >> dt.sec;
	if(ss6.fail()) {
		time_t rawtime;
 		struct tm * timeinfo;
  		time (&rawtime);
  		timeinfo = localtime(&rawtime);
  		dt.hour= timeinfo->tm_hour;
  		dt.min=timeinfo->tm_min;
  		dt.sec= timeinfo->tm_sec;
  		dt.year= timeinfo->tm_year+1900;
		dt.month= timeinfo->tm_mon +1;
		dt.day= timeinfo->tm_mday;
		return is;
	}

	return is;

}