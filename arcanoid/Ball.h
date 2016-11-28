#pragma once
#include "vars.h"

//класс шарик
class Ball
{
public:
	float x, y, dx, dy, r; //коорлинаты шарика и его скорости, радиус
	bool active; //переменная состояния мячика
	Ball(float, float, float);
	void move();// функция движения шарика
	~Ball();

private:

};

Ball::Ball(float x_, float y_, float r_) : x(x_), y(y_), dx(), dy(), r(r_), active(false)
{
}

Ball::~Ball()
{
}

void Ball::move() {

	x += dx;
	y += dy;
	//проверка близости к границам
	if (x - r <= 0) //к верху
	{
		x = r;
		dx *= -1;
	}
	else if (y - r <= 0) //к левому краю
	{
		y = r;
		dy *= -1;
	}
	else if (x + r >= 300) //к правому краю
	{
		x = 300 - r;
		dx *= -1;
	}
	else if (y + r >= r_y && y + r <= r_y + r_h && x > r_x && x < r_x + r_w) // взаимодействие с ракеткой
	{
		y = 300 - r -r_h;
		dy *= -1;
	}
	else if (y > 300) //не выпал ли мячик за нижнюю границу
	{
		active = false;
	}
	

}