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
//����� ������ ��������� ���������� � ����������� ������ Date, 
//������� ParseDate � ��������� ������ � ����� ��� ������ Date;

// ����� Date
// ������� ParseDate 
// �������� ������ � ����� ��� ������ Date.

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
	const int YEAR;	// ����� ����� �� 0 �� 9999
	const int MONTH;	// ����� ������ �� 1 �� 12 ������������
	const int DAY;		// ����� ��� �� 1 �� 31 ������������
	//int YEAR;	// ����� ����� �� 0 �� 9999
	//int MONTH;	// ����� ������ �� 1 �� 12 ������������
	//int DAY;		// ����� ��� �� 1 �� 31 ������������
};

//void CheckSimbol(istream& is);

Date ParseDate(istream& is);

bool operator<(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
ostream& operator<<(ostream& stream, const Date& hs);
ostream& operator << (ostream& out, const pair<Date, string>& p);
