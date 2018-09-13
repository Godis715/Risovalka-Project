#include "Model.h"

//private
Model::SVGformat::SVGformat() {}
Model::SVGformat::SVGformat(Model* _model)
{
	model = _model;
}
Model::SVGformat::~SVGformat() {}

std::string Model::SVGformat::ScanAttribute(std::ifstream& file)
{
	int startPos = file.tellg();
	file.seekg(-2, std::ios_base::cur);
	char tempSymbol = file.get();
	std::string attribute;
	while (tempSymbol != ' ' && tempSymbol != '\n' && tempSymbol != char(9))
	{
		attribute.insert(attribute.begin(), tempSymbol);
		file.seekg(-2, std::ios_base::cur);
		tempSymbol = file.get();
	}
	file.seekg(startPos - file.tellg(), std::ios_base::cur);
	return attribute;
}

Array<double> Model::SVGformat::ScanParams(std::ifstream& file)
{
	Array<double> params;
	char tempSymbol;
	std::string dig;
	do
	{
		tempSymbol = file.get();
		if (tempSymbol == '"')
		{
			do
			{
				tempSymbol = file.get();
				if ((tempSymbol == ' ' || tempSymbol == '"') && dig != "")
				{
					params.PushBack(std::stod(dig));
					dig.clear();
				}
				else if ((tempSymbol >= 48 && tempSymbol <= 57)
					|| tempSymbol == '.') dig += tempSymbol;
			} while (tempSymbol != '"');
		}
	} while (tempSymbol != '"');
	return params;
}

bool Model::SVGformat::ParsePointTag(std::ifstream& file)
{
	double x;
	double y;
	ID id;
	char tempSymbol = file.get();
	while (tempSymbol != '>')
	{
		if (tempSymbol == '=')
		{
			std::string attribute = ScanAttribute(file);
			Array<double> params = ScanParams(file);
			if (params.GetSize() != 1) return false; //бросить исключение
			if (attribute == "px")x = params[0];
			if (attribute == "py")y = params[0];
			if (attribute == "id")id = ID(int(params[0]));
		}
		tempSymbol = file.get();
	}
	Array<double> params;
	params.PushBack(x);
	params.PushBack(y);
	Array<ID> IDs;
	IDs.PushBack(id);
	model->CreateObjByID(ot_point, IDs, params);
	return true;
}

bool Model::SVGformat::ParseSegmentTag(std::ifstream& file)
{
	Array<ID> IDs;
	char tempSymbol = file.get();
	while (tempSymbol != '>')
	{
		if (tempSymbol == '=')
		{
			std::string attribute = ScanAttribute(file);
			Array<double> params = ScanParams(file);
			if (attribute == "id")
			{
				if (params.GetSize() == 1)
				{
					IDs.PushBack(ID(int(params[0])));
				}
				else return false; //бросить исключение
			}
			if (attribute == "childIds")
			{
				if (params.GetSize() == 2)
				{
					IDs.PushBack(ID(int(params[0])));
					IDs.PushBack(ID(int(params[1])));
				}
				else return false; //бросить исключение
			}
		}
		tempSymbol = file.get();
	}
	Array<double> params;
	model->CreateObjByID(ot_segment, IDs, params);
}

bool Model::SVGformat::ParseCircleTag(std::ifstream& file)
{
	Array<ID> IDs;
	Array <double> params;
	char tempSymbol = file.get();
	while (tempSymbol != '>')
	{
		if (tempSymbol == '=')
		{
			std::string attribute = ScanAttribute(file);
			Array<double> _params = ScanParams(file);
			if (attribute == "id")
			{
				if (_params.GetSize() == 1)
				{
					IDs.PushBack(ID(int(_params[0])));
				}
				else return false; //бросить исключение
			}
			if (attribute == "childIds")
			{
				if (_params.GetSize() == 1)
				{
					IDs.PushBack(ID(int(_params[0])));
				}
				else return false; //бросить исключение
			}
			if (attribute == "r")
			{
				if (_params.GetSize() == 1)
				{
					params.PushBack(_params[0]);
				}
				else return false; //бросить исключение
			}
		}
		tempSymbol = file.get();
	}
	model->CreateObjByID(ot_circle, IDs, params);
	return true;
}

bool Model::SVGformat::ParseArcTag(std::ifstream& file)
{
	Array<ID> IDs;
	Array <double> params;
	char tempSymbol = file.get();
	while (tempSymbol != '>')
	{
		if (tempSymbol == '=')
		{
			std::string attribute = ScanAttribute(file);
			Array<double> _params = ScanParams(file);
			if (attribute == "id")
			{
				if (_params.GetSize() == 1)
				{
					IDs.PushBack(ID(int(_params[0])));
				}
				else return false; //бросить исключение
			}
			if (attribute == "childIds")
			{
				if (_params.GetSize() == 2)
				{
					IDs.PushBack(ID(int(_params[0])));
					IDs.PushBack(ID(int(_params[1])));
				}
				else return false; //бросить исключение
			}
			if (attribute == "angle")
			{
				if (_params.GetSize() == 1)
				{
					params.PushBack(_params[0]);
				}
				else return false; //бросить исключение
			}
		}
		tempSymbol = file.get();
	}
	model->CreateObjByID(ot_arc, IDs, params);
	return true;
}

bool Model::SVGformat::ParseRequirementTag(std::ifstream& file, object_type typeReq)
{
	Array<ID> IDs;
	Array <double> params;
	char tempSymbol = file.get();
	while (tempSymbol != '>')
	{
		if (tempSymbol == '=')
		{
			std::string attribute = ScanAttribute(file);
			Array<double> _params = ScanParams(file);
			if (attribute == "id")
			{
				if (_params.GetSize() == 1)
				{
					IDs.PushBack(ID(int(_params[0])));
				}
				else return false; //бросить исключение
			}
			if (attribute == "IDs")
			{
				for (int i = 0; i < _params.GetSize(); i++)
				{
					IDs.PushBack(ID(int(_params[i])));
				}
			}
			if (attribute == "params")
			{
				for (int i = 0; i < _params.GetSize(); i++)
				{
					params.PushBack(_params[i]);
				}
			}
		}
		tempSymbol = file.get();
	}
	model->CreateObjByID(typeReq, IDs, params);
	return true;
}

//public
bool Model::SVGformat::Download(const std::string nameFile)
{
	std::ifstream file("project.svg");
	if (!file.is_open())
	{
		return false;
	}
	while (!file.eof())
	{
		char tempSymbol = file.get();
		if (tempSymbol == '<')
		{
			std::string tag;
			file >> tag;
			if (tag == "drawProject:point")ParsePointTag(file);
			if (tag == "line")ParseSegmentTag(file);
			if (tag == "circle")ParseCircleTag(file);
			if (tag == "drawProject:arc")ParseArcTag(file);
			if (tag == "drawProject:req>")
			{
				bool isEnd = false;
				while (!isEnd)
				{
					tempSymbol = file.get();
					if (tempSymbol == '<')
					{
						file >> tag;
						if (tag == "distBetPoints")ParseRequirementTag(file, ot_distBetPoints);
						if (tag == "equalSegmentLen")ParseRequirementTag(file, ot_equalSegmentLen);
						if (tag == "pointPosReq")ParseRequirementTag(file, ot_pointPosReq);
						if (tag == "pointsOnTheOneHand")ParseRequirementTag(file, ot_pointsOnTheOneHand);
						if (tag == "distBetPointSeg")ParseRequirementTag(file, ot_distBetPointSeg);
						if (tag == "distBetPointArc")ParseRequirementTag(file, ot_distBetPointArc);
						if (tag == "angleBetSeg")ParseRequirementTag(file, ot_angleBetSeg);
						if (tag == "pointInArc")ParseRequirementTag(file, ot_pointInArc);
						if (tag == "/drawProject:req>")isEnd = true;
					}
				}
			}
		}
	}
	file.close();
	return true;
}

bool Model::SVGformat::Save(const std::string way)
{
	std::ofstream saveFile("project.svg");
	//<?xml version="1.0" encoding="UTF-8"?>
	saveFile << "<?xml version=" << '"' << "1.0" << '"' << " encoding=" << '"' << "UTF-8" << '"' << "?>";
	saveFile << "\n<!-- DrawProject -->";
	saveFile << "\n<svg";
	saveFile << " width=" << '"' << "1000" << '"';
	saveFile << " height=" << '"' << "1000" << '"' << ">";
	if (model->dataPrim.GetSize() == 0) {
		saveFile << "\n</svg>";
		saveFile.close();
		return false;
	}
	auto dataPrimMarker = model->dataPrim.GetMarker();
	do
	{
		object_type tempType;
		Array<double> tempParams;
		ID tempID = (*dataPrimMarker)->GetID();
		model->GetObjParam(tempID, tempParams);
		model->GetObjType(tempID, tempType);
		if (tempType == ot_point) {
			saveFile << "\n	<drawProject:point";
			saveFile << "\n		px=" << '"' << tempParams[0] << '"';
			saveFile << "\n		py=" << '"' << tempParams[1] << '"';
			saveFile << "\n		id=" << '"' << tempID.GetHash() << '"';
			saveFile << "\n	/>";
		}
		if (tempType == ot_segment) {
			Segment* tepmSeg = dynamic_cast<Segment*>((*dataPrimMarker));
			saveFile << "\n	<line";
			saveFile << "\n		x1=" << '"' << tempParams[0] << '"';
			saveFile << "\n		y1=" << '"' << tempParams[1] << '"';
			saveFile << "\n		x2=" << '"' << tempParams[2] << '"';
			saveFile << "\n		y2=" << '"' << tempParams[3] << '"';
			saveFile << "\n		id=" << '"' << tempID.GetHash() << '"';
			saveFile << "\n		childIds=" << '"' << tepmSeg->point1->GetID().GetHash() << " "
				<< tepmSeg->point2->GetID().GetHash() << '"';
			saveFile << "\n		stroke=" << '"' << "red" << '"';
			saveFile << "\n		stroke-width=" << '"' << 5 << '"';
			saveFile << "\n	/>";
		}
		if (tempType == ot_arc) {
			Arc* tempArc = dynamic_cast<Arc*>((*dataPrimMarker));
			saveFile << "\n	<path";
			saveFile << "\n		d=" << '"';
			saveFile << "M" << tempParams[2] << "," << tempParams[3] << " ";
			double r = std::sqrt((tempParams[0] - tempParams[2])*(tempParams[0] - tempParams[2]) +
				(tempParams[1] - tempParams[3])*(tempParams[1] - tempParams[3]));
			saveFile << "A" << r << "," << r << " ";
			if (tempArc->GetAngle() <= PI)
			{
				saveFile << "0 " << 0 << "," << 0 << " ";
			}
			else saveFile << "0 " << 1 << "," << 0 << " ";
			saveFile << tempParams[4] << "," << tempParams[5] << '"';
			saveFile << "\n		id=" << '"' << tempID.GetHash() << '"';
			saveFile << "\n		childIds=" << '"' << tempArc->point1->GetID().GetHash() << " "
				<< tempArc->point2->GetID().GetHash() << '"';
			saveFile << "\n		stroke=" << '"' << "red" << '"';
			saveFile << "\n		stroke-width=" << '"' << 5 << '"';
			saveFile << "\n		fill=" << '"' << "none" << '"';
			saveFile << "\n	/>";

			saveFile << "\n	<drawProject:arc";
			saveFile << "\n		x1=" << '"' << tempParams[2] << '"';
			saveFile << "\n		y1=" << '"' << tempParams[3] << '"';
			saveFile << "\n		x2=" << '"' << tempParams[4] << '"';
			saveFile << "\n		y2=" << '"' << tempParams[5] << '"';
			saveFile << "\n		angle=" << '"' << tempArc->GetAngle() << '"';
			saveFile << "\n		id=" << '"' << tempID.GetHash() << '"';
			saveFile << "\n		childIds=" << '"' << tempArc->point1->GetID().GetHash() << " "
				<< tempArc->point2->GetID().GetHash() << '"';
			saveFile << "\n	/>";
		}
		if (tempType == ot_circle) {
			Circle* tepmCircle = dynamic_cast<Circle*>((*dataPrimMarker));
			saveFile << "\n	<circle";
			saveFile << "\n		cx=" << '"' << tempParams[0] << '"';
			saveFile << "\n		cy=" << '"' << tempParams[1] << '"';
			saveFile << "\n		r=" << '"' << tempParams[2] << '"';
			saveFile << "\n		id=" << '"' << tempID.GetHash() << '"';
			saveFile << "\n		childIds=" << '"' << tepmCircle->center->GetID().GetHash() << '"';
			saveFile << "\n		stroke=" << '"' << "red" << '"';
			saveFile << "\n		stroke-width=" << '"' << 5 << '"';
			saveFile << "\n		fill=" << '"' << "none" << '"';
			saveFile << "\n	/>";
		}
	} while (++dataPrimMarker);
	if (model->dataReq.GetSize() != 0) {
		saveFile << "\n	<drawProject:req>\n";
		auto dataReqMarker = model->dataReq.GetMarker();
		do
		{
			ID tempID = (*dataReqMarker)->GetID();
			object_type tempType = (*dataReqMarker)->GetType();
			Array<double> tempParams = (*dataReqMarker)->GetParams();
			List<ID>* tempIDs = (*model->dataLink.Find(tempID));
			switch (tempType) {
			case ot_distBetPoints: {
				saveFile << "		<distBetPoints";
				break;
			}
			case ot_equalSegmentLen: {
				saveFile << "		<equalSegmentLen";
				break;
			}
			case ot_connection: {
				continue;
			}
			case ot_pointPosReq: {
				saveFile << "		<pointPosReq";
				break;
			}
			case ot_pointsOnTheOneHand: {
				saveFile << "		<pointsOnTheOneHand";
				break;
			}
			case ot_distBetPointSeg: {
				saveFile << "		<distBetPointSeg";
				break;
			}
			case ot_angleBetSeg: {
				saveFile << "		<angleBetSeg";
				break;
			}
			case ot_distBetPointArc: {
				saveFile << "		<distBetPointArc";
				break;
			}
			case ot_pointInArc: {
				saveFile << "		<pointInArc";
				break;
			}
			}
			saveFile << "\n			id=" << '"' << tempID.GetHash() << '"';
			if (tempIDs->GetSize() != 0)
			{
				saveFile << "\n			IDs=" << '"';
				auto tempMarker = tempIDs->GetMarker();
				int i = 0;
				do
				{
					saveFile << tempMarker.GetValue().GetHash();
					if (i != tempIDs->GetSize() - 1) saveFile << " ";
					i++;
				} while (++tempMarker);
				saveFile << '"';
			}
			for (int i = 0; i < tempParams.GetSize(); i++)
			{
				if (i == 0) saveFile << "\n			params=" << '"';
				saveFile << tempParams[i];
				if (i == tempParams.GetSize() - 1)
				{
					saveFile << '"';
				}
				else saveFile << " ";
			}
			saveFile << "	/>\n";
		} while (++dataReqMarker);
		saveFile << "	</drawProject:req>";
	}
	saveFile << "\n</svg>";
	saveFile.close();
	return true;
}
