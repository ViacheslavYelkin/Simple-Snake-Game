#pragma once


#include <memory>

#include "Snake.h"
#include "Apple.h"
#include "GameField.h"
#include "GameFieldRenderer.h"

#define RESTART _getch() == 'r'

class Game {
public:
	Game() = default;

	void run();

private:
	void prepareConsole();
	void prepareGameField();
	void prepareSnake();
	void prepareApple();
	void runThreads();
	void printEndGameSentences();

private:
	GameFieldRenderer		   renderer_{};
	std::shared_ptr<Snake>	   snake_;
	std::unique_ptr<Apple>	   apple_{};
	std::shared_ptr<GameField> game_field_{};
};