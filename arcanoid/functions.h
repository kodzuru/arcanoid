#pragma once
#include "vars.h"

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
	glColor3f(0.1, 0.2, 0.8);
	glBegin(GL_QUADS); {
		for (int i(0); i < 10; i++) {
			for (int j(0); j < 15; j++) {
				Brick &b = brick[i][j];
				if (b.active) {
					glVertex2f(b.col*b.w + 1, b.raw*b.h + 1);
					glVertex2f(b.col*b.w + b.w - 1, b.raw*b.h + 1);
					glVertex2f(b.col*b.w + b.w - 1, b.raw*b.h + b.h - 1);
					glVertex2f(b.col*b.w + 2, b.raw*b.h + b.h - 1);
				}
			}
		}


	}glEnd();









	glutSwapBuffers(); //при использовании двойного буфера GLUT_DOUBLE
}

void Timer(int value)
{
	Draw();
	//если мяч не активен(двигается)
	if (ball.active) {
		ball.move();
		std::cout << "X " << ball.x << "  Y  " << ball.y << std::endl;
	}
		
	
	//glutPostRedisplay(); //обновление всего экрана. того что нарисовали
	glutTimerFunc(33, Timer, 0); //обновления функции инициализации(функции таймера):типа рекурсия
}

void MouseMove(int ax, int ay) //движение мыши без нажатия кнопок
{
	//координаты ракетки
	mouse_x = ax;
	r_x = mouse_x - r_w / 2;
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
		ball.dx = 4;
		ball.dy = 4;
	}


	//std::cout << "ax " << ax << "  ay  " << ay << std::endl;
}