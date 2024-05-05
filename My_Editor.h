#pragma once
#include "shape.h"
#include <Windows.h>

#define MY_SHAPE_ARRAY_SIZE 101

class MyEditor
{
protected:
    int xstart, ystart, xend, yend;
    Shape* pcshape[MY_SHAPE_ARRAY_SIZE];
public:
    void Start(Shape*);
    void OnLBdown(HWND hWnd);
    void OnLBup(HWND hWnd);
    void OnMouseMove(HWND hWnd);
    void OnPaint(HWND hWnd, HDC hdc);
};


