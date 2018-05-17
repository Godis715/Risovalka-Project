#pragma once

#include "Vector2.h"

enum color { white, red, black};
enum typeDrawing{points, line, polygon};

class IView
{
private:

public:
	virtual void DrawLine(const Vector2&, const Vector2&, typeDrawing) = 0;
	virtual void DrawArc(const Vector2&, const Vector2&, const Vector2&, typeDrawing) = 0;
	virtual void DrawPoint(const Vector2&) = 0;
	virtual void DrawCircle(const Vector2&, const Vector2&, typeDrawing) = 0;
	virtual void SetColor(color) = 0;
	virtual int Run() = 0;
	virtual void Clear() = 0;

};

