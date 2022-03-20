#pragma once

#include <memory>

#include "date.h"

// файлы должны содержать объ€влени€ и определени€ класса Node, 
// а также всех его потомков (см. выше), которые представл€ют собой 
// узлы абстрактного синтаксического дерева, 
// формируемого функцией ParseCondition;

// классы Node, 
// EmptyNode, DateComparisonNode, EventComparisonNode и LogicalOperationNode Ч 
// сформировать их иерархию и публичный интерфейс из main и ParseCondition;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    Or,
    And
};

class Node {
public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
    bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& cmp, const Date& date)
        : cmp_(cmp), date_(date) {
    }
    bool Evaluate(const Date& date, const string& event) const override;

private:
    const Comparison cmp_;
    const Date date_;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& cmp, const string& value)
        : cmp_(cmp), value_(value) {
    }
    bool Evaluate(const Date& date, const string& event) const override;
private:
    const Comparison cmp_;
    const string value_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode (
        const LogicalOperation& logical_operation,
        const shared_ptr<Node>& left,
        const shared_ptr<Node>& right)
        : cmp_(logical_operation)
        , left_(left)
        , right_(right) {
    }
    bool Evaluate(const Date& date, const string& event) const override;
private:
    const LogicalOperation cmp_;
    const shared_ptr<Node> left_;
    const shared_ptr<Node> right_;
};