#pragma once

#include "Snake.h"
#include "InputHandler.h"

#define USER_PRESS_ESCAPE InputHandler::direction_ == 27
#define SNAKE_DIED !Snake::snake_alive_
#define QUIT SNAKE_DIED || USER_PRESS_ESCAPE
#define RESET_QUIT_STATEMENTS InputHandler::direction_ = 'w';\
							  Snake::snake_alive_ = true;