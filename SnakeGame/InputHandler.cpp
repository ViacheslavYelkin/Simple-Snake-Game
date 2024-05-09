#include <conio.h>

#include "EDirection.h"
#include "QuitStatements.h"
#include "InputHandler.h"

void InputHandler::readDirection()
{
	while (!(QUIT))
	{
		direction_ = _getch();
	}
}

EDirection InputHandler::getDirection()
{
    switch (direction_) 
    {
        case 'w':
            return EDirection::UP;
            break;
        case 's':
            return EDirection::DOWN;
            break;
        case 'd':
            return EDirection::RIGHT;
            break;
        case 'a':
            return EDirection::LEFT;
            break;
        default:
            return EDirection::UP;
    }
}
