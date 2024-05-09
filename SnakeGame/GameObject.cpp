#include "GameObject.h"

GameObject::GameObject(std::shared_ptr<GameField> field, char sign)
	: game_field_{ field }, sign_{sign}
{
}
