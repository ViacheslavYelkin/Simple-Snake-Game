#pragma once

#include <random>
#include <memory>

#include "GameField.h"
#include "GameObject.h"


class Apple : public GameObject{
public:

	Apple(std::shared_ptr<GameField> field);
	virtual ~Apple() = default;

	virtual void subscribe(std::shared_ptr<GameObject> obj);
	virtual void unsubscribe(std::shared_ptr<GameObject> obj);
	virtual void notify();

	virtual void spawn(const std::unique_ptr<Point>& location);

private:
	bool isLocationOccupied(const std::unique_ptr<Point>& location);
	void regeneratePosition(const std::unique_ptr<Point>& location);

private:
	std::random_device				rd_{};
	std::mt19937					generate_{rd_()};
	std::uniform_int_distribution<> rand_row_{1, game_field_->rows() - 1};
	std::uniform_int_distribution<> rand_column_{1, game_field_->columns() - 1};
};