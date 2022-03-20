#include "date.h"

//файлы должны содержать объ€влени€ и определени€ класса Date, 
//функции ParseDate и оператора вывода в поток дл€ класса Date;

// класс Date
// функци€ ParseDate 
// оператор вывода в поток дл€ класса Date.

int Date :: GetYear() const { return YEAR; }
int Date :: GetMonth() const { return MONTH; }
int Date :: GetDay() const { return DAY; }

Date ParseDate(istream& is) {
	bool ok = true;

	int year;
	ok = ok && (is >> year);
	//ok = ok && (is.peek() == '-');
	is.ignore(1);

	int month;
	ok = ok && (is >> month);
	//ok = ok && (is.peek() == '-');
	is.ignore(1);

	int day;
	ok = ok && (is >> day);

	//if (!ok) {
	//	throw invalid_argument("");
	//}
	return Date(year, month, day);
}

bool operator<(const Date& lhs, const Date& rhs) {
	return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
		vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator==(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear() &&
		lhs.GetMonth() == rhs.GetMonth() &&
		lhs.GetDay() == rhs.GetDay()) {
		return 1;
	}
	else return 0;
}

bool operator!=(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear() ||
		lhs.GetMonth() != rhs.GetMonth() ||
		lhs.GetDay() != rhs.GetDay()) {
		return 1;
	}
	else return 0;
}


ostream& operator<<(ostream& stream, const Date& hs) {
	stream << setw(4) << setfill('0') << hs.GetYear() <<
		"-" << setw(2) << setfill('0') << hs.GetMonth() <<
		"-" << setw(2) << setfill('0') << hs.GetDay();
	return stream;
}


ostream& operator << (ostream& out, const pair<Date, string>& p) {
	out << p.first << " " << p.second;
	return out;
}
