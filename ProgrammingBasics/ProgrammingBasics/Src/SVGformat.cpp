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
	while (tempSymbol != ' ' && tempSymbol != '\n' && tempSymbol != '\t')
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
				else if ((tempSymbol >= '0' && tempSymbol <= '9')
					|| tempSymbol == '.') dig += tempSymbol;
			} while (tempSymbol != '"');
		}
	} while (tempSymbol != '"');
	return params;
}

bool Model::SVGformat::ParsePointTag(std::ifstream& file)
{
	Array<ID> IDs;
	Array<double> params;
	char tempSymbol = file.get();
	while (tempSymbol != '>')
	{
		if (tempSymbol == '=')
		{
			std::string attribute = ScanAttribute(file);
			Array<double> _params = ScanParams(file);
			if (_params.GetSize() != 1) return false; //бросить исключение
			if (attribute == "px")params.PushBack(_params[0]);
			if (attribute == "py")params.PushBack(_params[0]);
			if (attribute == "id")IDs.PushBack(ID(int(_params[0])));
		}
		tempSymbol = file.get();
	}
	model->CreateObjByID(ot_point, IDs, params);
	return true;
}

bool Model::SVGformat::ParseSegmentTag(std::ifstream& file)
{
	Array<ID> IDs;
	Array<double> params;
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
		}
		tempSymbol = file.get();
	}
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
	std::ofstream file("project.svg");
	if (!file.is_open())
	{
		return false;
	}
	//<?xml version="1.0" encoding="UTF-8"?>
	file << "<?xml version=" << '"' << "1.0" << '"' << " encoding=" << '"' << "UTF-8" << '"' << "?>";
	file << "\n<!-- DrawProject -->";
	file << "\n<svg";
	file << " width=" << '"' << "1000" << '"';
	file << " height=" << '"' << "1000" << '"' << ">";
	if (model->dataPrim.GetSize() == 0) {
		file << "\n</svg>";
		file.close();
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
			file << "\n	<drawProject:point";
			file << "\n		px=" << '"' << tempParams[0] << '"';
			file << "\n		py=" << '"' << tempParams[1] << '"';
			file << "\n		id=" << '"' << tempID.GetHash() << '"';
			file << "\n	/>";
		}
		if (tempType == ot_segment) {
			Segment* tepmSeg = dynamic_cast<Segment*>((*dataPrimMarker));
			file << "\n	<line";
			file << "\n		x1=" << '"' << tempParams[0] << '"';
			file << "\n		y1=" << '"' << tempParams[1] << '"';
			file << "\n		x2=" << '"' << tempParams[2] << '"';
			file << "\n		y2=" << '"' << tempParams[3] << '"';
			file << "\n		id=" << '"' << tempID.GetHash() << '"';
			file << "\n		childIds=" << '"' << tepmSeg->point1->GetID().GetHash() << " "
				<< tepmSeg->point2->GetID().GetHash() << '"';
			file << "\n		stroke=" << '"' << "red" << '"';
			file << "\n		stroke-width=" << '"' << 5 << '"';
			file << "\n	/>";
		}
		if (tempType == ot_arc) {
			Arc* tempArc = dynamic_cast<Arc*>((*dataPrimMarker));
			file << "\n	<path";
			file << "\n		d=" << '"';
			file << "M" << tempParams[2] << "," << tempParams[3] << " ";
			double r = std::sqrt((tempParams[0] - tempParams[2])*(tempParams[0] - tempParams[2]) +
				(tempParams[1] - tempParams[3])*(tempParams[1] - tempParams[3]));
			file << "A" << r << "," << r << " ";
			if (tempArc->GetAngle() <= PI)
			{
				file << "0 " << 0 << "," << 0 << " ";
			}
			else file << "0 " << 1 << "," << 0 << " ";
			file << tempParams[4] << "," << tempParams[5] << '"';
			file << "\n		id=" << '"' << tempID.GetHash() << '"';
			file << "\n		childIds=" << '"' << tempArc->point1->GetID().GetHash() << " "
				<< tempArc->point2->GetID().GetHash() << '"';
			file << "\n		stroke=" << '"' << "red" << '"';
			file << "\n		stroke-width=" << '"' << 5 << '"';
			file << "\n		fill=" << '"' << "none" << '"';
			file << "\n	/>";

			file << "\n	<drawProject:arc";
			file << "\n		x1=" << '"' << tempParams[2] << '"';
			file << "\n		y1=" << '"' << tempParams[3] << '"';
			file << "\n		x2=" << '"' << tempParams[4] << '"';
			file << "\n		y2=" << '"' << tempParams[5] << '"';
			file << "\n		angle=" << '"' << tempArc->GetAngle() << '"';
			file << "\n		id=" << '"' << tempID.GetHash() << '"';
			file << "\n		childIds=" << '"' << tempArc->point1->GetID().GetHash() << " "
				<< tempArc->point2->GetID().GetHash() << '"';
			file << "\n	/>";
		}
		if (tempType == ot_circle) {
			Circle* tepmCircle = dynamic_cast<Circle*>((*dataPrimMarker));
			file << "\n	<circle";
			file << "\n		cx=" << '"' << tempParams[0] << '"';
			file << "\n		cy=" << '"' << tempParams[1] << '"';
			file << "\n		r=" << '"' << tempParams[2] << '"';
			file << "\n		id=" << '"' << tempID.GetHash() << '"';
			file << "\n		childIds=" << '"' << tepmCircle->center->GetID().GetHash() << '"';
			file << "\n		stroke=" << '"' << "red" << '"';
			file << "\n		stroke-width=" << '"' << 5 << '"';
			file << "\n		fill=" << '"' << "none" << '"';
			file << "\n	/>";
		}
	} while (++dataPrimMarker);
	if (model->dataReq.GetSize() != 0) {
		file << "\n	<drawProject:req>\n";
		auto dataReqMarker = model->dataReq.GetMarker();
		do
		{
			ID tempID = (*dataReqMarker)->GetID();
			object_type tempType = (*dataReqMarker)->GetType();
			Array<double> tempParams = (*dataReqMarker)->GetParams();
			List<ID>* tempIDs = (*model->dataLink.Find(tempID));
			switch (tempType) {
			case ot_distBetPoints: {
				file << "		<distBetPoints";
				break;
			}
			case ot_equalSegmentLen: {
				file << "		<equalSegmentLen";
				break;
			}
			case ot_connection: {
				continue;
			}
			case ot_pointPosReq: {
				file << "		<pointPosReq";
				break;
			}
			case ot_pointsOnTheOneHand: {
				file << "		<pointsOnTheOneHand";
				break;
			}
			case ot_distBetPointSeg: {
				file << "		<distBetPointSeg";
				break;
			}
			case ot_angleBetSeg: {
				file << "		<angleBetSeg";
				break;
			}
			case ot_distBetPointArc: {
				file << "		<distBetPointArc";
				break;
			}
			case ot_pointInArc: {
				file << "		<pointInArc";
				break;
			}
			}
			file << "\n			id=" << '"' << tempID.GetHash() << '"';
			if (tempIDs->GetSize() != 0)
			{
				file << "\n			IDs=" << '"';
				auto tempMarker = tempIDs->GetMarker();
				int i = 0;
				do
				{
					file << tempMarker.GetValue().GetHash();
					if (i != tempIDs->GetSize() - 1) file << " ";
					i++;
				} while (++tempMarker);
				file << '"';
			}
			for (int i = 0; i < tempParams.GetSize(); i++)
			{
				if (i == 0) file << "\n			params=" << '"';
				file << tempParams[i];
				if (i == tempParams.GetSize() - 1)
				{
					file << '"';
				}
				else file << " ";
			}
			file << "	/>\n";
		} while (++dataReqMarker);
		file << "	</drawProject:req>";
	}
	file << "\n</svg>";
	file.close();
	return true;
}
