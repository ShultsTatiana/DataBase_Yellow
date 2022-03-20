#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>

using namespace std;

string ParseEvent(istream& is) {
    string event;
    getline(is, event);
    auto it = begin(event);
    for (it; (it != end(event) && *it == ' '); ++it) {}
    event = { it, end(event) };
    return event;
}

void TestAll();

int main() {
    TestAll();

    Database db;

    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        else if (command == "Print") {
            db.Print(cout);
        }
        else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        }
        else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        }
        else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            }
            catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        }
        else if (command.empty()) {
            continue;
        }
        else {
            throw logic_error("Unknown command: " + command);
        }
    }
    return 0;
}

void TestParseEvent() {
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
    {
        Database db;
        vector<string> events = {
            "a", "z", "b", "y", "c", "x", "d", "w", "e", "v"
        };
        for (const auto& e : events) { db.Add(Date(4, 5, 6), e); }

        // I am going to delete every second event to get the following sequence
        vector<string> filtered = { "a", "b", "c", "d", "e" };

        stringstream true_answer;
        for (const auto& e : filtered) {
            true_answer << Date(4, 5, 6) << " " << e << endl;
        }

        int count = db.RemoveIf(
            [](const Date& d, const string& e) { return e > "m"; });

        stringstream my_answer;
        db.Print(my_answer);

        AssertEqual(count, 5, "test 8-1");
        AssertEqual(my_answer.str(), true_answer.str(), "test 8-2"); // <-- this can fail
    }
    {
        Database db;
        int n = 0;
        AssertEqual(db.Last(Date(1, 1, 1)), "No entries", ("test" + to_string(++n)) );
        db.Add(Date(1, 10, 1), "C3");
        db.Add(Date(2, 1, 1), "B3");
        db.Add(Date(3, 1, 1), "A3");
        AssertEqual(db.Last(Date(1,1,1)), "No entries", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(1, 10, 1)), "0001-10-01 C3", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(1, 12, 1)), "0001-10-01 C3", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(2, 1, 1)), "0002-01-01 B3", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(2, 5, 1)), "0002-01-01 B3", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(3, 1, 1)), "0003-01-01 A3", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(4, 10, 1)), "0003-01-01 A3", ("test" + to_string(++n)));
        db.Add(Date(3, 1, 1), "A1");
        db.Add(Date(2, 1, 1), "B1");
        db.Add(Date(1, 10, 1), "C1");
        db.Add(Date(2, 1, 1), "B2");
        db.Add(Date(1, 10, 1), "C2");
        db.Add(Date(3, 1, 1), "A2");
        AssertEqual(db.Last(Date(1, 1, 1)), "No entries", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(1, 10, 1)), "0001-10-01 C2", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(1, 12, 1)), "0001-10-01 C2", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(2, 1, 1)), "0002-01-01 B2", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(2, 5, 1)), "0002-01-01 B2", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(3, 1, 1)), "0003-01-01 A2", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(4, 10, 1)), "0003-01-01 A2", ("test" + to_string(++n)));
    }
    {
        Database db;
        stringstream my_answer;
        my_answer << db.Last(Date(1, 2, 4));
        AssertEqual(my_answer.str(), "No entries", "test 8-3");
        int n = db.RemoveIf([](const Date& d, const string& e) { return e > "m"; });
        AssertEqual(n, 0, "test 8-4");
        db.Add(Date(1, 2, 4), "F");
        db.Add(Date(1, 2, 3), "F");
        db.Add(Date(1, 2, 4), "B");
        db.Add(Date(1, 2, 4), "A");
        vector<string> true_vector1 = {
            "0001-02-03 F",
            "0001-02-04 F",
            "0001-02-04 B",
            "0001-02-04 A",
        };
        stringstream my_answer2;
        stringstream true_answer;
        for (const auto& e : true_vector1) {
            true_answer << e << endl;
        }
        db.Print(my_answer2);
        AssertEqual(my_answer2.str(), true_answer.str(), "test 8-5"); // <-- this can fail
        n = db.RemoveIf([](const Date& d, const string& e) {
            return !(d < Date(1,2,3)) && !(d == Date(1, 2, 3)) && (e > "B");
        });
        AssertEqual(n, 1, "test 8-6");
        stringstream my_answer3;
        stringstream true_answer2 ("0001-02-03 F\n0001-02-04 B\n0001-02-04 A\n");
        db.Print(my_answer3);
        AssertEqual(my_answer3.str(), true_answer2.str(), "test 8-7"); // <-- this can fail
        n = db.RemoveIf([](const Date& d, const string& e) {
            return (d < Date(1, 2, 4));
        });
        AssertEqual(n, 1, "test 8-8");
        stringstream my_answer4;
        stringstream true_answer3("0001-02-04 B\n0001-02-04 A\n");
        db.Print(my_answer4);
        AssertEqual(my_answer4.str(), true_answer3.str(), "test 8-9"); // <-- this can fail
    }
    {
        Database db;

        db.Add(Date(1, 1, 1), "aa");
        db.Add(Date(1, 1, 1), "ab");
        db.Add(Date(1, 1, 1), "ac");
        db.Add(Date(1, 1, 2), "ba");
        db.Add(Date(1, 1, 2), "bb");
        db.Add(Date(1, 1, 2), "bc");
        Assert((db.Last(Date(1, 1, 1)) == "0001-01-01 ac"), "test007");
        Assert((db.Last(Date(1, 1, 2)) == "0001-01-02 bc"), "test008");

        istringstream is(R"(event == "bb")");
        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
        };
        db.RemoveIf(predicate);
        Assert((db.Last(Date(1, 1, 1)) == "0001-01-01 ac"), "test009");
        Assert((db.Last(Date(1, 1, 2)) == "0001-01-02 bc"), "test010");

        db.Add(Date(1, 1, 2), "bb");
        Assert((db.Last(Date(1, 1, 1)) == "0001-01-01 ac"), "test011");
        Assert((db.Last(Date(1, 1, 2)) == "0001-01-02 bb"), "test012");

        istringstream is2(R"(event == "bc")");
        auto condition2 = ParseCondition(is2);
        auto predicate2 = [condition2](const Date& date, const string& event) {
            return condition2->Evaluate(date, event);
        };        
        db.RemoveIf(predicate2);
        Assert((db.Last(Date(1, 1, 1)) == "0001-01-01 ac"), "test013");
        Assert((db.Last(Date(1, 1, 2)) == "0001-01-02 bb"), "test014");

        istringstream is3(R"(event == "bb")");
        auto condition3 = ParseCondition(is3);
        auto predicate3 = [condition3](const Date& date, const string& event) {
            return condition3->Evaluate(date, event);
        };
        db.RemoveIf(predicate3);
        Assert((db.Last(Date(1, 1, 2)) == "0001-01-02 ba"), "test015");
    }
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
}
