#include "shape.h"

void Shape::Set(long x1, long y1, long x2, long y2)
{
    xs1 = x1;
    ys1 = y1;
    xs2 = x2;
    ys2 = y2;
}

void PointShape::Show(HDC hdc)
{
    SetPixel(hdc, xs1, ys1, RGB(0, 0, 0)); // чорний колір для точки
}

void LineShape::Show(HDC hdc)
{
    MoveToEx(hdc, xs1, ys1, NULL);
    LineTo(hdc, xs2, ys2);
}

void RectShape::Show(HDC hdc)
{
    Rectangle(hdc, xs1, ys1, xs2, ys2);
}

void EllipseShape::Show(HDC hdc)
{
    Ellipse(hdc, xs1, ys1, xs2, ys2);
}

void LineOOShape::Show(HDC hdc)
{
    const int x3 = xs1;
    const int x4 = xs2;
    const int y3 = ys1;
    const int y4 = ys2;

    EllipseShape::Set(x4, y4 - 25, x4, y4+25);
    EllipseShape::Show(hdc);

    LineShape::Set(x3, y3, x4, y4);
    LineShape::Show(hdc);

    EllipseShape::Set(x3 - 2*((x4-x3)/10), y3 - 2*((x4 - x3) / 10), x3, y3 + 2* ((x4 - x3) / 10));
    EllipseShape::Show(hdc);

}

void CubeShape::Show(HDC hdc)
{

    RectShape::Set(xs1, ys1, xs2, ys2);
    RectShape::Show(hdc);

    const int x3 = xs1;
    const int x4 = xs2;
    const int y3 = ys1;
    const int y4 = ys2;

    LineShape::Set(xs1 - (20 * ((xs2 - xs1) / 50.00)), ys2 - (20 * ((xs2 - xs1) / 50.00)), xs2 - (20 * ((xs2 - xs1) / 50.00)), ys2 - (20 * ((xs2 - xs1) / 50.00)));
    LineShape::Show(hdc);

    LineShape::Set(x4 - (20 * ((x4 - x3) / 50.00)), y4 - (20 * ((xs2 - xs1) / 50.00)), x4 - (20 * ((x4 - x3) / 50.00)), y4 + (20 * ((xs2 - xs1) / 50.00)));
    LineShape::Show(hdc);

    LineShape::Set(x3 - (20 * ((x4 - x3) / 50.00)), y4 + (20 * ((x4 - x3) / 50.00)), x4 - (20 * ((x4 - x3) / 50.00)), y4 + (20 * ((x4 - x3) / 50.00)));
    LineShape::Show(hdc);

    LineShape::Set(x3 - (20 * ((x4 - x3) / 50.00)), y4 - (20 * ((xs2 - xs1) / 50.00)), x3 - (20 * ((x4 - x3) / 50.00)), y4 + (20 * ((xs2 - xs1) / 50.00)));
    LineShape::Show(hdc);

    LineShape::Set(x3, y3, x3 - (20 * ((x4 - x3) / 50.00)), y4- (20 * ((x4 - x3) / 50.00)));
    LineShape::Show(hdc);

    LineShape::Set(x4, y3, x4 - (20 * ((x4 - x3) / 50.00)), y4 - (20 * ((x4 - x3) / 50.00)));
    LineShape::Show(hdc);

    LineShape::Set(x3, y4, x3 - (20 * ((x4 - x3) / 50.00)), y4 + (20 * ((x4 - x3) / 50.00)));
    LineShape::Show(hdc);

    LineShape::Set(x4, y4, x4 - (20 * ((x4 - x3) / 50.00)), y4 + (20 * ((x4 - x3) / 50.00)));
    LineShape::Show(hdc);
}