#pragma once

enum class EDirection;

class InputHandler {
public:

	static void readDirection();
	static EDirection getDirection();
	
public:
	inline static char direction_{'w'};
};