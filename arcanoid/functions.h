#pragma once
#include "vars.h"


bool  isCollision(Ball&, Brick&); // функция проверки столкновения мяча с кирпичом


void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 0.0);//каким цветом всё стереть | цвет очистки
	glMatrixMode(GL_PROJECTION);//тип матрицы который будет изменять в последующем GL_PROJECTION - матрица проекций
	glLoadIdentity(); //загружаем единичную матрицу
	//glOrtho(-WinWid/2, WinWid/2, -WinHei /2, WinHei/2, -WinHei/2, WinHei/2); //задаётся сетка координат(матрица проекции) относительно центра экрана
	glOrtho(0, WinWid, WinHei, 0, 1, 0); //задаётся сетка координат(матрица проекции) относительно левого верхнего угла
}

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT); //рисуем фон GL_COLOR_BUFFER_BIT - буфер цвета, GL_DEPTH_BUFFER_BIT - буфер глубины

	// рисуем ракетку
	glColor3f(0.2, 0.8, 0.1);
	glRectf(r_x, r_y, r_x + r_w, r_y + r_h); //рисуем прямоугольник

	//рисуем мяч
	glBegin(GL_POLYGON); {
		glColor3f(0.1, 0.5, 0.7);
		for (float i(0); i < 2 * M_PI; i += M_PI / 1000) {
			glVertex2f(ball.x + ball.r*sin(i), ball.y + ball.r*cos(i));
		}
	}glEnd();

	// рисуем блоки
	glBegin(GL_QUADS); {
		for (int i(0); i < 10; i++) {
			glColor3ub(i*25, i*10, 160);
			for (int j(0); j < 15; j++) {
				Brick &b = brick[i][j];
				if (b.active) {
					glVertex2f(b.col*b.w + 1,		 b.raw*b.h + 1);
					glVertex2f(b.col*b.w + b.w - 1,	 b.raw*b.h + 1);
					glVertex2f(b.col*b.w + b.w - 1,	 b.raw*b.h + b.h - 1);
					glVertex2f(b.col*b.w + 1,		 b.raw*b.h + b.h - 1);
				}
			}
		}
	}glEnd();









	glutSwapBuffers(); //при использовании двойного буфера GLUT_DOUBLE
}

void Timer(int value)
{
	
	//если мяч не активен(двигается)
	if (ball.active) {
		ball.move();
		// проверяем столкновение мяча с каждым блоком
		for (int i(0); i < 10; i++) {
			for (int j(0); j < 15; j++) {
				Brick &b = brick[i][j];
				if (isCollision(ball, b)) {
					//изменения скоростей при соударении
					if (abs(ball.x - b.col*b.w - b.w / 2) < abs(ball.y - b.raw*b.h - b.h / 2)) // находится ли чмяч сверху или снизу
					{
						ball.dy *= -1;
					}else if (abs(ball.x - b.col*b.w - b.w / 2) > abs(ball.y - b.raw*b.h - b.h / 2))// находится ли чмяч справа или слева
					{
						ball.dx *= -1;
					}
					else // если мяч соударяется с диагональю блока
					{
						if (ball.dx > 0) {
							if (ball.x < b.col*b.w + 1) {
								ball.dx *= -1;
							}							
						}else if (ball.x >(b.col + 1)*b.w - 1) {
							ball.dx *= -1;
						}
						if (ball.dy > 0) {
							if (ball.y < b.raw*b.h + 1) {
								ball.dy *= -1;
							}
						}
						else if (ball.y >(b.raw + 1)*b.h - 1) {
							ball.dy *= -1;
						}

					}

					if (--b.hit == 0) {
						b.active = false;
					}
					goto o; // ЕСЛИ МЯЧ СТОЛКНУЛСЯ С МЯЧОМ ТО ВЫХОДИМ ИЗ ДВОЙНОГО ЦИКЛА goto(line 106)
				}				
			}
		}
		std::cout << "X " << ball.x << "  Y  " << ball.y << std::endl;
	}
o:	Draw(); // goto(line 100)
		
	
	//glutPostRedisplay(); //обновление всего экрана. того что нарисовали
	glutTimerFunc(33, Timer, 0); //обновления функции инициализации(функции таймера):типа рекурсия
}

void MouseMove(int ax, int ay) //движение мыши без нажатия кнопок
{
	//координаты ракетки
	r_x = ax - r_w / 2;
	//координаты мяча
	if (!ball.active) //если мяч на ракетке(не активен)
	{
		ball.x = r_x + r_w / 2;
		ball.y = r_y - ball.r;
	}


	//std::cout << "ax " << ax << "  ay  " << ay << std::endl;
}

void MousePressed(int button, int state, int ax, int ay) //событие на клик
{
	if (button == GLUT_LEFT_BUTTON && !ball.active) // если нажали мышку и мяч не активен
	{
		ball.active = true;
		//задаём скорости мячу
		ball.dx = 7;
		ball.dy = 4;
	}


	//std::cout << "ax " << ax << "  ay  " << ay << std::endl;
}

bool  isCollision(Ball &b, Brick &br) // функция проверки столкновения мяча с кирпичом
{


	float	x = b.x, y = b.y, r = b.r, // координаты и радиус мяча
			c = br.col, raw = br.raw, // номер столбца, номер строки | кирпич
			w = br.w, h = br.h; // ширина и высота кирпича
	// находится ли мячик и блок вблизи (границы мяча квадратные)
	if (br.active) // если блок активен
	{
		if (abs(x - c*w - w / 2 - 2) <= r + w / 2 && abs(y - raw*h - h / 2 - 2) <= r + h / 2) 
		{
			//уточняем угловые столкновения
			if (sqrt((c*w + w / 2 - x)*(c*w + w / 2 - x) + (raw*h + h / 2 - y)*(raw*h + h / 2 - y)) -
				(w / 2 - 1)*sqrt(2.0) - r > r*(sqrt(2.0) - 1)) {
				return 0;
			}
			else {
				return 1;
			}
		}
	}

	return 0;
}