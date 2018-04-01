#pragma once
#include "IView.h"
#include "Model.h"
#include "ID.h"
#include "Type.h"

class IDrawable {
public:
	virtual void Draw() = 0;
};

class Presenter
{
private:
	IView* view;
	Model* model;
public:
	Presenter(IView*);

	//Polygon* CreatePolygon(/*args*/);
	//Circle* CreateCircle(/*args*/);
	//LineSegment* CreateSegment(/*args*/);
};

class Figure : public IDrawable, public Primitive{
private:
	// field position from primitive
public:
	void IDrawable::Draw() = 0;
	virtual float GetDistance() = 0;
	virtual void SetPosition(Vector2) = 0;
	virtual void Rotate(float) = 0;
};

/*
class Polygon : public Figure {
private:
public:
};

class Circle : public Figure {
private:
public:
};

class LineSegment : public Figure {
private:
public:
}; */