#pragma once

#include <memory>

#include "GameField.h"

class GameFieldRenderer {
public:
	GameFieldRenderer() = default;
	GameFieldRenderer(std::shared_ptr<GameField> game_field);

	void addGameField(std::shared_ptr<GameField> game_field);
	void printGameField();

private:
	std::shared_ptr<GameField> game_field_;
	std::shared_ptr<GameField> prev_game_field_;
};