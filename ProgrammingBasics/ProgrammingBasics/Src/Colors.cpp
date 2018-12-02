#include "Colors.h"

void Color::DrowWindow(const int r, const int g, const int b) {
	drowWindow = (r << 16) + (g << 8) + b;
}
void Color::BackGround(const int r, const int g, const int b) {
	backGround = (r << 16) + (g << 8) + b;
}
void Color::Primitives(const int r, const int g, const int b) {
	primitives = (r << 16) + (g << 8) + b;
}
void Color::SelectedPrim(const int r, const int g, const int b) {
	selectedPrim = (r << 16) + (g << 8) + b;
}
void Color::DependentPrim(const int r, const int g, const int b) {
	dependentPrim = (r << 16) + (g << 8) + b;
}
void Color::ChangingPrim(const int r, const int g, const int b) {
	changingPrim = (r << 16) + (g << 8) + b;
}
void Color::CreatingPrim(const int r, const int g, const int b) {
	creatingPrim = (r << 16) + (g << 8) + b;
}
void Color::LineForCurve(const int r, const int g, const int b) {
	lineForCurve = (r << 16) + (g << 8) + b;
}

Color* Color::GetInstance() {
	if (instance == nullptr) {
		instance = new Color;
	}
	return instance;
}

Color::Color() {

}
Color* Color::instance = nullptr;
