#pragma once

#include "Vector2.h"

enum color { white, red };

class IView
{
private:

public:
	virtual void DrawLine(Vector2, Vector2) = 0;
	virtual void DrawArc(Vector2, Vector2) = 0;
	virtual void DrawPoint(Vector2) = 0;
	virtual void SetColor(color) = 0;
	virtual void Run() = 0;
	virtual void Clear() = 0;

};

