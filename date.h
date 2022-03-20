#pragma once

#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>
#include <iomanip>
#include <string>
#include <iomanip>
#include <sstream>
#include <stdexcept>


using namespace std;
//файлы должны содержать объ€влени€ и определени€ класса Date, 
//функции ParseDate и оператора вывода в поток дл€ класса Date;

// класс Date
// функци€ ParseDate 
// оператор вывода в поток дл€ класса Date.

class Date {
public:
	Date(const int& year,
		const int& month,
		const int& day) 
		: YEAR(year)
		, MONTH(month)
		, DAY(day) {
	}
	//Date(const int& year,
	//	const int& month,
	//	const int& day) {
	//	YEAR = year;
	//	if (month > 12 || month < 1) {
	//		throw invalid_argument("");
	//	}
	//	MONTH = month;
	//	if (day > 31 || day < 1) {
	//		throw invalid_argument("");
	//	}
	//	DAY = day;
	//}

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

private:
	const int YEAR;	// целое число от 0 до 9999
	const int MONTH;	// номер мес€ца от 1 до 12 включительно
	const int DAY;		// номер дн€ от 1 до 31 включительно
	//int YEAR;	// целое число от 0 до 9999
	//int MONTH;	// номер мес€ца от 1 до 12 включительно
	//int DAY;		// номер дн€ от 1 до 31 включительно
};

//void CheckSimbol(istream& is);

Date ParseDate(istream& is);

bool operator<(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
ostream& operator<<(ostream& stream, const Date& hs);
ostream& operator << (ostream& out, const pair<Date, string>& p);
