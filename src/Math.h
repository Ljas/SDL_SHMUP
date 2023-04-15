#pragma once
#include <iostream>

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

	double x, y;
};