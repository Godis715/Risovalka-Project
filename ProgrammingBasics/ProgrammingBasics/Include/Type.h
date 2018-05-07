#ifndef __TYPE
#define __TYPE

#include "Hash-Table.h"

enum prim_type {
	point_t,
	segment_t,
	arc_t
};

enum req_type {
	connection_t,
	distBetPoints_t,
	equalSegmentLen_t,

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
