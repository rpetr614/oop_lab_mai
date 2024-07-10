/********************************************************************
*               ����������� � �������������� �������                *
*-------------------------------------------------------------------*
* Project Type : Win32 Console Application                          *
* Project Name : labaproga4.1                                       *
* File Name : Source.cpp                                            *
* Language : C/C++                                                  *
* Programmer(s) : �3�-209�-22                                       *
*                 ������� �.�                                       *
* Modifyed By :                                                     *
* Created : 10.04.2024                                              *
* Comment(s) : ������ ���������                                     *
*                                                                   *
*                                                                   *
*********************************************************************/
//����������� ���������
#include <windows.h>//��� ������ � ������ � �������� � Windows
#include "Header.h"

//���������� ���������� ��������� ���������� ��� ���������
extern HDC hdc;

//������ ��� �������� ������� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)


//����������� ������ Location
Location::Location(int InitX, int InitY)
{
    //������������� ���������
    X = InitX;
    Y = InitY;
}//Location

//���������� ������ Location
Location::~Location(void)
{
}//~Location

//�������� ���������� X
int Location::GetX(void)
{
    return X;
}//GetX()

//�������� ���������� Y
int Location::GetY(void)
{
    return Y;
}//GetY()

//����������� ������ Point
Point::Point(int InitX, int InitY) : Location(InitX, InitY)
{
    //���������� ����� ������
    Visible = false;
} //Point()

//���������� ������ Point
Point::~Point(void)
{
} //~Point()

//�������� �����
void Point::Show(void)
{
    Visible = true;
    //������ ������� �����
    //SetPixel(hdc, X, Y, RGB(255, 0, 0));
    //
    Ellipse(hdc, X - 10, Y - 10, X + 10, Y + 10);

}//Show()

//������ �����
void Point::Hide(void)
{
    Visible = false;
    //����������� ����� ������, ����� ������ �����
    SetPixel(hdc, X, Y, RGB(255, 255, 255));
}//Hide()

//���������, ������ �� �����
bool Point::IsVisible(void)
{
    return Visible;
}//IsVisible

//����������� ����� � ����� ����������
void Point::MoveTo(int NewX, int NewY)
{
    Hide(); //�������� ������� �����
    X = NewX; //��������� ����������
    Y = NewY;
    Show(); //���������� ����� � ����� �����
}//MoveTo()
//����������� ����� � �������� ����� ��� ����������� �������
void Point::Drag(int Step)
{
    int FigX, FigY;
    //�������� ������� ���������� �����
    FigX = GetX();
    FigY = GetY();

    //����������� ���� ��� ����������� �����
    while (1)
    {
        //��������� ������� ������� Escape ��� ���������� �����������
        if (KEY_DOWN(VK_ESCAPE))
            break;

        //����������� �����
        if (KEY_DOWN(VK_LEFT))
        {
            FigX = FigX - Step;
            MoveTo(FigX, FigY);
            Sleep(500);
        }

        //����������� ������
        if (KEY_DOWN(VK_RIGHT))
        {
            FigX = FigX + Step;
            MoveTo(FigX, FigY);
            Sleep(500);
        }

        //����������� ����
        if (KEY_DOWN(VK_DOWN))
        {
            FigY = FigY + Step;
            MoveTo(FigX, FigY);
            Sleep(500);
        }

        //����������� �����
        if (KEY_DOWN(VK_UP))
        {
            FigY = FigY - Step;
            MoveTo(FigX, FigY);
            Sleep(500);
        }
    }

}//Drag()
Figure::Figure(int InitX, int InitY) : Point(InitX, InitY)
{
}

Figure::~Figure() {
}

int Figure::getIndex() {
    return index;
}

// �������� �� protected ���������� � (�����-���)
int Figure::get_xRB()
{
    return xRightBottom;
}

// �������� �� protected ���������� Y (�����-���)
int Figure::get_yRB()
{
    return yRightBottom;
}

// �������� �� protected ���������� � (����-�����)
int Figure::get_xLUp()
{
    return xLeftUp;
}

// �������� �� protected ���������� Y (����-�����)
int Figure::get_yLUp()
{
    return yLeftUp;
}
//����������� ������ Face, ���������������� ��������� ����
Face::Face(int InitX, int InitY, int FR, int ER, int ML, int NL) : Figure(InitX, InitY)
{
    //��������� ������� ����, �������� ����, ����� ���� � ����� ���
    FaceRad = FR;
    EyeRad = ER;
    MouthLength = ML;
    NoseLength = NL;
    index = 0;
}//Face()

//���������� ������ Face
Face::~Face()
{
}//~Face()

//������� Show ���������� ����
void Face::Show() {
    Visible = true;//���������� ���� ��������� ����
    makeHitbox();
    faceshape();
    eyes();
    mouth();
    nose();
}//Show()
//������� Hide ������ ����
void Face::Hide() {
    Visible = false;//���������� ���� ��������� ����
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));//������� ���� ��� ���������
    SelectObject(hdc, pen);//������� ����
    //���������� ����, �����, ��� � ���
    Ellipse(hdc, X - FaceRad, Y - FaceRad, X + FaceRad, Y + FaceRad);
    Ellipse(hdc, X - FaceRad / 2 - EyeRad, Y - FaceRad / 2, X - FaceRad / 2 + EyeRad, Y + EyeRad);
    Ellipse(hdc, X + FaceRad / 2 - EyeRad, Y - FaceRad / 2, X + FaceRad / 2 + EyeRad, Y + EyeRad);
    MoveToEx(hdc, X, Y - NoseLength / 2, NULL);
    LineTo(hdc, X - FaceRad / 4, Y + NoseLength / 2);
    LineTo(hdc, X + FaceRad / 4, Y + NoseLength / 2);
    LineTo(hdc, X, Y - NoseLength / 2);
    MoveToEx(hdc, X - MouthLength / 2, Y + FaceRad / 2, NULL);
    LineTo(hdc, X + MouthLength / 2, Y + FaceRad / 2);
}//Hide()
//����������� ����� � �������� ����� ��� ����������� �������
void Face::Drag(int Step)
{
    int figX, figY; //����� ���������� ������

    figX = GetX(); //�������� ��������� ���������� ������
    figY = GetY();
    //����� ����������� �������� ������
    if (KEY_DOWN(VK_LEFT)) //37 ������� �����
    {
        figX -= Step;
        xLeftUp -= Step;		// ��������� ������ ������ (�����)
        xRightBottom -= Step;	// ��������� ������ ������ (������)
        MoveTo(figX, figY);
        Sleep(50); //�������� ������ �� 500 ����������
        return;
    }//if

    if (KEY_DOWN(VK_RIGHT)) //39 ������� ������
    {
        figX += Step;
        xRightBottom += Step;				// ��������� ������ ������ (������)
        xLeftUp += Step;					// ��������� ������ ������ (�����)
        MoveTo(figX, figY);
        Sleep(50); //�������� ������ �� 500 ����������
        return;
    }//if

    if (KEY_DOWN(VK_DOWN)) //40 ������� ����
    {
        figY += Step;
        yRightBottom += Step;		// ��������� ������ ������ (�����)
        yLeftUp += Step;			// ��������� ������ ������ (������)
        MoveTo(figX, figY);
        Sleep(50); //�������� ������ �� 500 ����������
        return;
    }//if

    if (KEY_DOWN(VK_UP)) //38 ������� �����
    {
        figY -= Step;
        yRightBottom -= Step;		// ��������� ������ ������ (�����)
        yLeftUp -= Step;			// ��������� ������ ������ (������)
        MoveTo(figX, figY);
        Sleep(50); //�������� ������ �� 500 ����������
        return;
    }//if
}//Face::Drag()
int Face::getFaceRad() {
    return FaceRad;
}

int Face::getEyesRad() {
    return EyeRad;
}

int Face::getMouthLength() {
    return MouthLength;
}

int Face::getNoseLength() {
    return NoseLength;
}

void Face::makeHitbox() {
    xRightBottom = X + FaceRad;		// ���������� � (������)
    yRightBottom = Y + FaceRad;		// ���������� Y (������)
    xLeftUp = X - FaceRad;			// ���������� � (�����)
    yLeftUp = Y - FaceRad;			// ���������� Y (�������)
}

void Face::faceshape()
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//������� ���� ��� ���������
    SelectObject(hdc, pen);//������� ����
    Ellipse(hdc, X - FaceRad, Y - FaceRad, X + FaceRad, Y + FaceRad);
    DeleteObject(pen);
}
void Face::eyes()
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//������� ���� ��� ���������
    SelectObject(hdc, pen);//������� ����
    Ellipse(hdc, X - FaceRad / 2 - EyeRad, Y - FaceRad / 2, X - FaceRad / 2 + EyeRad, Y + EyeRad);
    Ellipse(hdc, X + FaceRad / 2 - EyeRad, Y - FaceRad / 2, X + FaceRad / 2 + EyeRad, Y + EyeRad);
    DeleteObject(pen);
}
void Face::mouth()
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//������� ���� ��� ���������
    SelectObject(hdc, pen);//������� ����
    MoveToEx(hdc, X - MouthLength / 2, Y + FaceRad / 2, NULL);
    LineTo(hdc, X + MouthLength / 2, Y + FaceRad / 2);
    DeleteObject(pen);
}
void Face::nose()
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//������� ���� ��� ���������
    SelectObject(hdc, pen);//������� ����
    MoveToEx(hdc, X, Y - NoseLength / 2, NULL);
    LineTo(hdc, X - FaceRad / 4, Y + NoseLength / 2);
    LineTo(hdc, X + FaceRad / 4, Y + NoseLength / 2);
    LineTo(hdc, X, Y - NoseLength / 2);
    DeleteObject(pen);
}
SadFace::SadFace(int InitX, int InitY, int FR, int ER, int ML, int NL) : Face(InitX, InitY, FR, ER, ML, NL)
{
    index = 3;
}
SadFace::~SadFace() {

}

void SadFace::Hide()
{
    Visible = false;//���������� ���� ��������� ����
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));//������� ���� ��� ���������
    SelectObject(hdc, pen);//������� ����
    //���������� ����, �����, ��� � ���
    Ellipse(hdc, X - FaceRad, Y - FaceRad, X + FaceRad, Y + FaceRad);
    Ellipse(hdc, X - FaceRad / 2 - EyeRad, Y - FaceRad / 2, X - FaceRad / 2 + EyeRad, Y + EyeRad);
    Ellipse(hdc, X + FaceRad / 2 - EyeRad, Y - FaceRad / 2, X + FaceRad / 2 + EyeRad, Y + EyeRad);
    MoveToEx(hdc, X, Y - NoseLength / 2, NULL);
    LineTo(hdc, X - FaceRad / 4, Y + NoseLength / 2);
    LineTo(hdc, X + FaceRad / 4, Y + NoseLength / 2);
    LineTo(hdc, X, Y - NoseLength / 2);
    Arc(hdc, X - MouthLength / 2, Y + MouthLength / 4, X + MouthLength / 2, Y + 3 * MouthLength / 4, X + MouthLength / 2, Y + MouthLength / 2, X - MouthLength / 2, Y + MouthLength / 2);
}
void SadFace::mouth()
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//������� ���� ��� ���������
    SelectObject(hdc, pen);//������� ����
    Arc(hdc, X - MouthLength / 2, Y + MouthLength / 4, X + MouthLength / 2, Y + 3 * MouthLength / 4, X + MouthLength / 2, Y + MouthLength / 2, X - MouthLength / 2, Y + MouthLength / 2);
    DeleteObject(pen);
}


SmileFace::SmileFace(int InitX, int InitY, int FR, int ER, int ML, int NL) : Face(InitX, InitY, FR, ER, ML, NL)
{
    index = 1;
}
SmileFace::~SmileFace() {

}

void SmileFace::Hide()
{
    Visible = false;//���������� ���� ��������� ����
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));//������� ���� ��� ���������
    SelectObject(hdc, pen);//������� ����
    //���������� ����, �����, ��� � ���
    Ellipse(hdc, X - FaceRad, Y - FaceRad, X + FaceRad, Y + FaceRad);
    Ellipse(hdc, X - FaceRad / 2 - EyeRad, Y - FaceRad / 2, X - FaceRad / 2 + EyeRad, Y + EyeRad);
    Ellipse(hdc, X + FaceRad / 2 - EyeRad, Y - FaceRad / 2, X + FaceRad / 2 + EyeRad, Y + EyeRad);
    MoveToEx(hdc, X, Y - NoseLength / 2, NULL);
    LineTo(hdc, X - FaceRad / 4, Y + NoseLength / 2);
    LineTo(hdc, X + FaceRad / 4, Y + NoseLength / 2);
    LineTo(hdc, X, Y - NoseLength / 2);
    Arc(hdc, X - MouthLength / 2, Y + MouthLength / 2, X + MouthLength / 2, Y + MouthLength, X - MouthLength / 2, Y + MouthLength / 2, X + MouthLength / 2, Y + MouthLength / 2);
}
void SmileFace::mouth() {
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//������� ���� ��� ���������
    SelectObject(hdc, pen);//������� ����
    Arc(hdc, X - MouthLength / 2, Y + MouthLength / 2, X + MouthLength / 2, Y + MouthLength, X - MouthLength / 2, Y + MouthLength / 2, X + MouthLength / 2, Y + MouthLength / 2);
    DeleteObject(pen);
}
BlackFace::BlackFace(int InitX, int InitY, int FR, int ER, int ML, int NL) : Face(InitX, InitY, FR, ER, ML, NL)
{
    index = 2;
}
BlackFace::~BlackFace() {

}
void BlackFace::mouth()
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//������� ���� ��� ���������
    SelectObject(hdc, pen);//������� ����
    Arc(hdc, X - MouthLength / 2, Y + MouthLength / 4, X + MouthLength / 2, Y + 3 * MouthLength / 4, X + MouthLength / 2, Y + MouthLength / 2, X - MouthLength / 2, Y + MouthLength / 2);
    DeleteObject(pen);
}
void BlackFace::faceshape()
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//������� ���� ��� ���������
    HBRUSH faceBrush = CreateSolidBrush(RGB(139, 69, 19)); // ���������� ���� ��� ����
    SelectObject(hdc, faceBrush); // ������� ����� ��� ����
    SelectObject(hdc, pen);//������� ����
    Ellipse(hdc, X - FaceRad, Y - FaceRad, X + FaceRad, Y+FaceRad);
    DeleteObject(pen);
    DeleteObject(faceBrush);
}
void BlackFace::eyes()
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//������� ���� ��� ���������
    HBRUSH eyeBrush = CreateSolidBrush(RGB(255, 255, 255)); // ����� ���� ��� ����
    SelectObject(hdc, eyeBrush); // ������� ����� ��� ����
    SelectObject(hdc, pen);//������� ����
    Ellipse(hdc, X - FaceRad / 2 - EyeRad, Y - FaceRad / 2, X - FaceRad / 2 + EyeRad, Y + EyeRad);
    Ellipse(hdc, X + FaceRad / 2 - EyeRad, Y - FaceRad / 2, X + FaceRad / 2 + EyeRad, Y + EyeRad);
    DeleteObject(pen);
    DeleteObject(eyeBrush);
}

void BlackFace::Hide()
{
    Visible = false; // ���������� ���� ��������� ����

    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // ������� ���� ��� ���������
    HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255)); // ������� ����� ��� ���������� ���������� ����� ����

    SelectObject(hdc, pen); // ������� ����
    SelectObject(hdc, brush); // ������� �����

    // ���������� ����
    Ellipse(hdc, X - FaceRad, Y - FaceRad, X + FaceRad, Y + FaceRad);

    // ���������� �����
    Ellipse(hdc, X - FaceRad / 2 - EyeRad, Y - FaceRad / 2, X - FaceRad / 2 + EyeRad, Y + EyeRad);
    Ellipse(hdc, X + FaceRad / 2 - EyeRad, Y - FaceRad / 2, X + FaceRad / 2 + EyeRad, Y + EyeRad);

    // ���������� ���
    MoveToEx(hdc, X, Y - NoseLength / 2, NULL);
    LineTo(hdc, X - FaceRad / 4, Y + NoseLength / 2);
    LineTo(hdc, X + FaceRad / 4, Y + NoseLength / 2);
    LineTo(hdc, X, Y - NoseLength / 2);

    // ���������� ���
    Arc(hdc, X - MouthLength / 2, Y + MouthLength / 4, X + MouthLength / 2, Y + 3 * MouthLength / 4, X + MouthLength / 2, Y + MouthLength / 2, X - MouthLength / 2, Y + MouthLength / 2);

}
Object::Object(int InitX, int InitY) :Figure(InitX, InitY) {

}
Object::~Object() {

}

//�����������
Stone::Stone(int InitX, int InitY, int r) :Object(InitX, InitY) {
    radius = r;
    index = 0;
}//Stone::Stone()

//����������
Stone::~Stone() {
}//Stone::~Stone()
void Stone::makeHitbox()
{
    xRightBottom = X + radius;
    yRightBottom = Y + radius;
    xLeftUp = X - radius;
    yLeftUp = Y - radius;
}
void Stone::Show()
{
    makeHitbox();
    HPEN pen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
    HBRUSH Brush = CreateSolidBrush(RGB(128, 128, 128));
    SelectObject(hdc, Brush);

    Ellipse(hdc, X - radius, Y - radius, X + radius, Y + radius);

    DeleteObject(Brush);
}

//�����������
Cactus::Cactus(int InitX, int InitY, int w, int h) :Object(InitX, InitY) {
    width = w;
    height = h;
    index = 1;

    //������ ������� ���������
}

//����������
Cactus::~Cactus() {
}//Cactus::~Cactus()
void Cactus::makeHitbox()
{
    xLeftUp = X;
    yLeftUp = Y;
    xRightBottom = X + width;
    yRightBottom = Y + 3 * height / 2;
}
void Cactus::Show()
{
    makeHitbox();
    HPEN pen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
    HBRUSH Brush = CreateSolidBrush(RGB(0, 255, 0));
    SelectObject(hdc, Brush);

    // ������ �������
    Rectangle(hdc, X + width / 3, Y, X + 2 * width / 3, Y + height);

    // ������ �������� �������
    Ellipse(hdc, X, Y - height / 2, X + width, Y);

    DeleteObject(Brush);
}

//�����������
Pond::Pond(int InitX, int InitY, int r) :Object(InitX, InitY) {
    radius = r;
    index = 2;
}

//����������
Pond::~Pond() {
}//Pond::~Pond()
void Pond::makeHitbox()
{
    xLeftUp = X - radius;
    yLeftUp = Y - radius;
    xRightBottom = X + radius;
    yRightBottom = Y + radius;
}
void Pond::Show() {
    makeHitbox();
    HPEN pen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
    HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 255));
    SelectObject(hdc, Brush);

    //Ellipse(hdc, X - 400, Y - 90, X + 350, Y - 20);
    Ellipse(hdc, X - radius, Y - radius / 2, X + radius, Y + radius / 2); //����

    DeleteObject(Brush);
}
//�����������
Bottle::Bottle(int InitX, int InitY, int w, int h) :Object(InitX, InitY) {
    width = w;
    height = h;
    int neckHeight = h / 5;
    index = 3;



}

//����������
Bottle::~Bottle() {
}//Bottle::~Bottle()
void Bottle::makeHitbox()
{
    int neckHeight = height / 5;
    xLeftUp = X - 5;
    yLeftUp = Y - 5;
    xRightBottom = X + width + 5;
    yRightBottom = Y + height + neckHeight + 10;
}
void Bottle::Show()
{
    makeHitbox();
    HPEN pen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
    int neckHeight = height / 5;
    HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, Brush);
    Rectangle(hdc, X, Y, X + width, Y + height);
    // ��������� ������� ����� ������� (��������)
    Rectangle(hdc, X + width / 3, Y - neckHeight, X + width * 2 / 3, Y);

    // ��������� ���� ��������� �������  
    DeleteObject(Brush);
}
bool Collision(Figure& obj1, Figure& obj2)
{
    // ����������� ������������ �����
    bool left = obj2.get_xLUp() <= obj1.get_xRB() && obj2.get_xRB() >= obj1.get_xRB()
        && (obj2.get_yLUp() <= obj1.get_yRB() && obj2.get_yLUp() >= obj1.get_yLUp()
            || obj2.get_yRB() >= obj1.get_yLUp() && obj2.get_yRB() <= obj1.get_yRB());
    // ����������� ������������ ������
    bool right = obj2.get_xRB() >= obj1.get_xLUp() && obj2.get_xLUp() <= obj1.get_xLUp()
        && (obj2.get_yLUp() <= obj1.get_yRB() && obj2.get_yLUp() >= obj1.get_yLUp()
            || obj2.get_yRB() >= obj1.get_yLUp() && obj2.get_yRB() <= obj1.get_yRB());
    // ����������� ������������ ������
    bool top = obj2.get_yLUp() <= obj1.get_yLUp() && obj2.get_yRB() >= obj1.get_yLUp()
        && (obj2.get_xLUp() <= obj1.get_xRB() && obj2.get_xLUp() >= obj1.get_xLUp()
            || obj2.get_xLUp() >= obj1.get_xLUp() && obj2.get_xRB() <= obj1.get_xRB());
    // ����������� ������������ �����
    bool bottom = obj2.get_yRB() >= obj1.get_yRB() && obj2.get_yLUp() <= obj1.get_yRB()
        && (obj2.get_xLUp() <= obj1.get_xRB() && obj2.get_xLUp() >= obj1.get_xLUp()
            || obj2.get_xRB() >= obj1.get_xLUp() && obj2.get_xRB() <= obj1.get_xRB());
    // ����������� ����, ��������� �� ����������� "������" ������
    bool inside = obj2.get_xLUp() >= obj1.get_xLUp() && obj2.get_yLUp() >= obj1.get_yLUp() &&
        obj2.get_xRB() <= obj1.get_xRB() && obj2.get_yRB() <= obj1.get_yRB();
    // ���� ���� ���� ������� �����������, �� ������������ ����
    return left || right || top || bottom || inside;
}