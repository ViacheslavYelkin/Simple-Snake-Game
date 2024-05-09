#include <memory>

#include "Point.h"

Point::Point(int x, int y)
	: x_{ x }, y_{ y }
{
}

Point::Point(const std::unique_ptr<Point>& other)
{
	this->x_ = other->x_;
	this->y_ = other->y_;
}

void Point::operator+=(const Point& rhs)
{
	this->x_ += rhs.x_;
	this->y_ += rhs.y_;

}

void Point::operator-=(const Point& rhs)
{
	this->x_ -= rhs.x_;
	this->y_ -= rhs.y_;
}

Point& Point::operator=(const Point& rhs)
{
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
	return (this->x_ == rhs.x_ &&
			this->y_ == rhs.y_);
}
