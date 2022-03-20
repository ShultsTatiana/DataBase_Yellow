#pragma once

#include "date.h"

#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>
#include <sstream>
#include <deque>


using namespace std;

//файлы должны содержать объ€вление и определение класса Database;
// класс Database - база данных Ч создать его публичный интерфейс, 
// основыва€сь на том, как он используетс€ в функции main;

class Database {
public:
	void Add(const Date& date, const string& event);
	ostream& Print(ostream& stream) const;
	
	template <typename Func>
	int RemoveIf(const Func& predicate) {
		int count = 0;
		deque<Date> map_del;
		for (auto it = begin(data_event); it != end(data_event); it++) {
			pair<vector<string>, set<string>> entry;
			for (auto& j : (*it).second.first) {
				if (!predicate((*it).first, j)) {
					entry.first.push_back(j);
					entry.second.insert(j);
				}
				else count++;
			}

			if (entry.first.size() == 0) {
				map_del.push_back((*it).first);
				//it++;
			}
			else (*it).second = entry;
			//else data_event.erase(it++);
		}
		if (!map_del.empty()) {
			for (Date i : map_del) {
				data_event.erase(i);
			}
		}
		return count;
	}

	template <typename Func>
	deque<pair<Date, string>> FindIf (const Func& predicate) const {
		deque<pair<Date, string>> entry;
		for (const auto& i : data_event) {
			for (const auto& j : i.second.first) {
				if (predicate(i.first, j)) {
					entry.push_back(make_pair(i.first, j));
				}
			}
		}
		return entry;
	}
	
	string Last(const Date& date) const;

private:
	map <Date, pair<vector<string>, set<string>>> data_event;

};
