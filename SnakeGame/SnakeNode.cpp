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
	// Copying data of give node of snake
	this->location_ = std::make_unique<Point>(node->location_);
	this->next_ = node->next_;
}

void SnakeNode::spawn(const std::unique_ptr<Point>& location)
{
	// Initializing location if need
	if (!location_)
	{
		location_ = std::make_unique<Point>();
	}

	// Copying given location to local
	if (location_ != location) 
	{
		location_.operator*() = location.operator*();
	}

	// Adding node to game field to print in console at given location
	game_field_->insert(sign_, location_);
}

void SnakeNode::subscribe(std::shared_ptr<GameObject> obj)
{
	// Subscribing objects to inform in future if current object was collided or modified by subscribed objects.
	objects_.push_back(obj);
}

void SnakeNode::unsubscribe(std::shared_ptr<GameObject> obj)
{
	// Unsubscribing objects
	objects_.erase(
		std::remove(std::begin(objects_), std::end(objects_), obj),
		std::end(objects_)
	);
}

void SnakeNode::notify()
{
	// Checking if current object collided with any of subscribers
	// If true, it means that snake died
	// Else do nothing
	for (auto&& obj : objects_) 
	{
		if (this->location_ == obj->location_.operator*())
		{
			Snake::snake_alive_ = false;
		}
	}
}
