#pragma once
#include <iostream>
static int PLAYFIELD_LEFT = 16;
static int PLAYFIELD_TOP = 16;
static int PLAYFIELD_RIGHT = 352;
static int PLAYFIELD_BOTTOM = 464;

struct Vector2d
{
	Vector2d()
		:x(0.0), y(0.0)
	{}

	Vector2d(double p_x, double p_y)
		:x(p_x), y(p_y)
	{}

	void print()
	{
		std::cout << x << ", " << y << std::endl;
	}

	Vector2d(Vector2d a, Vector2d b)
		:x(a.x + b.x), y(a.y + b.y) {

	}

	double x, y;
};