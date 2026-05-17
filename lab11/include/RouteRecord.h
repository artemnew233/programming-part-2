#pragma once
#include <string>
#include <sstream>

// Part 2a: RouteRecord<CodeType, MetricType> — binds a route code to a metric value.
template <typename CodeType, typename MetricType>
class RouteRecord {
public:
    RouteRecord(CodeType code, MetricType metric)
        : code_(std::move(code)), metric_(std::move(metric)) {}

    const CodeType& code() const { return code_; }
    const MetricType& metric() const { return metric_; }

    std::string toString() const {
        std::ostringstream oss;
        oss << code_ << " -> " << metric_;
        return oss.str();
    }

private:
    CodeType code_;
    MetricType metric_;
};
