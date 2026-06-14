#pragma once

#include <cmath>
#include <span>
#include <stdexcept>
#include <string>
#include <vector>

namespace lab18 {

/**
 * \brief A single waypoint on a delivery route.
 */
struct Point {
    std::string name; ///< Waypoint label
    double      x{};  ///< X coordinate
    double      y{};  ///< Y coordinate
};

/**
 * \brief Manages an ordered sequence of delivery route waypoints.
 *
 * Provides route length, longest segment detection, and empty-route checks.
 * All coordinates use the same unit; no projection is applied.
 */
class Route {
public:
    /**
     * \brief Constructs a route from an existing list of points.
     * \param points Ordered waypoints. May be empty.
     */
    explicit Route(std::vector<Point> points);

    /**
     * \brief Adds a waypoint at the end of the route.
     * \param p The point to append.
     */
    void addPoint(const Point& p);

    /**
     * \brief Returns whether the route has no waypoints.
     */
    [[nodiscard]] bool empty() const noexcept;

    /**
     * \brief Returns the number of waypoints.
     */
    [[nodiscard]] std::size_t size() const noexcept;

    /**
     * \brief Returns the waypoints as a read-only span.
     */
    [[nodiscard]] std::span<const Point> points() const noexcept;

    /**
     * \brief Computes the total Euclidean route length.
     * \return 0.0 for routes with fewer than two points.
     */
    [[nodiscard]] double totalLength() const noexcept;

    /**
     * \brief Returns the length of the longest individual segment.
     * \return 0.0 for routes with fewer than two points.
     */
    [[nodiscard]] double longestSegment() const noexcept;

    /**
     * \brief Returns the index of the start of the longest segment.
     * \throws std::out_of_range if the route has fewer than two points.
     */
    [[nodiscard]] std::size_t longestSegmentIndex() const;

    /**
     * \brief Euclidean distance between two points.
     */
    static double distance(const Point& a, const Point& b) noexcept;

private:
    std::vector<Point> points_;
};

} // namespace lab18
