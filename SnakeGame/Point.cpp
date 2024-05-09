#include <memory>

#include "Point.h"

Point::Point(int x, int y)
	: x_{ x }, y_{ y }
{
}

Point::Point(const std::unique_ptr<Point>& other)
{
	// Copying coords of passed Point 
	this->x_ = other->x_;
	this->y_ = other->y_;
}

void Point::operator+=(const Point& rhs)
{
	// Adding coords of given Point to current
	this->x_ += rhs.x_;
	this->y_ += rhs.y_;

}

void Point::operator-=(const Point& rhs)
{
	// Subtracting coords of given Point from current 
	this->x_ -= rhs.x_;
	this->y_ -= rhs.y_;
}

Point& Point::operator=(const Point& rhs)
{
	// Copying coords of passed Point
	if (this == &rhs)
	{
		return *this;
	}

	this->x_ = rhs.x_;
	this->y_ = rhs.y_;

	return *this;
}

bool Point::operator==(const Point& rhs)
{
	// Checking if passed Point located at same position as current
	return (this->x_ == rhs.x_ &&
			this->y_ == rhs.y_);
}
