#include <windows.h>
#include <memory>


#include "Point.h"
#include "Console.h"
#include "GameField.h"
#include "GameFieldBuilder.h"

GameFieldBuilder::GameFieldBuilder()
	: game_field_{ nullptr }
{
}

void GameFieldBuilder::buildGameField()
{
	int rows;
	int columns;
	Console::getConsoleSize(rows, columns);

	// Creating GameField object with size of console width and height
	game_field_ = std::make_shared<GameField>(rows, columns); 

	// Initializing matrix
	game_field_->initializeField();

	// Filling initialized matrix with default symbol ' '
	for (int i{}; i < game_field_->rows_; i++) 
	{
		for (int j{}; j < game_field_->columns_; j++) 
		{
			game_field_->insert(game_field_->default_fill_character_, std::make_unique<Point>(i, j));
			game_field_->insertInBuffer(game_field_->default_fill_character_, std::make_unique<Point>(i, j));
		}
	}
}

std::shared_ptr<GameField> GameFieldBuilder::getGameField()
{
	return game_field_ ? game_field_ : nullptr; // Checking if game field was created and returning pointer to it
}
