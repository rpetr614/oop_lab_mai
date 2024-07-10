
/********************************************************************
*               Информатика и вычислительная техника                *
*-------------------------------------------------------------------*
* Project Type : Win32 Console Application                          *
* Project Name : labaproga4.1                                       *
* File Name : labaproga4.1.cpp                                      *
* Language : C/C++                                                  *
* Programmer(s) : М3О-209Б-22                                       *
*                 Романов П.А                                       *
* Modifyed By :                                                     *
* Created : 10.04.2024                                              *
* Comment(s) : ПЕРВАЯ ПРОГРАММА                                     *
*                                                                   *
*                                                                   *
*********************************************************************/
//подключение библиотек
#include <windows.h>
#include <iostream>    
using namespace std;
#include "Header.h" 
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)//определение клавиши
HDC hdc;
//main



int main()
{
	setlocale(LC_ALL, "ru");  //подключение русского языка
	hdc = GetDC(GetConsoleWindow());

	//матрица перехода (по строкам конфликтные объекты, по столбцам лица)
	int matr_per[ARR_SIZE][ARR_SIZE] = {
	{3, 0, 1, 3 },
	{3, 1, 0, 2},
	{1, 2, 0, 3},
	{0, 2, 2, 1} };

	Face AFace(500, 500, 87, 25, 75, 25);
	SadFace BFace(500, 500, 87, 25, 75, 25);
	SmileFace CFace(500, 500, 87, 25, 75, 25);
	BlackFace DFace(500, 500, 87, 25, 75, 25);

	Face* CurFace;
	CurFace = &AFace;

	Face* faces[ARR_SIZE] = { &AFace, &CFace, &DFace, &BFace };
	Stone AStone(200, 900, 50);
	Cactus ACactus(1700, 300, 60, 120);
	Pond APond(1300, 1000, 100);
	Bottle ABottle(50, 180, 80, 200);



	CurFace->Show(); //показать лицо изначально
	Figure* objects[ARR_SIZE] = { &AStone, &ACactus, &APond, &ABottle };

	for (int i = 0; i < ARR_SIZE; i++) objects[i]->Show();

	while (true)
	{
		CurFace->Drag(20);
		for (int i = 0; i < ARR_SIZE; i++)
		{
			if (Collision(*CurFace, *objects[i]))
			{
				CurFace->MoveTo(500, 500);	// переход в начальную точку  
				CurFace->Hide();
				CurFace = faces[matr_per[objects[i]->getIndex()][CurFace->getIndex()]];
				CurFace->Show();
				for (int i = 0; i < ARR_SIZE; i++) objects[i]->Show();
				break;
			}//if
		}
	}//while

}