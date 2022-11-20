#ifndef PLAYER_H
#define PLAYER_H
#include "BaseTypes.h"
#include "Border.h"

class Player
{
public:
	Vector location;

public:
	Vector speed = Vector(0, 0);

private:
	Vector boundDirection = Vector(0, 0);

public:
	double radius = 30;

private:
	Vector safeLocation = Vector(0, 0);

private:
	bool isBounded = false;

private:
	double movementSpeed = 8;

public:
	Player(double x, double y);

	void drawPlayer1(void);
	void drawPlayer2(void);


	void move(double x, double y);

public:
	void bound(Vector &boundDirections, double safeX, double safeY);

	void updateLocation();
	void fixCollision();
public:
	CircleBorder getPlayerBorder();
};

#endif