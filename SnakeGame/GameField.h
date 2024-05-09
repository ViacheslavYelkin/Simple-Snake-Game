#pragma once

#include <memory>

#include "Point.h"

class GameField {
	friend class GameFieldBuilder;
	friend class GameFieldRenderer;

public:

	GameField(int length, int height);
	~GameField();

	char at(const std::unique_ptr<Point>& pos) const;
	char atBuffer(const std::unique_ptr<Point>& pos) const;
	int insert(char element, const std::unique_ptr<Point>& pos);
	int insertInBuffer(char element, const std::unique_ptr<Point>& pos);
	int size() const;
	int rows() const;
	int columns() const;
	bool isInBounds(const std::unique_ptr<Point>& pos) const;

private:
	void initializeField();

private:
	int		rows_;
	int		columns_;
	char**  field_;
	char**  prev_field_;
	char    default_fill_character_;

};