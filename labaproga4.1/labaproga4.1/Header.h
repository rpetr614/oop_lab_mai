#pragma once
/********************************************************************
*               ����������� � �������������� �������                *
*-------------------------------------------------------------------*
* Project Type : Win32 Console Application                          *
* Project Name : labaproga4.1                                       *
* File Name : Header.h                                              *
* Language : C/C++                                                  *
* Programmer(s) : �3�-209�-22                                       *
*                 ������� �.�                                       *
* Modifyed By :                                                     *
* Created : 10.04.2024                                              *
* Comment(s) : ������ ���������                                     *
*                                                                   *
*                                                                   *
*********************************************************************/
#define ARR_SIZE 4
//Location
class Location
{
protected:
	int X;//���������� X
	int Y;//���������� Y
public:
	Location(int InitX, int InitY);//�����������
	~Location();//����������
	int GetX();//�������� ���������� X
	int GetY();//�������� ���������� Y
};//Location

//Point
class Point : public Location
{
protected:
	bool Visible;//���������� �����

public:
	Point(int InitX, int InitY);//�����������
	~Point();//����������
	bool IsVisible();//������ ��� ���������� �����
	void MoveTo(int NewX, int NewY);//����������� ������ �� ����� ����������
	void Drag(int Step);//����������� ������ � ������� �������
	virtual void Show();//�������� ������
	virtual void Hide();//������ ������
};//Point
class Figure : public Point//��� ������
{
protected:
	int index;						// ������
	int xRightBottom;				// ���������� � (�����-���)
	int yRightBottom;				// ���������� Y (�����-���)
	int xLeftUp;					// ���������� � (����-����)
	int yLeftUp;					// ���������� Y (����-����)
public:
	Figure(int InitX, int InitY);
	~Figure();
	int get_xRB();					// �������� �� protected ���������� � (�����-���)
	int get_yRB();					// �������� �� protected ���������� Y (�����-���)
	int get_xLUp();					// �������� �� protected ���������� � (����-�����)	
	int get_yLUp();					// �������� �� protected ���������� Y (����-�����)
	int getIndex();					// �������� �� protected ������
	virtual void makeHitbox() = 0;  // ������� ������� ��� �������������� � ������� ���������
};
class IFace//��������� ����
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
	int FaceRad;//������ ����
	int EyeRad;//������ �����
	int MouthLength;//����� ���
	int NoseLength;//����� ����

public:
	Face(int InitX, int InitY, int FR, int ER, int ML, int NL);//�����������
	~Face();//����������
	virtual void faceshape();
	virtual void eyes();
	virtual void mouth();
	virtual void nose();
	void Drag(int Step);//����������� ������ � ������� �������
	virtual void Show();//�������� ������
	virtual void Hide();//������ ������
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
	SadFace(int InitX, int InitY, int FR, int ER, int ML, int NL);//����������� 
	~SadFace();//����������
	virtual void Hide();//������ ������
	virtual void mouth();
};
class SmileFace : public Face
{
private:

public:
	SmileFace(int InitX, int InitY, int FR, int ER, int ML, int NL);//�����������
	~SmileFace();//����������
	virtual void Hide();//������ ������
	virtual void mouth();
};
class BlackFace : public Face
{
private:

public:
	BlackFace(int InitX, int InitY, int FR, int ER, int ML, int NL);//�����������
	~BlackFace();//����������
	virtual void Hide();//������ ������
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
	int width;//������
	int height;//������
public:
	Cactus(int InitX, int InitY, int w, int h); //�����������
	~Cactus(); //����������
	virtual void makeHitbox();
	virtual void Show();
};//class Cactus

class Stone : public Object {
protected:
	int radius; //������ �����
public:
	Stone(int InitX, int InitY, int r); //�����������
	~Stone(); //����������
	virtual void makeHitbox();
	virtual void Show();
};//class Stone
class Pond : public Object {
protected:
	int radius; //������
public:
	Pond(int InitX, int InitY, int r); //�����������
	~Pond(); //����������
	virtual void makeHitbox();
	virtual void Show();
};//class Pond
class Bottle : public Object {
protected:
	int width; //������
	int height;//������
public:
	Bottle(int InitX, int InitY, int w, int h); //�����������
	~Bottle(); //����������
	virtual void makeHitbox();
	virtual void Show();
};//class Bottle
bool Collision(Figure& obj1, Figure& obj2);