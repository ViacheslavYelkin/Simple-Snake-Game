#pragma once

#include <memory>

#include "GameObject.h"
#include "Point.h"

struct SnakeNode : public GameObject {
private:
	friend class Snake;

public:
	SnakeNode(std::shared_ptr<GameField> field);
	SnakeNode(const std::shared_ptr<SnakeNode>& node);

	virtual ~SnakeNode() = default;

	virtual void spawn(const std::unique_ptr<Point>& location);
	virtual void subscribe(std::shared_ptr<GameObject> obj);
	virtual void unsubscribe(std::shared_ptr<GameObject> obj);
	virtual void notify();

public:
	std::shared_ptr<SnakeNode> next_{};

};