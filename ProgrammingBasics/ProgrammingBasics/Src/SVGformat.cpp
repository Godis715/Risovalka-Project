#include "DataController.h"

//private

#define POINT_PRMS 2
#define SEGMENT_PRMS 0
#define ARC_PRMS 1
#define CIRCLE_PRMS 1

#define POINT_CHLD 0
#define SEGMENT_CHLD 2
#define ARC_CHLD 2
#define CIRCLE_CHLD 1

#define STROKE_WIDTH 5
#define STROKE_COLOR "red"
#define DOC_WIDTH 1000
#define DOC_HEIGHT 1000

SVGformat::SVGObject::SVGObject(object_type _type, int childrenNum, int paramsNum) :
	children(childrenNum), params(paramsNum), type(_type)
{
	
}


SVGformat::SVGformat() {
	dataCtrl = DataController::GetInstance();
	primCtrl = PrimController::GetInstance();
	reqCtrl = ReqController::GetInstance();
	objCtrl = ObjectController::GetInstance();
}

SVGformat::~SVGformat() {}

bool SVGformat::IsContains(IDMap& idMap, unsigned long long hash) {
	auto it = idMap.Find(hash);
	return it.IsValid();
}

std::string SVGformat::ScanAttribute(std::ifstream& file)
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

Array<double> SVGformat::ScanParams(std::ifstream& file)
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
					|| tempSymbol == '.' || tempSymbol == '-') dig += tempSymbol;
			} while (tempSymbol != '"');
		}
	} while (tempSymbol != '"');
	return params;
}

void SVGformat::AddObject(const SVGObject& obj) {
	auto iter = objMap.Find(obj.hash);
	if (!iter.IsValid()) {
		objMap.Add(obj.hash, obj);
	}
	else {
		LOG("SVGformat::AddObject: Object with that ID already exist", LEVEL_3);
	}
}

bool SVGformat::ParsePointTag(std::ifstream& file)
{
	SVGObject obj(ot_point, POINT_CHLD, POINT_PRMS);
	char tempSymbol = file.get();
	while (tempSymbol != '>')
	{
		if (tempSymbol == '=')
		{
			std::string attribute = ScanAttribute(file);
			Array<double> _params = ScanParams(file);
			if (_params.GetSize() != 1) return false; //бросить исключение
			if (attribute == "px")
				obj.params[0] = _params[0];
			if (attribute == "py")
				obj.params[1] = _params[0];
			if (attribute == "id")
				obj.hash = _params[0];
		}
		tempSymbol = file.get();
	}
	
	AddObject(obj);

	return true;
}

bool SVGformat::ParseSegmentTag(std::ifstream& file)
{
	SVGObject obj(ot_segment, SEGMENT_CHLD, SEGMENT_PRMS);
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
					obj.hash = _params[0];
				}
				else return false; //бросить исключение
			}
			if (attribute == "childIds")
			{
				if (_params.GetSize() == 2)
				{
					obj.children[0] = _params[0];
					obj.children[1] = _params[1];
				}
				else return false; //бросить исключение
			}
		}
		tempSymbol = file.get();
	}
	AddObject(obj);
}

bool SVGformat::ParseCircleTag(std::ifstream& file)
{
	SVGObject obj(ot_circle, CIRCLE_CHLD, CIRCLE_PRMS);
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
					obj.hash = _params[0];
				}
				else return false; //бросить исключение
			}
			if (attribute == "childIds")
			{
				if (_params.GetSize() == 1)
				{
					obj.children[0] = _params[0];
				}
				else return false; //бросить исключение
			}
			if (attribute == "r")
			{
				if (_params.GetSize() == 1)
				{
					obj.params[0] = _params[0];
				}
				else return false; //бросить исключение
			}
		}
		tempSymbol = file.get();
	}
	AddObject(obj);
	return true;
}

bool SVGformat::ParseArcTag(std::ifstream& file)
{
	SVGObject obj(ot_arc, ARC_CHLD, ARC_PRMS);
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
					obj.hash = _params[0];
				}
				else return false; //бросить исключение
			}
			if (attribute == "childIds")
			{
				if (_params.GetSize() == 2)
				{
					obj.children[0] = _params[0];
					obj.children[1] = _params[1];
				}
				else return false; //бросить исключение
			}
			if (attribute == "angle")
			{
				if (_params.GetSize() == 1)
				{
					obj.params[0] = _params[0];
				}
				else return false; //бросить исключение
			}
		}
		tempSymbol = file.get();
	}
	AddObject(obj);
	return true;
}

bool SVGformat::ParseRequirementTag(std::ifstream& file, object_type typeReq)
{
	SVGObject obj(typeReq, 0, 0);
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
					obj.hash = _params[0];
				}
				else return false; //бросить исключение
			}
			if (attribute == "IDs")
			{
				for (int i = 0; i < _params.GetSize(); i++)
				{
					obj.children.PushBack(int(_params[i]));
				}
			}
			if (attribute == "params")
			{
				for (int i = 0; i < _params.GetSize(); i++)
				{
					obj.params.PushBack(_params[i]);
				}
			}
		}
		tempSymbol = file.get();
	}
	AddObject(obj);
	return true;
}

//public
bool SVGformat::Download(const std::string& nameFile)
{

	objMap.DeleteDict();

	std::ifstream file(nameFile);
	if (!file.is_open())
	{
		LOGERROR("SVGformat::Download: couldn't open the file", LEVEL_3);
		return false;
	}

	while (!file.eof())
	{
		char tempSymbol = file.get();
		if (tempSymbol == '<')
		{
			std::string tag;
			file >> tag;
			if (tag == "drawProject:point")
				ParsePointTag(file);
			if (tag == "line")
				ParseSegmentTag(file);
			if (tag == "circle")
				ParseCircleTag(file);
			if (tag == "drawProject:arc")
				ParseArcTag(file);
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
	ApplyDownloadData();
	return true;
}

void SVGformat::ApplyDownloadData() {
	IDMap idMap;
	auto objIt = objMap.GetMarker();

	// init points - as first
	while (objIt.IsValid()) {
		SVGObject obj = *objIt;
		if (obj.type == ot_point) {
			if (!IsContains(idMap, obj.hash)) {
				ID point = primCtrl->CreatePrimitive(obj.type, Array<ID>(0), obj.params);
				dataCtrl->AddObject(point);
				idMap.Add(obj.hash, point);
			}
			else {
				LOG("SVGformat::ApplyDonwloadData: this ID already exist", LEVEL_3);
			}
		}
		++objIt;
	}

	// init points - as first

	objIt = objMap.GetMarker();
	while (objIt.IsValid()) {
		SVGObject obj = *objIt;
		if (primCtrl->IsPrimitive(obj.type) && obj.type != ot_point) {
			if (!IsContains(idMap, obj.hash)) {
				Array<ID> children(obj.children.GetSize());
				for (int i = 0; i < obj.children.GetSize(); ++i) {
					if (!IsContains(idMap, obj.children[i])) {
						LOGERROR("SVGformat::ApplyDonwloadData: trying to use unknown ID", LEVEL_3);
					}
					children[i] = *(idMap.Find(obj.children[i]));
				}
				ID newObject = primCtrl->CreatePrimitive(obj.type, children, obj.params);
				dataCtrl->AddObject(newObject);
				dataCtrl->Connect(newObject, children);
				idMap.Add(obj.hash, newObject);
			}
			else {
				LOG("SVGformat::ApplyDonwloadData: this ID already exist", LEVEL_3);
			}
		}
		++objIt;
	}

	objIt = objMap.GetMarker();
	while (objIt.IsValid()) {
		SVGObject obj = *objIt;
		if (reqCtrl->IsReq(obj.type)) {
			if (!IsContains(idMap, obj.hash)) {
				Array<ID> children(obj.children.GetSize());
				for (int i = 0; i < obj.children.GetSize(); ++i) {
					if (!IsContains(idMap, obj.children[i])) {
						LOGERROR("SVGformat::ApplyDonwloadData: trying to use unknown ID", LEVEL_3);
					}
					children[i] = *(idMap.Find(obj.children[i]));
				}
				ID newObject = reqCtrl->CreateReq(obj.type, children, obj.params);
				dataCtrl->AddObject(newObject);
				dataCtrl->Connect(newObject, children);
				idMap.Add(obj.hash, newObject);
			}
			else {
				LOG("SVGformat::ApplyDonwloadData: this ID already exist", LEVEL_3);
			}
		}
		++objIt;
	}
}


bool SVGformat::Save(const std::string& path, bool withDrawProjectTags)
{
	std::ofstream file(path);
	if (!file.is_open())
	{
		return false;
	}
	//<?xml version="1.0" encoding="UTF-8"?>
	file << "<?xml version=" << '"' << "1.0" << '"' << " encoding=" << '"' << "UTF-8" << '"' << "?>";
	file << "\n<!-- DrawProject -->";
	file << "\n<svg";
	file << " width=" << '"' << DOC_WIDTH << '"';
	file << " height=" << '"' << DOC_HEIGHT << '"' << ">";
	if (dataCtrl->primData.GetSize() == 0) {
		file << "\n</svg>";
		file.close();
		return false;
	}
	auto primDataMarker = dataCtrl->primData.GetMarker();
	while(primDataMarker.IsValid()) {
		ID tempID = (*primDataMarker);
		Array<double> tempParams = primCtrl->GetPrimitiveParamsAsValues(tempID);
		object_type tempType = objCtrl->GetType(tempID);
		Array<ID> children = primCtrl->GetChildren(tempID);
		if (tempType == ot_point) {
			if (withDrawProjectTags) {
				file << "\n	<drawProject:point";
				file << "\n		px=" << '"' << tempParams[0] << '"';
				file << "\n		py=" << '"' << tempParams[1] << '"';
				file << "\n		id=" << '"' << tempID.GetHash() << '"';
				file << "\n	/>";
			}
		}
		if (tempType == ot_segment) {
			auto point1 = primCtrl->GetPrimitiveParamsAsValues(children[0]);
			auto point2 = primCtrl->GetPrimitiveParamsAsValues(children[1]);

			file << "\n	<line";
			file << "\n		x1=" << '"' << point1[0] << '"';
			file << "\n		y1=" << '"' << point1[1] << '"';
			file << "\n		x2=" << '"' << point2[0] << '"';
			file << "\n		y2=" << '"' << point2[1] << '"';
			file << "\n		id=" << '"' << tempID.GetHash() << '"';
			file << "\n		childIds=" << '"' << children[0].GetHash() << " "
				<< children[1].GetHash() << '"';
			file << "\n		stroke=" << '"' << STROKE_COLOR << '"';
			file << "\n		stroke-width=" << '"' << STROKE_WIDTH << '"';
			file << "\n	/>";
		}
		if (tempType == ot_arc) {
			Arc* tempArc = dynamic_cast<Arc*>(primCtrl->GetPrimitive(tempID));
			auto point1 = primCtrl->GetPrimitiveParamsAsValues(children[0]);
			auto point2 = primCtrl->GetPrimitiveParamsAsValues(children[1]);
			auto center = tempArc->GetCenter();

			file << "\n	<path";
			file << "\n		d=" << '"';
			file << "M" << point1[0] << "," << point1[1] << " ";
			double r = std::sqrt((center.x - point1[0])*(center.x - point1[0]) +
				(center.y - point2[0])*(center.y - point2[0]));
			file << "A" << r << "," << r << " ";
			if (tempArc->GetAngle() <= PI)
			{
				file << "0 " << 0 << "," << 0 << " ";
			}
			else file << "0 " << 1 << "," << 0 << " ";
			file << point2[0] << "," << point2[1] << '"';
			file << "\n		id=" << '"' << tempID.GetHash() << '"';
			file << "\n		childIds=" << '"' << children[0].GetHash() << " "
				<< children[1].GetHash() << '"';
			file << "\n		stroke=" << '"' << STROKE_COLOR << '"';
			file << "\n		stroke-width=" << '"' << STROKE_WIDTH << '"';
			file << "\n		fill=" << '"' << "none" << '"';
			file << "\n	/>";

			if (withDrawProjectTags) {
				file << "\n	<drawProject:arc";
				file << "\n		x1=" << '"' << point1[0] << '"';
				file << "\n		y1=" << '"' << point1[1] << '"';
				file << "\n		x2=" << '"' << point2[0] << '"';
				file << "\n		y2=" << '"' << point2[1] << '"';
				file << "\n		angle=" << '"' << tempParams[0] << '"';
				file << "\n		id=" << '"' << tempID.GetHash() << '"';
				file << "\n		childIds=" << '"' << children[0].GetHash() << " "
					<< children[1].GetHash() << '"';
				file << "\n	/>";
			}
		}
		if (tempType == ot_circle) {
			Circle* tepmCircle = dynamic_cast<Circle*>(primCtrl->GetPrimitive(tempID));
			auto center = primCtrl->GetPrimitiveParamsAsValues(children[0]);
			file << "\n	<circle";
			file << "\n		cx=" << '"' << center[0] << '"';
			file << "\n		cy=" << '"' << center[1] << '"';
			file << "\n		r=" << '"' << tempParams[0] << '"';
			file << "\n		id=" << '"' << tempID.GetHash() << '"';
			file << "\n		childIds=" << '"' << children[0].GetHash() << '"';
			file << "\n		stroke=" << '"' << STROKE_COLOR << '"';
			file << "\n		stroke-width=" << '"' << STROKE_WIDTH << '"';
			file << "\n		fill=" << '"' << "none" << '"';
			file << "\n	/>";
		}
		++primDataMarker;
	}
	if (dataCtrl->reqData.GetSize() != 0) {
		if (withDrawProjectTags) {
			file << "\n	<drawProject:req>\n";
			auto dataReqMarker = dataCtrl->reqData.GetMarker();
			while (dataReqMarker.IsValid()) {
				ID tempID = (*dataReqMarker);
				Array<double> tempParams = reqCtrl->GetReqParamsAsValues(tempID);
				object_type tempType = objCtrl->GetType(tempID);
				BinSearchTree<ID, ID>* tempIDs = (*dataCtrl->linkData.Find(tempID));
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
						file << (*tempMarker).GetHash();
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
				++dataReqMarker;
			}
			file << "	</drawProject:req>";
		}
	}
	file << "\n</svg>";
	file.close();
	return true;
}
