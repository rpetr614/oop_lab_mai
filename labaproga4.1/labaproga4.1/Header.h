#pragma once
/********************************************************************
*               Информатика и вычислительная техника                *
*-------------------------------------------------------------------*
* Project Type : Win32 Console Application                          *
* Project Name : labaproga4.1                                       *
* File Name : Header.h                                              *
* Language : C/C++                                                  *
* Programmer(s) : М3О-209Б-22                                       *
*                 Романов П.А                                       *
* Modifyed By :                                                     *
* Created : 10.04.2024                                              *
* Comment(s) : ПЕРВАЯ ПРОГРАММА                                     *
*                                                                   *
*                                                                   *
*********************************************************************/
#define ARR_SIZE 4
//Location
class Location
{
protected:
	int X;//координата X
	int Y;//координата Y
public:
	Location(int InitX, int InitY);//конструктор
	~Location();//деструктор
	int GetX();//получить координату X
	int GetY();//получить координату Y
};//Location

//Point
class Point : public Location
{
protected:
	bool Visible;//светимость точки

public:
	Point(int InitX, int InitY);//конструктор
	~Point();//деструктор
	bool IsVisible();//узнать про светимость точки
	void MoveTo(int NewX, int NewY);//переместить фигуру на новые координаты
	void Drag(int Step);//переместить фигуру с помощью стрелок
	virtual void Show();//показать фигуру
	virtual void Hide();//скрыть фигуру
};//Point
class Figure : public Point//АБК фигура
{
protected:
	int index;						// индекс
	int xRightBottom;				// координата Х (право-низ)
	int yRightBottom;				// координата Y (право-низ)
	int xLeftUp;					// координата Х (лево-верх)
	int yLeftUp;					// координата Y (лево-верх)
public:
	Figure(int InitX, int InitY);
	~Figure();
	int get_xRB();					// Получить из protected координату Х (право-низ)
	int get_yRB();					// Получить из protected координату Y (право-низ)
	int get_xLUp();					// Получить из protected координату Х (лево-вверх)	
	int get_yLUp();					// Получить из protected координату Y (лево-вверх)
	int getIndex();					// Получить из protected индекс
	virtual void makeHitbox() = 0;  // Создать границы для взаимодействия с другими объектами
};
class IFace//интерфейс лицо
{
public:
	virtual void faceshape() = 0;
	virtual void eyes() = 0;
	virtual void mouth() = 0;
	virtual void nose() = 0;
};
//Face
class Face : public Figure, IFace
{
protected:
	int FaceRad;//радиус лица
	int EyeRad;//радиус глаза
	int MouthLength;//длина рта
	int NoseLength;//длина носа

public:
	Face(int InitX, int InitY, int FR, int ER, int ML, int NL);//конструктор
	~Face();//деструктор
	virtual void faceshape();
	virtual void eyes();
	virtual void mouth();
	virtual void nose();
	void Drag(int Step);//переместить фигуру с помощью стрелок
	virtual void Show();//показать фигуру
	virtual void Hide();//скрыть фигуру
	int getFaceRad();
	int getEyesRad();
	int getMouthLength();
	int getNoseLength();
	virtual void makeHitbox();
};
class SadFace : public Face
{
private:

public:
	SadFace(int InitX, int InitY, int FR, int ER, int ML, int NL);//конструктор 
	~SadFace();//деструктор
	virtual void Hide();//скрыть фигуру
	virtual void mouth();
};
class SmileFace : public Face
{
private:

public:
	SmileFace(int InitX, int InitY, int FR, int ER, int ML, int NL);//конструктор
	~SmileFace();//деструктор
	virtual void Hide();//скрыть фигуру
	virtual void mouth();
};
class BlackFace : public Face
{
private:

public:
	BlackFace(int InitX, int InitY, int FR, int ER, int ML, int NL);//конструктор
	~BlackFace();//деструктор
	virtual void Hide();//скрыть фигуру
	virtual void mouth();
	virtual void faceshape();
	virtual void eyes();
};


class Object : public Figure
{
protected:

public:
	Object(int InitX, int InitY);
	~Object();
};

class Cactus : public Object {
protected:
	int width;//ширина
	int height;//высота
public:
	Cactus(int InitX, int InitY, int w, int h); //конструктор
	~Cactus(); //деструктор
	virtual void makeHitbox();
	virtual void Show();
};//class Cactus

class Stone : public Object {
protected:
	int radius; //радиус камня
public:
	Stone(int InitX, int InitY, int r); //конструктор
	~Stone(); //деструктор
	virtual void makeHitbox();
	virtual void Show();
};//class Stone
class Pond : public Object {
protected:
	int radius; //радиус
public:
	Pond(int InitX, int InitY, int r); //конструктор
	~Pond(); //деструктор
	virtual void makeHitbox();
	virtual void Show();
};//class Pond
class Bottle : public Object {
protected:
	int width; //ширина
	int height;//высота
public:
	Bottle(int InitX, int InitY, int w, int h); //конструктор
	~Bottle(); //деструктор
	virtual void makeHitbox();
	virtual void Show();
};//class Bottle
bool Collision(Figure& obj1, Figure& obj2);