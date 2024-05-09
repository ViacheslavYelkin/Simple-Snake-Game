#pragma once

#include <memory>
#include <vector>

#include "Point.h"
#include "GameField.h"

class GameObject {
	friend class Apple;
	friend struct SnakeNode;
	friend class Snake;
	
public:

	GameObject(std::shared_ptr<GameField> field, char sign);
	virtual ~GameObject() = default;

	virtual void spawn(const std::unique_ptr<Point>& location) = 0;
	virtual void subscribe(std::shared_ptr<GameObject> obj) = 0;
	virtual void unsubscribe(std::shared_ptr<GameObject> obj) = 0;
	virtual void notify() = 0;

protected:
	char									 sign_;
	std::unique_ptr<Point>					 location_;
	std::shared_ptr<GameField>				 game_field_;
	std::vector<std::shared_ptr<GameObject>> objects_;

};