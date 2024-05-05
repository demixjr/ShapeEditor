#include "My_Editor.h"
#include "Shape.h"
#include "framework.h"
#include <typeinfo> 
#include "Lab_4.h"
#include "resource.h"
Shape* p = {nullptr};

BOOL press = false;
extern HDC hdc;

void MyEditor::Start(Shape*shape)
{
    p = shape;
}

void MyEditor::OnLBdown(HWND hWnd) {
        POINT pt;
        HDC hdc;
        hdc = GetDC(hWnd);
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);
        xstart = xend = pt.x;
        ystart = yend = pt.y;
        press = true; 
}

void MyEditor::OnMouseMove(HWND hWnd)
{
    if (press)
    {
        POINT pt;
        HPEN hPenOld, hPen;
        HDC hdc;
        hdc = GetDC(hWnd); //отримуємо контекст вікна для малювання
        SetROP2(hdc, R2_NOTXORPEN);
        hPen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
        hPenOld = (HPEN)SelectObject(hdc, hPen);

        p->Set(xstart, ystart, xend, yend);
        p->Show(hdc);
        
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);
        xend = pt.x; //координати поточної точки курсору
        yend = pt.y;

        p->Set(xstart, ystart, xend, yend);
        p->Show(hdc);
        
        SelectObject(hdc, hPenOld);
        DeleteObject(hPen);
        ReleaseDC(hWnd, hdc);
    }
}

void MyEditor::OnLBup(HWND hWnd) {
    press = false;
    p->Set(xstart, ystart, xend, yend);
    HPEN hPenOld, hPen;
    HBRUSH hBrush, hBrushOld;

    HDC hdc = GetDC(hWnd);

    hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    hPenOld = (HPEN)SelectObject(hdc, hPen);
    if (typeid(*p) == typeid(RectShape)) {
        hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0)); //новий пензль
        hBrushOld = (HBRUSH)SelectObject(hdc, hBrush); //пензль -> у hdc
        p->Show(hdc);
        SelectObject(hdc, hBrushOld); //відновлюється пензль-попередник
        DeleteObject(hBrush);
    }
    else if (typeid(*p) == typeid(LineOOShape))
    { 
        hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
        hPenOld = (HPEN)SelectObject(hdc, hPen);
        hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0)); //новий пензль
        hBrushOld = (HBRUSH)SelectObject(hdc, hBrush); //пензль -> у hdc
        p->Show(hdc);
        Ellipse(hdc, xend, yend - 2*((xend-xstart)/10), xend + 2 * ((xend - xstart) / 10), yend + 2 * ((xend - xstart) / 10));
        SelectObject(hdc, hBrushOld); 
        SelectObject(hdc, hPenOld); 
        DeleteObject(hBrush);
        DeleteObject(hPen);
    }
    else if (typeid(*p) == typeid(CubeShape))
    {
        hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
        hPenOld = (HPEN)SelectObject(hdc, hPen);
        p->Show(hdc);
        SelectObject(hdc, hPenOld);
        DeleteObject(hPen);
    }
    else
    {
        p->Show(hdc);
        SelectObject(hdc, hPenOld); //відновлюється пензль-попередник
        DeleteObject(hPen);
        ReleaseDC(hWnd, hdc);
    }
}

void MyEditor::OnPaint(HWND hWnd, HDC hdc) {
        for (int i = 0; i < MY_SHAPE_ARRAY_SIZE; i++) {
            if (pcshape[i])
            {
                pcshape[i] = p;
                if (typeid(*p) == typeid(RectShape))
                {
                    HBRUSH hBrush, hBrushOld;
                    hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0)); //новий пензль
                    hBrushOld = (HBRUSH)SelectObject(hdc, hBrush); //пензль -> у hdc
                    pcshape[i]->Show(hdc);
                    SelectObject(hdc, hBrushOld); //відновлюється пензль-попередник
                    DeleteObject(hBrush);
                }
                else if (typeid(*p) == typeid(LineOOShape))
                {
                    HPEN hPenOld, hPen;
                    HBRUSH hBrush, hBrushOld;
                    hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
                    hPenOld = (HPEN)SelectObject(hdc, hPen);
                    hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0)); //новий пензль
                    hBrushOld = (HBRUSH)SelectObject(hdc, hBrush); //пензль -> у hdc
                    p->Show(hdc);
                    Ellipse(hdc, xend, yend - 25, xend + 25, yend + 25);
                    SelectObject(hdc, hBrushOld);
                    SelectObject(hdc, hPenOld);
                    DeleteObject(hBrush);
                    DeleteObject(hPen);
                }
                else if (typeid(*p) == typeid(CubeShape))
                {
                    HPEN hPenOld, hPen;
                    hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
                    hPenOld = (HPEN)SelectObject(hdc, hPen);
                    p->Show(hdc);
                    SelectObject(hdc, hPenOld);
                    DeleteObject(hPen);
                }
                else
                {
                    pcshape[i]->Show(hdc);
                }
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
    }




