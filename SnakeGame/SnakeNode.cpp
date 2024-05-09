#include <memory>

#include "Point.h"
#include "Snake.h"
#include "GameObject.h"
#include "SnakeNode.h"

SnakeNode::SnakeNode(std::shared_ptr<GameField> field)
	: GameObject(field, 'S')
{
	next_ = nullptr;
}

SnakeNode::SnakeNode(const std::shared_ptr<SnakeNode>& node)
	: GameObject(node->game_field_, node->sign_)
{
	this->location_ = std::make_unique<Point>(node->location_);
	this->next_ = node->next_;
}

void SnakeNode::spawn(const std::unique_ptr<Point>& location)
{
	if (!location_)
	{
		location_ = std::make_unique<Point>();
	}

	if (location_ != location) 
	{
		location_.operator*() = location.operator*();
	}

	game_field_->insert(sign_, location_);
}

void SnakeNode::subscribe(std::shared_ptr<GameObject> obj)
{
	objects_.push_back(obj);
}

void SnakeNode::unsubscribe(std::shared_ptr<GameObject> obj)
{
	objects_.erase(
		std::remove(std::begin(objects_), std::end(objects_), obj),
		std::end(objects_)
	);
}

void SnakeNode::notify()
{
	for (auto&& obj : objects_) 
	{
		if (this->location_ == obj->location_.operator*())
		{
			Snake::snake_alive_ = false;
		}
	}
}
