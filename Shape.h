#pragma once
#include <windows.h>

class Shape
{
protected:
	long xs1, ys1, xs2, ys2;

public:
	void Set(long x1, long y1, long x2, long y2);
	virtual void Show(HDC hdc) = 0;
};

class PointShape : public Shape
{
public:
	void Show(HDC hdc);
};

class LineShape : public virtual Shape
{
public:
	void Show(HDC hdc);
};

class RectShape : public virtual Shape
{
public:
	void Show(HDC hdc);
};

class EllipseShape : public virtual Shape
{
public:
	void Show(HDC hdc);
};

class LineOOShape : public LineShape, EllipseShape
{
	void Show(HDC hdc);
};

class CubeShape : public LineShape, RectShape
{
	void Show(HDC hdc);
};
