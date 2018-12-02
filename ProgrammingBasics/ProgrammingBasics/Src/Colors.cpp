#include "Colors.h"
#include <fstream>



void Color::DrowWindow(const int r, const int g, const int b) {
	colors[0] = (r << 16) + (g << 8) + b;
	SaveFile();
}
void Color::BackGround(const int r, const int g, const int b) {
	colors[1] = (r << 16) + (g << 8) + b;
	SaveFile();
}
void Color::Primitives(const int r, const int g, const int b) {
	colors[2] = (r << 16) + (g << 8) + b;
	SaveFile();
}
void Color::Points(const int r, const int g, const int b) {
	colors[3] = (r << 16) + (g << 8) + b;
	SaveFile();
}
void Color::SelectedPrim(const int r, const int g, const int b) {
	colors[4] = (r << 16) + (g << 8) + b;
	SaveFile();
}
void Color::DependentPrim(const int r, const int g, const int b) {
	colors[5] = (r << 16) + (g << 8) + b;
	SaveFile();
}
void Color::ChangingPrim(const int r, const int g, const int b) {
	colors[6] = (r << 16) + (g << 8) + b;
	SaveFile();
}
void Color::CreatingPrim(const int r, const int g, const int b) {
	colors[7] = (r << 16) + (g << 8) + b;
	SaveFile();
}
void Color::LineForCurve(const int r, const int g, const int b) {
	colors[8] = (r << 16) + (g << 8) + b;
	SaveFile();
}

const int Color::DrowWindow() const {
	return colors[0];
}
const int Color::BackGround() const {
	return colors[1];
}
const int Color::Primitives() const {
	return colors[2];
}
const int Color::Points() const {
	return colors[3];
}
const int Color::SelectedPrim() const {
	return colors[4];
}
const int Color::DependentPrim() const {
	return colors[5];
}
const int Color::ChangingPrim() const {
	return colors[6];
}
const int Color::CreatingPrim() const {
	return colors[7];
}
const int Color::LineForCurve() const {
	return colors[8];
}

Color* Color::GetInstance() {
	
	if (instance == nullptr) {
		instance = new Color;
	}
	return instance;
}

void Color::FillDefault() {
	colors[0] = 16777215;
	colors[1] = 0;
	colors[2] = 16777215;
	colors[3] = 16711680;
	colors[4] = 2263842;
	colors[5] = 4369151;
	colors[6] = 16776960;
	colors[7] = 16753920;
	colors[8] = 8388736;
}

Color::Color() {
	std::ifstream colorsFile;
	colorsFile.open("colors.txt");
	if (!colorsFile.is_open()) {
		throw std::exception("file is not open");
	}
	
	for (int i = 0; i < size; ++i) {
		if (!colorsFile.eof()) {
			colorsFile >> colors[i];
		}
		else {
			FillDefault();
			return;
		}
	}
}
Color* Color::instance = nullptr;

void Color::SaveFile() {
	std::ofstream colorsFile;
	colorsFile.open("colors.txt");
	if (!colorsFile.is_open()) {
		throw std::exception("file is not open");
	}
	for (int i = 0; i < size; ++i) {
		colorsFile << colors[i] << ' ';
	}
}