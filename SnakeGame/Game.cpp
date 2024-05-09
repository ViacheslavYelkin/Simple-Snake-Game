#include <memory>
#include <thread>
#include <string>
#include <iomanip>
#include <conio.h>
#include <iostream>

#include "Point.h"
#include "Snake.h"
#include "Apple.h"
#include "Console.h"
#include "GameField.h"
#include "Framerate.h"
#include "InputHandler.h"
#include "QuitStatements.h"
#include "GameFieldBuilder.h"
#include "GameFieldRenderer.h"
#include "Game.h"

void Game::prepareConsole()
{
    Console::makeCursorInvisible();
}

void Game::prepareGameField()
{
    GameFieldBuilder builder;
    builder.buildGameField();

    game_field_ = builder.getGameField();
    renderer_.addGameField(game_field_);
}

void Game::prepareSnake()
{
    snake_ = std::make_shared<Snake>(game_field_);

    snake_->spawn(std::make_unique<Point>(game_field_->rows() / 2,
        game_field_->columns() / 2)
    );
}

void Game::prepareApple()
{
    apple_ = std::make_unique<Apple>(game_field_);
    apple_->subscribe(snake_);
    apple_->spawn(std::make_unique<Point>());
}

void Game::runThreads()
{
    std::jthread print_thread(&GameFieldRenderer::printGameField, &renderer_);
    std::jthread read_user_input_thread(&InputHandler::readDirection);

    auto move_snake = [this]()
        {
            while (!(QUIT))
            {
                this->snake_->move(InputHandler::getDirection());
                std::this_thread::sleep_for(std::chrono::milliseconds(SNAKE_SPEED);
            }
        };
    std::jthread move_snake_thread(move_snake);

    auto eat_apple = [this]()
        {
            while (!(QUIT))
            {
                this->apple_->notify();
                std::this_thread::sleep_for(std::chrono::milliseconds(UPDATE_FREQUENCY));
            }
        };
    std::jthread eat_apple_thread(eat_apple);
}

void Game::printEndGameSentences()
{
    Console::cleanConsole();

    std::string score_sentence{ "Your score: " + std::to_string(Snake::apples_eaten_) + "\n\n" };
    std::string restart_sentece{ "To restart - press 'R'\n" };
    std::string escape_sentece{ "Stop session - press 'ESC'\n" };

    for (int i{}; i < (game_field_->rows() / 2) - 2; i++) 
    {
        std::cout << '\n';
    }

    std::cout << std::setw(game_field_->columns() / 2 + score_sentence.size() / 2) << score_sentence;;
    std::cout << std::setw(game_field_->columns() / 2 + restart_sentece.size() / 2) << restart_sentece;
    std::cout << std::setw(game_field_->columns() / 2 + escape_sentece.size() / 2) << escape_sentece;
}

void Game::run()
{
   repeat:
    prepareConsole();
    prepareGameField();
    prepareSnake();
    prepareApple();
    
    runThreads();

    printEndGameSentences();

    if (RESTART) 
    {
       RESET_QUIT_STATEMENTS
       Snake::apples_eaten_ = 0;
       goto repeat;            
    } 

    Console::cleanConsole();
}


