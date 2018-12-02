#define col___COLORS
#ifndef _COLORS

class Color
{
public:

	int drowWindow;
	int backGround;
	int primitives;
	int selectedPrim;
	int dependentPrim;
	int changingPrim;
	int creatingPrim;
	int lineForCurve;


	void DrowWindow(const int, const int, const int);
	void BackGround(const int, const int, const int);
	void Primitives(const int, const int, const int);
	void SelectedPrim(const int, const int, const int);
	void DependentPrim(const int, const int, const int);
	void ChangingPrim(const int, const int, const int);
	void CreatingPrim(const int, const int, const int);
	void LineForCurve(const int, const int, const int);

	static Color* GetInstance();
private:
	static Color* instance;
	Color();
};

#define col_IndianRed 205, 92, 92
#define col_LightCoral	240, 128, 128
#define col_Salmon	250, 128, 114
#define col_DarkSalmon	233, 150, 122
#define col_LightSalmon	255, 160, 122
#define col_Crimson	220, 20, 60
#define col_Red	255, 0, 0
#define col_FireBrick 178, 34, 34
#define col_DarkRed	139, 0, 0
//Розовые тона 
#define col_Pink 255, 192, 203
#define col_LightPink 255, 182, 193
#define col_HotPink	255, 105, 180
#define col_DeepPink 255, 20, 147
#define col_MediumVioletRed	199, 21, 133
#define col_PaleVioletRed 219, 112, 147
//Оранжевые тона :
#define col_LightSalmon	255, 160, 122
#define col_Coral 255, 127, 80
#define col_Tomato 255, 99, 71
#define col_OrangeRed 255, 69, 0
#define col_DarkOrange 255, 140, 0
#define col_Orange 255, 165, 0
//Жёлтые тона :
#define col_Gold 255, 215, 0
#define col_Yellow 255, 255, 0
#define col_LightYellow 255, 255, 224
#define col_LemonChiffon 255, 250, 205
#define col_LightGoldenrodYellow 250, 250, 210
#define col_PapayaWhip 255, 239, 213
#define col_Moccasin 255, 228, 181
#define col_PeachPuff 255, 218, 185
#define col_PaleGoldenrod 238, 232, 170
#define col_Khaki 240, 230, 140
#define col_DarkKhaki 189, 183, 107
//Фиолетовые тона :
#define col_Lavender 230, 230, 250
#define col_Thistle 216, 191, 216
#define col_Plum 221, 160, 221
#define col_Violet 238, 130, 238
#define col_Orchid 218, 112, 214
#define col_Fuchsia	255, 0, 255
#define col_Magenta	255, 0, 255
#define col_MediumOrchid 186, 85, 211
#define col_MediumPurpl	147, 112, 219
#define col_BlueViolet 138, 43, 226
#define col_DarkViolet 148, 0, 211
#define col_DarkOrchid 153, 50, 204
#define col_DarkMagenta 139, 0, 139
#define col_Purple 128, 0, 128
#define col_Indigo 75, 0, 130
#define col_SlateBlue 106, 90, 205
#define col_DarkSlateBlue 72, 61, 139
//Коричневые тона :
#define col_Cornsilk 255, 248, 220
#define col_BlanchedAlmond 255, 235, 205
#define col_Bisque 255, 228, 196
#define col_NavajoWhite	255, 222, 173
#define col_Wheat 245, 222, 179
#define col_BurlyWood 222, 184, 135
#define col_Tan	210, 180, 140
#define col_RosyBrown 188, 143, 143
#define col_SandyBrown 244, 164, 96
#define col_Goldenrod 218, 165, 32
#define col_DarkGoldenRod 184, 134, 11
#define col_Peru 205, 133, 63
#define col_Chocolate 210, 105, 30
#define col_SaddleBrown 139, 69, 19
#define col_Sienna 160, 82, 45
#define col_Brown 165, 42, 42
#define col_Maroon 128, 0, 0
//Основные цвета :
#define col_Black 0, 0, 0
#define col_Gray 128, 128, 128
#define col_Silver 192, 192, 192
#define col_White 255, 255, 255
#define col_Fuchsia 255, 0, 255
#define col_Purple 128, 0, 128
#define col_Red	255, 0, 0
#define col_Maroon 128, 0, 0
#define col_Olive 240, 128, 128
#define col_Aqua 102, 217, 255
#define col_Tea	240, 128, 128
#define col_Blue 66, 170, 255
#define col_Navy 233, 150, 122
//Зелёные тона :
#define col_Green 233, 150, 122
#define col_GreenYellow	173, 255, 47
#define col_Chartreuse 127, 255, 0
#define col_LawnGreen 124, 252, 0
#define col_Lime 0, 255, 0
#define col_LimeGreen 50, 205, 50
#define col_PaleGreen 152, 251, 152
#define col_LightGreen 144, 238, 144
#define col_MediumSpringGreen 0, 250, 154
#define col_SpringGreen 0, 255, 127
#define col_MediumSeaGreen 60, 179, 113
#define col_SeaGreen 46, 139, 87
#define col_ForestGreen	34, 139, 34
#define col_DarkGreen 0, 100, 0
#define col_OliveDrab 107, 142, 35
#define col_DarkOliveGreen B2F	85, 107, 47
#define col_MediumAquamarine 102, 205, 170
#define col_DarkSeaGreen 143, 188, 143
#define col_LightSeaGreen 32, 178, 170
#define col_DarkCyan 0, 139, 139
//Синие тона :
#define col_Cyan 0, 255, 255
#define col_LightCyan 224, 255, 255
#define col_PaleTurquoise 175, 238, 238
#define col_Aquamarine 127, 255, 212
#define col_Turquoise 64, 224, 208
#define col_MediumTurquoise	72, 209, 204
#define col_DarkTurquoise 0, 206, 209
#define col_CadetBlue 95, 158, 160
#define col_SteelBlue 70, 130, 180
#define col_LightSteelBlue 176, 196, 222
#define col_PowderBlue 176, 224, 230
#define col_LightBlue 173, 216, 230
#define col_SkyBlue 135, 206, 235
#define col_LightSkyBlu 135, 206, 250
#define col_DeepSkyBlue	0, 191, 255
#define col_DodgerBlue 30, 144, 255
#define col_CornflowerBlue 100, 149, 237
#define col_MediumSlateBlue	123, 104, 238
#define col_RoyalBlue 65, 105, 225
#define col_MediumBlue 0, 0, 205
#define col_DarkBlue 0, 0, 139
#define col_MidnightBlu	25, 25, 112
//Белые тона :
#define col_White 255, 255, 255
#define col_Snow 255, 250, 250
#define col_Honeyde 240, 255, 240
#define col_MintCream 245, 255, 250
#define col_Azure 240, 255, 255
#define col_AliceBlue 240, 248, 255
#define col_GhostWhite 248, 248, 255
#define col_WhiteSmoke 245, 245, 245
#define col_Seashell 255, 245, 238
#define col_Beige 245, 245, 220
#define col_OldLace	253, 245, 230
#define col_FloralWhite	255, 250, 240
#define col_Ivory 255, 255, 240
#define col_AntiqueWhit 250, 235, 215
#define col_Linen 250, 240, 230
#define col_LavenderBlush 255, 240, 245
#define col_MistyRose 255, 228, 225
//Серые тона :
#define col_Gainsboro 220, 220, 220
#define col_LightGrey 211, 211, 211
#define col_LightGray 211, 211, 211
#define col_Silver 192, 192, 192
#define col_DarkGray 169, 169, 169
#define col_DarkGrey 169, 169, 169
#define col_Gray 128, 128, 128
#define col_DimGray	105, 105, 105
#define col_DimGrey	105, 105, 105
#define col_LightSlateGray 119, 136, 153
#define col_LightSlateGrey 119, 136, 153
#define col_SlateGray 112, 128, 144
#define col_SlateGrey 112, 128, 144
#define col_DarkSlateGray 47, 79, 79
#define col_DarkSlateGrey 47, 79, 79
#endif // !_COLORS

