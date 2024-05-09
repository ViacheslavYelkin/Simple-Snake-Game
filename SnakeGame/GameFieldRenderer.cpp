#include <memory>
#include <thread>
#include <string>
#include <chrono>
#include <iostream>
#include <Windows.h> 

#include "Point.h"
#include "Console.h"
#include "GameField.h"
#include "Framerate.h"
#include "QuitStatements.h"
#include "GameFieldRenderer.h"

GameFieldRenderer::GameFieldRenderer(std::shared_ptr<GameField> game_field)
	: game_field_{ game_field }
{
}

void GameFieldRenderer::addGameField(std::shared_ptr<GameField> game_field)
{
    game_field_ = game_field;
}

void GameFieldRenderer::printGameField()
{
	while (!(QUIT))
    {
        Console::cleanConsole();
		// printing game field with different formatting
		for (int i{}; i < game_field_->rows_; i++) 
        {
			for (int j{}; j < game_field_->columns_; j++) 
            {
                if (game_field_->at(std::make_unique<Point>(i, j)) != 'A' &&
                    game_field_->at(std::make_unique<Point>(i, j)) != 'S' && 
                    game_field_->at(std::make_unique<Point>(i, j)) == game_field_->atBuffer(std::make_unique<Point>(i, j)))
                {
                    continue;
                }

                Console::setCursorPosition(j, i);
				std::cout << game_field_->at(std::make_unique<Point>(i, j));
                game_field_->insertInBuffer(game_field_->at(std::make_unique<Point>(i, j)), std::make_unique<Point>(i, j));
			}
			std::cout << '\n';
		}
        std::this_thread::sleep_for(std::chrono::milliseconds(UPDATE_FREQUENCY));
	}
}