#pragma once

#include "Vector2.h"

enum color { white, red };

class IView
{
private:

public:
	virtual void DrawLine(const Vector2&, const Vector2&) = 0;
	virtual void DrawArc(const Vector2&, const Vector2&) = 0;
	virtual void DrawPoint(const Vector2&) = 0;
	virtual void SetColor(color) = 0;
	virtual void Run() = 0;
	virtual void Clear() = 0;

};

