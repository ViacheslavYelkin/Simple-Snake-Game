#pragma once

#include <memory>

struct Point {
public:
	Point() = default;
	Point(int x, int y);
	Point(const std::unique_ptr<Point>& other);

	void operator+= (const Point& rhs);
	void operator-= (const Point& rhs);
	Point& operator= (const Point& rhs);
	bool operator== (const Point& rhs);

public:
	int x_{};
	int y_{};
};