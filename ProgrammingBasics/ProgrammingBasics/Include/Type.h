#ifndef __TYPE
#define __TYPE

#include "Dictionary.h"

enum object_type {
	point_t,
	segment_t,
	arc_t,
	circle_t,

	connection_t,
	distBetPoints_t,
	equalSegmentLen_t,
	pointPosReq_t,

	pointsOnTheOneHand,
	distBetPointSeg,
	angleBetSeg,
	distBetPointArc,
	pointInArc,
	triangle,
	correctTriangle,
	nsAngle,
	correctNsAngle
};

#endif
