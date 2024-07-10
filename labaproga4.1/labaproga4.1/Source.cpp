/********************************************************************
*               Информатика и вычислительная техника                *
*-------------------------------------------------------------------*
* Project Type : Win32 Console Application                          *
* Project Name : labaproga4.1                                       *
* File Name : Source.cpp                                            *
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
#include <windows.h>//для работы с окнами и графикой в Windows
#include "Header.h"

//глобальная переменная контекста устройства для рисования
extern HDC hdc;

//макрос для проверки нажатия клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)


//конструктор класса Location
Location::Location(int InitX, int InitY)
{
    //инициализация координат
    X = InitX;
    Y = InitY;
}//Location

//деструктор класса Location
Location::~Location(void)
{
}//~Location

//получить координату X
int Location::GetX(void)
{
    return X;
}//GetX()

//получить координату Y
int Location::GetY(void)
{
    return Y;
}//GetY()

//конструктор класса Point
Point::Point(int InitX, int InitY) : Location(InitX, InitY)
{
    //изначально точка скрыта
    Visible = false;
} //Point()

//деструктор класса Point
Point::~Point(void)
{
} //~Point()

//показать точку
void Point::Show(void)
{
    Visible = true;
    //рисуем красную точку
    //SetPixel(hdc, X, Y, RGB(255, 0, 0));
    //
    Ellipse(hdc, X - 10, Y - 10, X + 10, Y + 10);

}//Show()

//скрыть точку
void Point::Hide(void)
{
    Visible = false;
    //закрашиваем белым цветом, чтобы скрыть точку
    SetPixel(hdc, X, Y, RGB(255, 255, 255));
}//Hide()

//проверить, видима ли точка
bool Point::IsVisible(void)
{
    return Visible;
}//IsVisible

//переместить точку в новые координаты
void Point::MoveTo(int NewX, int NewY)
{
    Hide(); //скрываем текущую точку
    X = NewX; //обновляем координаты
    Y = NewY;
    Show(); //показываем точку в новом месте
}//MoveTo()
//перемещение точки с заданным шагом при удерживании клавиши
void Point::Drag(int Step)
{
    int FigX, FigY;
    //получаем текущие координаты точки
    FigX = GetX();
    FigY = GetY();

    //бесконечный цикл для перемещения точки
    while (1)
    {
        //проверяем нажатие клавиши Escape для завершения перемещения
        if (KEY_DOWN(VK_ESCAPE))
            break;

        //перемещение влево
        if (KEY_DOWN(VK_LEFT))
        {
            FigX = FigX - Step;
            MoveTo(FigX, FigY);
            Sleep(500);
        }

        //перемещение вправо
        if (KEY_DOWN(VK_RIGHT))
        {
            FigX = FigX + Step;
            MoveTo(FigX, FigY);
            Sleep(500);
        }

        //перемещение вниз
        if (KEY_DOWN(VK_DOWN))
        {
            FigY = FigY + Step;
            MoveTo(FigX, FigY);
            Sleep(500);
        }

        //перемещение вверх
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

// Получить из protected координату Х (право-низ)
int Figure::get_xRB()
{
    return xRightBottom;
}

// Получить из protected координату Y (право-низ)
int Figure::get_yRB()
{
    return yRightBottom;
}

// Получить из protected координату Х (лево-вверх)
int Figure::get_xLUp()
{
    return xLeftUp;
}

// Получить из protected координату Y (лево-вверх)
int Figure::get_yLUp()
{
    return yLeftUp;
}
//конструктор класса Face, инициализирующий параметры лица
Face::Face(int InitX, int InitY, int FR, int ER, int ML, int NL) : Figure(InitX, InitY)
{
    //установка радиуса лица, радиусов глаз, длины носа и длины рта
    FaceRad = FR;
    EyeRad = ER;
    MouthLength = ML;
    NoseLength = NL;
    index = 0;
}//Face()

//деструктор класса Face
Face::~Face()
{
}//~Face()

//функция Show отображает лицо
void Face::Show() {
    Visible = true;//установить флаг видимости лица
    makeHitbox();
    faceshape();
    eyes();
    mouth();
    nose();
}//Show()
//функция Hide прячет лицо
void Face::Hide() {
    Visible = false;//установить флаг видимости лица
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));//создать перо для рисования
    SelectObject(hdc, pen);//выбрать перо
    //нарисовать лицо, глаза, нос и рот
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
//перемещение точки с заданным шагом при удерживании клавиши
void Face::Drag(int Step)
{
    int figX, figY; //новые координаты фигуры

    figX = GetX(); //получаем начальные координаты фигуры
    figY = GetY();
    //выбор направления движения фигуры
    if (KEY_DOWN(VK_LEFT)) //37 стрелка влево
    {
        figX -= Step;
        xLeftUp -= Step;		// Изменение границ фигуры (слева)
        xRightBottom -= Step;	// Изменение границ фигуры (справа)
        MoveTo(figX, figY);
        Sleep(50); //задержка экрана на 500 милисекунд
        return;
    }//if

    if (KEY_DOWN(VK_RIGHT)) //39 стрелка вправо
    {
        figX += Step;
        xRightBottom += Step;				// Изменение границ фигуры (справа)
        xLeftUp += Step;					// Изменение границ фигуры (слева)
        MoveTo(figX, figY);
        Sleep(50); //задержка экрана на 500 милисекунд
        return;
    }//if

    if (KEY_DOWN(VK_DOWN)) //40 стрелка вниз
    {
        figY += Step;
        yRightBottom += Step;		// Изменение границ фигуры (снизу)
        yLeftUp += Step;			// Изменение границ фигуры (сверху)
        MoveTo(figX, figY);
        Sleep(50); //задержка экрана на 500 милисекунд
        return;
    }//if

    if (KEY_DOWN(VK_UP)) //38 стрелка вверх
    {
        figY -= Step;
        yRightBottom -= Step;		// Изменение границ фигуры (снизу)
        yLeftUp -= Step;			// Изменение границ фигуры (сверху)
        MoveTo(figX, figY);
        Sleep(50); //задержка экрана на 500 милисекунд
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
    xRightBottom = X + FaceRad;		// Координата Х (правая)
    yRightBottom = Y + FaceRad;		// Координата Y (нижняя)
    xLeftUp = X - FaceRad;			// Координата Х (левая)
    yLeftUp = Y - FaceRad;			// Координата Y (верхняя)
}

void Face::faceshape()
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//Создать перо для рисования
    SelectObject(hdc, pen);//выбрать перо
    Ellipse(hdc, X - FaceRad, Y - FaceRad, X + FaceRad, Y + FaceRad);
    DeleteObject(pen);
}
void Face::eyes()
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//Создать перо для рисования
    SelectObject(hdc, pen);//выбрать перо
    Ellipse(hdc, X - FaceRad / 2 - EyeRad, Y - FaceRad / 2, X - FaceRad / 2 + EyeRad, Y + EyeRad);
    Ellipse(hdc, X + FaceRad / 2 - EyeRad, Y - FaceRad / 2, X + FaceRad / 2 + EyeRad, Y + EyeRad);
    DeleteObject(pen);
}
void Face::mouth()
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//Создать перо для рисования
    SelectObject(hdc, pen);//выбрать перо
    MoveToEx(hdc, X - MouthLength / 2, Y + FaceRad / 2, NULL);
    LineTo(hdc, X + MouthLength / 2, Y + FaceRad / 2);
    DeleteObject(pen);
}
void Face::nose()
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//Создать перо для рисования
    SelectObject(hdc, pen);//выбрать перо
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
    Visible = false;//установить флаг видимости лица
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));//Создать перо для рисования
    SelectObject(hdc, pen);//выбрать перо
    //нарисовать лицо, глаза, нос и рот
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
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//Создать перо для рисования
    SelectObject(hdc, pen);//выбрать перо
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
    Visible = false;//установить флаг видимости лица
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));//Создать перо для рисования
    SelectObject(hdc, pen);//выбрать перо
    //нарисовать лицо, глаза, нос и рот
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
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//Создать перо для рисования
    SelectObject(hdc, pen);//выбрать перо
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
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//Создать перо для рисования
    SelectObject(hdc, pen);//выбрать перо
    Arc(hdc, X - MouthLength / 2, Y + MouthLength / 4, X + MouthLength / 2, Y + 3 * MouthLength / 4, X + MouthLength / 2, Y + MouthLength / 2, X - MouthLength / 2, Y + MouthLength / 2);
    DeleteObject(pen);
}
void BlackFace::faceshape()
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//Создать перо для рисования
    HBRUSH faceBrush = CreateSolidBrush(RGB(139, 69, 19)); // Коричневый цвет для лица
    SelectObject(hdc, faceBrush); // выбрать кисть для лица
    SelectObject(hdc, pen);//выбрать перо
    Ellipse(hdc, X - FaceRad, Y - FaceRad, X + FaceRad, Y+FaceRad);
    DeleteObject(pen);
    DeleteObject(faceBrush);
}
void BlackFace::eyes()
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));//Создать перо для рисования
    HBRUSH eyeBrush = CreateSolidBrush(RGB(255, 255, 255)); // Белый цвет для глаз
    SelectObject(hdc, eyeBrush); // выбрать кисть для лица
    SelectObject(hdc, pen);//выбрать перо
    Ellipse(hdc, X - FaceRad / 2 - EyeRad, Y - FaceRad / 2, X - FaceRad / 2 + EyeRad, Y + EyeRad);
    Ellipse(hdc, X + FaceRad / 2 - EyeRad, Y - FaceRad / 2, X + FaceRad / 2 + EyeRad, Y + EyeRad);
    DeleteObject(pen);
    DeleteObject(eyeBrush);
}

void BlackFace::Hide()
{
    Visible = false; // установить флаг видимости лица

    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // Создать перо для рисования
    HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255)); // Создать кисть для заполнения внутренней части лица

    SelectObject(hdc, pen); // выбрать перо
    SelectObject(hdc, brush); // выбрать кисть

    // нарисовать лицо
    Ellipse(hdc, X - FaceRad, Y - FaceRad, X + FaceRad, Y + FaceRad);

    // нарисовать глаза
    Ellipse(hdc, X - FaceRad / 2 - EyeRad, Y - FaceRad / 2, X - FaceRad / 2 + EyeRad, Y + EyeRad);
    Ellipse(hdc, X + FaceRad / 2 - EyeRad, Y - FaceRad / 2, X + FaceRad / 2 + EyeRad, Y + EyeRad);

    // нарисовать нос
    MoveToEx(hdc, X, Y - NoseLength / 2, NULL);
    LineTo(hdc, X - FaceRad / 4, Y + NoseLength / 2);
    LineTo(hdc, X + FaceRad / 4, Y + NoseLength / 2);
    LineTo(hdc, X, Y - NoseLength / 2);

    // нарисовать рот
    Arc(hdc, X - MouthLength / 2, Y + MouthLength / 4, X + MouthLength / 2, Y + 3 * MouthLength / 4, X + MouthLength / 2, Y + MouthLength / 2, X - MouthLength / 2, Y + MouthLength / 2);

}
Object::Object(int InitX, int InitY) :Figure(InitX, InitY) {

}
Object::~Object() {

}

//конструктор
Stone::Stone(int InitX, int InitY, int r) :Object(InitX, InitY) {
    radius = r;
    index = 0;
}//Stone::Stone()

//деструктор
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

//конструктор
Cactus::Cactus(int InitX, int InitY, int w, int h) :Object(InitX, InitY) {
    width = w;
    height = h;
    index = 1;

    //расчет крайних координат
}

//деструктор
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

    // Рисуем стебель
    Rectangle(hdc, X + width / 3, Y, X + 2 * width / 3, Y + height);

    // Рисуем верхушку кактуса
    Ellipse(hdc, X, Y - height / 2, X + width, Y);

    DeleteObject(Brush);
}

//конструктор
Pond::Pond(int InitX, int InitY, int r) :Object(InitX, InitY) {
    radius = r;
    index = 2;
}

//деструктор
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
    Ellipse(hdc, X - radius, Y - radius / 2, X + radius, Y + radius / 2); //лужа

    DeleteObject(Brush);
}
//конструктор
Bottle::Bottle(int InitX, int InitY, int w, int h) :Object(InitX, InitY) {
    width = w;
    height = h;
    int neckHeight = h / 5;
    index = 3;



}

//деструктор
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
    // Отрисовка верхней части бутылки (горлышка)
    Rectangle(hdc, X + width / 3, Y - neckHeight, X + width * 2 / 3, Y);

    // Уничтожим нами созданные объекты  
    DeleteObject(Brush);
}
bool Collision(Figure& obj1, Figure& obj2)
{
    // Определение столкновения слева
    bool left = obj2.get_xLUp() <= obj1.get_xRB() && obj2.get_xRB() >= obj1.get_xRB()
        && (obj2.get_yLUp() <= obj1.get_yRB() && obj2.get_yLUp() >= obj1.get_yLUp()
            || obj2.get_yRB() >= obj1.get_yLUp() && obj2.get_yRB() <= obj1.get_yRB());
    // Определение столкновений справа
    bool right = obj2.get_xRB() >= obj1.get_xLUp() && obj2.get_xLUp() <= obj1.get_xLUp()
        && (obj2.get_yLUp() <= obj1.get_yRB() && obj2.get_yLUp() >= obj1.get_yLUp()
            || obj2.get_yRB() >= obj1.get_yLUp() && obj2.get_yRB() <= obj1.get_yRB());
    // Определение столкновений сверху
    bool top = obj2.get_yLUp() <= obj1.get_yLUp() && obj2.get_yRB() >= obj1.get_yLUp()
        && (obj2.get_xLUp() <= obj1.get_xRB() && obj2.get_xLUp() >= obj1.get_xLUp()
            || obj2.get_xLUp() >= obj1.get_xLUp() && obj2.get_xRB() <= obj1.get_xRB());
    // Определение столкновений снизу
    bool bottom = obj2.get_yRB() >= obj1.get_yRB() && obj2.get_yLUp() <= obj1.get_yRB()
        && (obj2.get_xLUp() <= obj1.get_xRB() && obj2.get_xLUp() >= obj1.get_xLUp()
            || obj2.get_xRB() >= obj1.get_xLUp() && obj2.get_xRB() <= obj1.get_xRB());
    // Определение того, находится ли препятствие "внутри" фигуры
    bool inside = obj2.get_xLUp() >= obj1.get_xLUp() && obj2.get_yLUp() >= obj1.get_yLUp() &&
        obj2.get_xRB() <= obj1.get_xRB() && obj2.get_yRB() <= obj1.get_yRB();
    // Если хоть одно условие выполняется, то столкновение есть
    return left || right || top || bottom || inside;
}