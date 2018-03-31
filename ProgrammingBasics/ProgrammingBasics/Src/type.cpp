#include "Type.h"

//Type::Type(const type_id _id) {
//	switch (_id)
//	{
//	case point: {
//		name = "Point";
//		break;
//	}
//	case segment: {
//		name = "Segment";
//		break;
//	}
//	case arc: {
//		name = "Arc";
//		break;
//	}
//	default:
//		/*throw unknown type_id*/
//		break;
//	}
//	id = _id;
//}
//
//std::string Type::GetName() const {
//	return name;
//}
//
//type_id Type::GetTypeId() const {
//	return id;
//}

//TypeRequirement::TypeRequirement(const Requirement_id _id) {
//	switch (_id)
//	{
//	case distBetPoints: {
//		name = "DistBetPoints";
//		break;
//	}
//	case pointsOnTheOneHand: {
//		name = "PointsOnTheOneHand";
//		break;
//	}
//	case distBetPointSeg: {
//		name = "DistBetPointSeg";
//		break;
//	}
//	case angleBetSeg: {
//		name = "AngleBetSeg";
//		break;
//	}
//	case distBetPointArc: {
//		name = "DistBetPointArc";
//		break;
//	}
//	case pointInArc: {
//		name = "PointInArc";
//		break;
//	}
//	default:
//		/*throw unknown type_id*/
//		break;
//	}
//	id = _id;
//}
//
//std::string TypeRequirement::GetName() const {
//	return name;
//}
//
//Requirement_id TypeRequirement::GetRequirementId() const {
//	return id;
//}