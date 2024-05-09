#include <random>
#include <memory>
#include <typeinfo>

#include "Snake.h"
#include "GameField.h"
#include "GameObject.h"
#include "Apple.h"

Apple::Apple(std::shared_ptr<GameField> field)
	: GameObject(field, 'A')
{
	location_ = std::make_unique<Point>();
}

void Apple::subscribe(std::shared_ptr<GameObject> obj)
{
	objects_.push_back(obj);

	std::shared_ptr<SnakeNode> curr = dynamic_cast<Snake&>(obj.operator*()).head_->next_;

	while (curr) 
	{
		objects_.push_back(curr);
		curr = curr->next_;
	}
}

void Apple::unsubscribe(std::shared_ptr<GameObject> obj)
{
	objects_.erase(
		std::remove(std::begin(objects_), std::end(objects_), obj),
		std::end(objects_)
	);
}

void Apple::notify()
{
	for (auto&& obj : objects_) 
	{
		if (typeid(obj.operator*()) != typeid(Snake))
		{
			continue;
		}

		if (this->location_ == obj->location_.operator*()) 
		{
			dynamic_cast<Snake&>(obj.operator*()).eat();
			spawn(std::make_unique<Point>());

			objects_.push_back(dynamic_cast<Snake&>(obj.operator*()).tail_);
			return;
		}
	}
}

void Apple::spawn(const std::unique_ptr<Point>& location)
{
	while (isLocationOccupied(location) || location == Point(0,0)) 
	{
		regeneratePosition(location);
	}

	location_.operator*() = location.operator*();

	game_field_->insert(sign_, location_);

}

bool Apple::isLocationOccupied(const std::unique_ptr<Point>& location)
{
	for (auto&& obj : objects_) 
	{
		if (location == obj->location_.operator*())
		{
			return true;
		}
	}
	return false;
}

void Apple::regeneratePosition(const std::unique_ptr<Point>& location)
{
	location->x_ = rand_row_(generate_);
	location->y_ = rand_column_(generate_);
}
