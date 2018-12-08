#include "IMode.h"


namespace DrawProject {

#pragma region OtherFunction
	string objTypeToString(const object_type type)
	{
		switch (type)
		{
		case ot_point: {
			return string("point");
		}
		case ot_segment: {
			return string("segment");
		}
		case ot_arc: {
			return string("arc");
		}
		case ot_circle: {
			return string("circle");
		}
		case ot_curve: {
			return string("curve");
		}
		case ot_distBetPoints: {
			return string("distBetPoints");
		}
		case ot_equalSegmentLen: {
			return string("equalSegmentLen");
		}
		case ot_pointsOnTheOneHand: {
			return string("pointsOnTheOneHand");
		}
		case ot_distBetPointSeg: {
			return string("distBetPointSeg");
		}
		case ot_pointPosReq: {
			return string("pointPosReq");
		}
		case ot_angleBetSeg: {
			return string("angleBetSeg");
		}
		case ot_distBetPointArc: {
			return string("distBetPointArc");
		}
		case ot_pointInArc: {
			return string("pointInArc");
		}
		default:
			return string("");
		}
	}

	double Parse(string number) {
		int countPoint = 0;
		if (number[0] == 'e' || number[0] == '.') {
			return -1;
		}

		for (size_t i = 1; i < number.length(); ++i) {
			if (number[i] == 'e' || number[i] == '-') {
				return -1;
			}
			if (number[i] == '.') {
				++countPoint;
				if (countPoint > 1) {
					return -1;
				}
			}
		}
		return stod(number);
	}

	const char* ReverseParse(const double dig, int& size)
	{
		std::string strDig;
		std::ostringstream ost;
		ost << std::fixed << std::setprecision(2) << dig;
		strDig = ost.str();

		size = strDig.length();
		char* charDig = new char[size];
		for (int i = 0; i < size; i++)
		{
			charDig[i] = strDig[i];
		}
		return charDig;
	}

	const string ReverseParse(const double dig) {
		std::string strDig;
		std::ostringstream ost;
		ost << std::fixed << std::setprecision(2) << dig;
		strDig = ost.str();

		return strDig;
	}

	const char* str_ch(const string str) {
		char* charDig = new char[str.length() + 1];
		for (size_t i = 0; i < str.length(); i++)
		{
			charDig[i] = str[i];
		}
		charDig[str.length()] = '\0';
		return charDig;
	}
#pragma endregion

#pragma region Mode
	Mode* Mode::UnexpectedEvent(const Event e, const Array<double>& params) {
		switch (e) {
		case ev_symmetricalDraw: {
			return new DMSymmetrical(e, params);
		}
		case ev_rotationDraw: {
			return new DMSectorSymmetrical(e, params);
		}
		case ev_defualtDraw: {
			return new DMDefualt(e);
		}
		case ev_createPoint: {
			return new DMDefualt(e);
		}
		case ev_createStar: {
			return new DMDefualt(e);
		}
		case ev_createBrokenLine: {
			return new DMDefualt(e);
		}
		case ev_createArc: {
			return new DMDefualt(e);
		}
		case ev_createSegment: {
			return new DMDefualt(e);
		}
		case ev_createCircle: {
			return new DMDefualt(e);
		}
		case ev_createCurve: {
			return new DMDefualt(e);
		}
		case ev_mouseMove:
			return nullptr;
		case ev_leftMouseUp:
			return nullptr;
		case ev_ctrlDown:
			return nullptr;
		case ev_ctrlUp:
			return nullptr;
		case ev_enter:
			return nullptr;
		case ex_set_theme:
			return nullptr;
		case ev_undo: {
			auto undo_redo = Undo_Redo::GetInstance();
			undo_redo->Undo();
			return new Selection();
		}
		case ev_redu: {
			auto undo_redo = Undo_Redo::GetInstance();
			undo_redo->Redo();
			return new Selection();
		}
		default:
			return new Selection();
		}
	}

	Mode::Mode() {
		model = Model::GetInstance();
		presenter = Presenter::GetInstance();
		view = presenter->GetView();
		color = Color::GetInstance();
	}
#pragma endregion
}