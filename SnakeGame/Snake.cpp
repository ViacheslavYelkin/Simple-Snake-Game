#include <thread>
#include <chrono>
#include <memory>

#include "Apple.h"
#include "SnakeNode.h"
#include "GameObject.h"
#include "EDirection.h"
#include "Snake.h"

Snake::Snake(std::shared_ptr<GameField> field)
	: GameObject(field, 'S'), head_{std::make_shared<SnakeNode>(field)}
{
	location_ = std::make_unique<Point>();
	snake_speed_modifier_ = k_max_snake_speed_modifier_;
}

Snake::~Snake()
{
	std::shared_ptr<SnakeNode> curr = head_->next_;
	while (curr) 
	{
		head_->unsubscribe(curr);
		curr = curr->next_;
	}
}

void Snake::eat()
{
	std::unique_ptr<Point> offset = std::make_unique<Point>();
	getOffsetPoint(offset);

	if(tail_)
	{
		std::shared_ptr<SnakeNode> next = std::make_shared<SnakeNode>(game_field_);
		next->location_ = std::make_unique<Point>();
		next->location_.operator*() = tail_->location_.operator*();
		next->location_.operator*() -= offset.operator*();

		tail_->next_ = next;
		tail_ = next;

	}
	else 
	{
		tail_ = std::make_shared<SnakeNode>(game_field_);
		tail_->location_ = std::make_unique<Point>();
		tail_->location_.operator*() = head_->location_.operator*();
		tail_->location_.operator*() -= offset.operator*();

		head_->next_ = tail_;
	}
	head_->subscribe(tail_);
	apples_eaten_++;
	modifySpeed();
}

void Snake::move(EDirection direction)
{
	direction_ = direction;
	std::unique_ptr<Point> offset = std::make_unique<Point>();
	getOffsetPoint(offset);

	std::shared_ptr<SnakeNode> curr = head_->next_;
	std::shared_ptr<SnakeNode> prev = std::make_shared<SnakeNode>(head_);

	game_field_->insert(' ',
						head_->location_
					   );

	head_->location_.operator*() += offset.operator*();
	if (!game_field_->isInBounds(head_->location_))
	{
		moveToOppositeSide();
	}

	head_->spawn(head_->location_);
	location_.operator*() = head_->location_.operator*();
	head_->notify();

	while (curr) 
	{
		std::shared_ptr<SnakeNode> temp = std::make_shared<SnakeNode>(curr);
		game_field_->insert(' ', curr->location_);
		curr->location_.operator*() = prev->location_.operator*();
		curr->spawn(curr->location_);
		prev = temp;
		curr = curr->next_;
	}
}

void Snake::spawn(const std::unique_ptr<Point>& location)
{
	if (!head_->location_) {
		head_->spawn(std::make_unique<Point>(location));
		location_.operator*() = head_->location_.operator*();
	}
}

void Snake::modifySpeed()
{
	if (apples_eaten_ % apples_eaten_to_modify_speed_ == 0) 
	{
		snake_speed_modifier_ = (snake_speed_modifier_ >= k_min_snake_speed_modifier_) ? 
								snake_speed_modifier_ - k_decrease_snake_speed_modifier_by_ :
								k_min_snake_speed_modifier_;
	}
}

void Snake::moveToOppositeSide()
{
	switch (direction_)
	{
	case EDirection::UP:
		head_->location_->x_ = game_field_->rows() - 1;
		break;
	case EDirection::DOWN:
		head_->location_->x_ = 1;
		break;
	case EDirection::LEFT:
		head_->location_->y_ = game_field_->columns() - 1;
		break;
	case EDirection::RIGHT:
		head_->location_->y_ = 0;
		break;
	}
}

void Snake::getOffsetPoint(std::unique_ptr<Point>& offset)
{
	switch (direction_)
	{
	case EDirection::UP:
		offset->x_ = -1;
		break;
	case EDirection::DOWN:
		offset->x_ = 1;
		break;
	case EDirection::LEFT:
		offset->y_ = -1;
		break;
	case EDirection::RIGHT:
		offset->y_ = 1;
		break;
	}
}


void Snake::subscribe(std::shared_ptr<GameObject> obj)
{
}

void Snake::unsubscribe(std::shared_ptr<GameObject> obj)
{
}

void Snake::notify()
{
}