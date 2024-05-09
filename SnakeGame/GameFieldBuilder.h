#pragma once

#include <memory>

#include "GameField.h"

class GameFieldBuilder {
public:

	GameFieldBuilder();

	void buildGameField();
	std::shared_ptr<GameField> getGameField();

private:
	std::shared_ptr<GameField> game_field_;

};