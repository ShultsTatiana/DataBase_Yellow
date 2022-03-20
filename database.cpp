#include "database.h"

//����� ������ ��������� ���������� � ����������� ������ Database;
// ����� Database - ���� ������ � ������� ��� ��������� ���������, 
// ����������� �� ���, ��� �� ������������ � ������� main;


void Database :: Add(const Date& date, const string& event) {
	bool f = data_event[date].second.count(event);
	if (f == 0) {
		data_event[date].first.push_back(event);
		data_event[date].second.insert(event);
	}
}

ostream& Database::Print(ostream& stream) const {
	if (!data_event.empty()) {
		for (const auto& i : data_event) {
			for (const auto& j : i.second.first) {
				stream << i.first << " " << j << endl;
			}
		}
	}
	return stream;
}

string Database::Last(const Date& date) const {
	// ����� ���� �������� ��� ������� ����� ����� ����������, �� ������������ date;
	// �� ���� ������� � ����� ����� ����� ������� ��������� ����������� � ������� � �������, ����������� ������� ������� Print;
	// ���� date ������ ���� �������� ���, ���������� ������� �No entries�.
	if (data_event.empty()) {
		return "No entries";
	}
	else {
		auto it = data_event.lower_bound(date);
		if (it == end(data_event)) {
			it--;
		}
		else {
			if (it->first != date) {
				if (it == begin(data_event)) {
					return "No entries";
				}
				it--;
			}
		}
		auto it2 = end(it->second.first);
		it2--;
		stringstream is;
		is << make_pair(it->first, *it2);
		return is.str();
	}
}