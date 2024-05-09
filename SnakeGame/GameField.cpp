#include <memory>

#include "Point.h"
#include "GameField.h"

GameField::GameField(int length, int height)
	: rows_{ length }, columns_{ height }, default_fill_character_{ ' ' }
{
}

GameField::~GameField()
{
	// deleting all allocated memory for matrix
	for (int i{}; i < rows_; i++) 
	{
		delete[] field_[i];
	}

	delete[] field_;
}

char GameField::at(const std::unique_ptr<Point>& pos) const
{
	return field_[pos->x_][pos->y_]; // returning symbol at requested position
}

char GameField::atBuffer(const std::unique_ptr<Point>& pos) const
{
	return prev_field_[pos->x_][pos->y_];
}

int GameField::insert(char element, const std::unique_ptr<Point>& pos)
{
	// checking if given location in bound of matrix
	// if true replacing/inserting new character at given location
	// else returning -1
	if (isInBounds(pos)) 
	{
		field_[pos->x_][pos->y_] = element;
		return 0;
	}
	return -1;
}

int GameField::insertInBuffer(char element, const std::unique_ptr<Point>& pos)
{
	if (isInBounds(pos)) 
	{
		prev_field_[pos->x_][pos->y_] = element;
		return 0;
	}
	return -1;
}

int GameField::size() const
{
	return rows_ * columns_; // returning full size of matrix
}

int GameField::rows() const
{
	return rows_;
}

int GameField::columns() const
{
	return columns_;
}

void GameField::initializeField()
{
	field_ = new char* [rows_]; // initializing rows of matrix
	prev_field_ = new char* [rows_];

	// initializing columns of matrix
	for (int i{}; i < rows_; i++) 
	{
		field_[i] = new char[columns_];
		prev_field_[i] = new char[columns_];
	}
}

bool GameField::isInBounds(const std::unique_ptr<Point>& pos) const
{
	// checking if given values are in bounds of current matrix
	return (
		(pos->x_ >= 1 && pos->x_ < rows_) &&
		(pos->y_ >= 0 && pos->y_ < columns_)
		);
}

