/*
***************** ------ ARCANOID ------ *****************
*/
#define _USE_MATH_DEFINES

#include <glut.h>
#include <iostream>
#include <conio.h>
#include <cmath>

#include "Ball.h" // класс мяча
#include "vars.h";
#include "Brick.h"

Ball ball(r_x + r_w / 2, r_y - r_h, 5); //создаём объект мяч
Brick brick[10][15];
#include "functions.h" // различные функции



float r_x = 50.0, r_y = 290.0, r_w = 80, r_h = 8.0; //координаты и резмеры ракетки
float WinWid = 300.0;
float WinHei = 300.0;




using namespace std;
int main(int argc, char** argv) {

	//инициализация
	glutInit(&argc, argv); // глобальная инициализация
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);// инициализация мода дисплея(как рисуем)
	glutInitWindowSize(WinWid, WinHei); // инициализация размеров дисплея/окна
	glutInitWindowPosition(800, 300); // инициализация позиции окна
	glutCreateWindow("Super <openGL> balalaika"); //создание окна


	//управление мышы
	{
		glutPassiveMotionFunc(MouseMove); //регистрация когда двигается но кнопок не нажато
		glutMouseFunc(MousePressed); //регистрация когда происходит клик
	}
	glutTimerFunc(33, Timer, 0); // регистрация функции анимации(функция таймера)


	//регистрация
	glutDisplayFunc(Draw); //регистрация функции рисования
	Initialize(); //регистрация функции инициализация

	for (int i(0); i < 10; i++) {
		for (int j(0); j < 15; j++) {
			brick[i][j].active = true;
			brick[i][j].col = j;
			brick[i][j].raw = i;
		}
	}



	glutMainLoop(); //запуск главного цикла(стандартная функция GLUT)

	_getch();
	return 1;
}