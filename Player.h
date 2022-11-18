#ifndef PLAYER_H
#define PLAYER_H
#include "BaseTypes.h"

class Player
{
public:
	Vector location;

public:
	Vector speed = Vector(0, 0);

private:
	int movementSpeed = 8;

public:
	Player(int x, int y);

	void drawPlayer(void);

	void move(int x, int y);

	void updateLocation();
};

#endif