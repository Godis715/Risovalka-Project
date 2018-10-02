#ifndef __IVIEW
#define __IVIEW
#include "Vector2.h"
#include "IWidjet.h"

enum typeDrawing{points, line, polygon};
enum statusCreate { drawPoint, drawSegment, drawArc, drawCircle };
enum typeWidjet{displayParamPrim, displayParamReq, creatingToolbar, requirementInput};

class IView
{
private:

public:
	virtual void DrawLine(const Vector2&, const Vector2&, typeDrawing) = 0;
	virtual void DrawArc(const Vector2&, const Vector2&, const Vector2&, typeDrawing) = 0;
	virtual void DrawPoint(const Vector2&) = 0;
	virtual void DrawCircle(const Vector2&, const Vector2&, typeDrawing) = 0;
	virtual void SetColor(int, int, int) = 0;
	virtual int Run() = 0;
	virtual void Update() = 0;
	virtual void TranslateScene(const Vector2&) = 0;
	virtual void ScaleScene(const double&) = 0;
	virtual void RotateScene(const double&) = 0;
	virtual IWidjet* GetWidjet(const typeWidjet) = 0;
};

#endif // !__IVIEW