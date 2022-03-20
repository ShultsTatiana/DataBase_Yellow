#include "node.h"
using namespace std;

// файлы должны содержать объ¤влени¤ и определени¤ класса Node, 
// а также всех его потомков (см. выше), которые представл¤ют собой 
// узлы абстрактного синтаксического дерева, 
// формируемого функцией ParseCondition;

// классы Node, 
// EmptyNode, DateComparisonNode, EventComparisonNode и LogicalOperationNode Ч 
// сформировать их иерархию и публичный интерфейс из main и ParseCondition;

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
    return true;
}

bool DateComparisonNode :: Evaluate(const Date& date, const string& event) const {
    switch (cmp_) {
    case Comparison::Less :
        return date < date_;
    case Comparison::LessOrEqual :
        return (date < date_) || (date == date_);
    case Comparison::Greater :
        return !(date < date_) && !(date == date_);
    case Comparison::GreaterOrEqual :
        return !(date < date_);
    case Comparison::Equal:
        return date == date_;
    case Comparison::NotEqual :
        return date != date_;
    }
}

bool EventComparisonNode :: Evaluate(const Date& date, const string& event) const {
    switch (cmp_) {
    case Comparison::Less:
        return event < value_;
    case Comparison::LessOrEqual:
        return event <= value_;
    case Comparison::Greater:
        return event > value_;
    case Comparison::GreaterOrEqual:
        return event >= value_;
    case Comparison::Equal:
        return event == value_;
    case Comparison::NotEqual:
        return event != value_;
    }
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
    switch (cmp_) {
    case LogicalOperation::Or:
        return left_->Evaluate(date, event) || right_->Evaluate(date, event);
    case LogicalOperation::And:
        return left_->Evaluate(date, event) && right_->Evaluate(date, event);
    }
}
