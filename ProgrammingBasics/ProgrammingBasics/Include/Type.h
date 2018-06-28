#ifndef __TYPE
#define __TYPE

#include "Dictionary.h"

enum object_type {
	ot_point,
	ot_segment,
	ot_arc,
	ot_circle,

	ot_connection,
	ot_distBetPoints,
	ot_equalSegmentLen,
	ot_pointPosReq,
	ot_pointsOnTheOneHand,
	ot_distBetPointSeg,
	ot_distBetPointArc,

	ot_angleBetSeg,
	ot_pointInArc,
	ot_triangle,
	ot_correctTriangle,
	ot_nsAngle,
	ot_correctNsAngle
};

#endif
