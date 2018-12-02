#include "Colors.h"
#include <fstream>



void Color::DrowWindow(const int r, const int g, const int b) {
	colors[0] = rgbColor{ r, g ,b };
	SaveFile();
}
void Color::BackGround(const int r, const int g, const int b) {
	colors[1] = rgbColor{ r, g ,b };
	SaveFile();
}
void Color::Primitives(const int r, const int g, const int b) {
	colors[2] = rgbColor{ r, g ,b };
	SaveFile();
}
void Color::Points(const int r, const int g, const int b) {
	colors[3] = rgbColor{ r, g ,b };
	SaveFile();
}
void Color::SelectedPrim(const int r, const int g, const int b) {
	colors[4] = rgbColor{ r, g ,b };
	SaveFile();
}
void Color::DependentPrim(const int r, const int g, const int b) {
	colors[5] = rgbColor{ r, g ,b };
	SaveFile();
}
void Color::ChangingPrim(const int r, const int g, const int b) {
	colors[6] = rgbColor{ r, g ,b };
	SaveFile();
}
void Color::CreatingPrim(const int r, const int g, const int b) {
	colors[7] = rgbColor{ r, g ,b };
	SaveFile();
}
void Color::LineForCurve(const int r, const int g, const int b) {
	colors[8] = rgbColor{ r, g ,b };
	SaveFile();
}

const rgbColor Color::DrowWindow() const {
	return colors[0];
}
const rgbColor Color::BackGround() const {
	return colors[1];
}
const rgbColor Color::Primitives() const {
	return colors[2];
}
const rgbColor Color::Points() const {
	return colors[3];
}
const rgbColor Color::SelectedPrim() const {
	return colors[4];
}
const rgbColor Color::DependentPrim() const {
	return colors[5];
}
const rgbColor Color::ChangingPrim() const {
	return colors[6];
}
const rgbColor Color::CreatingPrim() const {
	return colors[7];
}
const rgbColor Color::LineForCurve() const {
	return colors[8];
}

Color* Color::GetInstance() {
	
	if (instance == nullptr) {
		instance = new Color;
	}
	return instance;
}

void Color::SetTheme(const int theme) {
	switch (theme)
	{
	case 1:
	{
		colors[0] = rgbColor{ col_Silver };
		colors[1] = rgbColor{ col_Black };
		colors[2] = rgbColor{ col_Black };
		colors[3] = rgbColor{ col_Red };
		colors[4] = rgbColor{ col_Blue };
		colors[5] = rgbColor{ col_Orange };
		colors[6] = rgbColor{ col_Yellow };
		colors[7] = rgbColor{ col_Orange };
		colors[8] = rgbColor{ col_Purple };
		break;
	}
	case 2:
	{
		colors[0] = rgbColor{ col_Black };
		colors[1] = rgbColor{ col_White };
		colors[2] = rgbColor{ col_White };
		colors[3] = rgbColor{ col_Red };
		colors[4] = rgbColor{ col_ForestGreen };
		colors[5] = rgbColor{ col_Blue };
		colors[6] = rgbColor{ col_Yellow };
		colors[7] = rgbColor{ col_Orange };
		colors[8] = rgbColor{ col_Purple };
		break;
	}
	case 3:
	{
		colors[0] = rgbColor{ col_Blue };
		colors[1] = rgbColor{ col_DarkBlue };
		colors[2] = rgbColor{ col_Black };
		colors[3] = rgbColor{ col_Red };
		colors[4] = rgbColor{ col_Yellow };
		colors[5] = rgbColor{ col_Green };
		colors[6] = rgbColor{ col_Orange };
		colors[7] = rgbColor{ col_Yellow };
		colors[8] = rgbColor{ col_Purple };
		break;
	}
	default:
		break;
	}
	SaveFile();
}

Color::Color() {
	std::ifstream colorsFile;
	colorsFile.open("colors.txt");
	if (!colorsFile.is_open()) {
		throw std::exception("file is not open");
	}
	
	for (int i = 0; i < size; ++i) {
		if (!colorsFile.eof()) {
			colorsFile >> colors[i].r;
			colorsFile >> colors[i].g;
			colorsFile >> colors[i].b;
		}
		else {
			SetTheme(2);
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
		colorsFile << colors[i].r << ' ';
		colorsFile << colors[i].g << ' ';
		colorsFile << colors[i].b << ' ';
	}
}