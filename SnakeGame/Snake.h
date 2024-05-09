#pragma once

#include <memory>
 
#include "Apple.h"
#include "SnakeNode.h"
#include "Framerate.h"
#include "GameObject.h"

#define SNAKE_SPEED static_cast<int>((UPDATE_FREQUENCY) * Snake::snake_speed_modifier_))

enum class EDirection;

class Snake : public GameObject{
private:
	friend class Apple;

public:

	Snake(std::shared_ptr<GameField> field);
	virtual ~Snake();

	void eat();
	void move(EDirection direction);
	virtual void spawn(const std::unique_ptr<Point>& location);
	virtual void subscribe(std::shared_ptr<GameObject> obj);
	virtual void unsubscribe(std::shared_ptr<GameObject> obj);
	virtual void notify();
	
public:	
	inline static int		   apples_eaten_{};
	inline static bool		   snake_alive_{ true };
	inline static float		   snake_speed_modifier_{};

private:
	void modifySpeed();
	void moveToOppositeSide();
	void getOffsetPoint(std::unique_ptr<Point>& offset);

private:
	const float				   k_max_snake_speed_modifier_{2.f};
	const float				   k_min_snake_speed_modifier_{1.f};
	const float				   k_decrease_snake_speed_modifier_by_{ 0.2f };

	int						   apples_eaten_to_modify_speed_{10};
	EDirection				   direction_{};
	std::shared_ptr<SnakeNode> head_{};
	std::shared_ptr<SnakeNode> tail_{};
	

};