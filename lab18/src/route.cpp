#include "lab18/route.hpp"

namespace lab18 {

Route::Route(std::vector<Point> points) : points_(std::move(points)) {}

void Route::addPoint(const Point& p) { points_.push_back(p); }

bool        Route::empty() const noexcept { return points_.empty(); }
std::size_t Route::size()  const noexcept { return points_.size(); }

std::span<const Point> Route::points() const noexcept {
    return std::span<const Point>(points_);
}

double Route::distance(const Point& a, const Point& b) noexcept {
    const double dx = a.x - b.x;
    const double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

double Route::totalLength() const noexcept {
    if (points_.size() < 2) return 0.0;
    double total = 0.0;
    for (std::size_t i = 1; i < points_.size(); ++i)
        total += distance(points_[i - 1], points_[i]);
    return total;
}

double Route::longestSegment() const noexcept {
    if (points_.size() < 2) return 0.0;
    double best = 0.0;
    for (std::size_t i = 1; i < points_.size(); ++i) {
        const double d = distance(points_[i - 1], points_[i]);
        if (d > best) best = d;
    }
    return best;
}

std::size_t Route::longestSegmentIndex() const {
    if (points_.size() < 2)
        throw std::out_of_range("Route::longestSegmentIndex: fewer than two points");
    std::size_t best = 0;
    double      bestDist = 0.0;
    for (std::size_t i = 1; i < points_.size(); ++i) {
        const double d = distance(points_[i - 1], points_[i]);
        if (d > bestDist) { bestDist = d; best = i - 1; }
    }
    return best;
}

} // namespace lab18
