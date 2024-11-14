#include "Segment.h"

#include <algorithm>
#include <cmath>
#include <utility>

Segment::Segment(Vector2 start, Vector2 end): _start(std::move(start)), _end(std::move(end)) {}

Vector2 Segment::start() const { return _start; }

Segment& Segment::setStart(Vector2 start) {
    _start = std::move(start);
    return *this;
}

Vector2 Segment::end() const { return _end; }

Segment& Segment::setEnd(Vector2 end) {
    _end = std::move(end);
    return *this;
}

bool Segment::isLying(const Vector2& v) const {
    return v.x <= std::max(_start.x, _end.x) and v.x >= std::min(_start.x, _end.x) and
           v.y <= std::max(_start.y, _end.y) and v.y >= std::min(_start.y, _end.y);
}

#define INFINITE_POINTS 0

std::optional<Vector2> Segment::intersects(const Segment& segment) const {
    const Vector2::Orientation orientation1(Vector2::orientation(_start, _end, segment._start));
    const Vector2::Orientation orientation2(Vector2::orientation(_start, _end, segment._end));
    const Vector2::Orientation orientation3(
            Vector2::orientation(segment._start, segment._end, _start));
    const Vector2::Orientation orientation4(
            Vector2::orientation(segment._start, segment._end, _end));

    // General case: if the orientations are different, the segments intersect
    if (orientation1 != orientation2 && orientation3 != orientation4) {
        // Compute the intersection point using parametric equations
        float denom = (_end.x - _start.x) * (segment._end.y - segment._start.y) -
                      (_end.y - _start.y) * (segment._end.x - segment._start.x);

        if (denom == INFINITE_POINTS)
            return Vector2::NANV;  // Parallel or collinear

        const float lambda = ((_start.x - segment._start.x) * (segment._end.y - segment._start.y) -
                              (_start.y - segment._start.y) * (segment._end.x - segment._start.x)) /
                             denom;

        return _start + (_end - _start) * lambda;
    }

    // Special cases:
    // _start, _end and segment._start are collinear and segment._start lies on segment [_start,
    // _end]
    if (orientation1 == Vector2::Orientation::Collinear and isLying(segment._start))
        return segment._start;

    // _start, _end and segment._end are collinear and segment._end lies on segment [_start,
    // _end]
    if (orientation2 == Vector2::Orientation::Collinear and isLying(segment._end))
        return segment._end;

    // segment._start, segment._end and _start are collinear and _start lies on segment
    // [segment._start, segment._end]
    if (orientation3 == Vector2::Orientation::Collinear and segment.isLying(_start))
        return _start;

    // segment._start, segment._end and _end are collinear and _end lies on segment [segment._start,
    // segment._end]
    if (orientation4 == Vector2::Orientation::Collinear and segment.isLying(_end))
        return _end;

    // If none of the above, the segments don't intersect
    return std::nullopt;
}
