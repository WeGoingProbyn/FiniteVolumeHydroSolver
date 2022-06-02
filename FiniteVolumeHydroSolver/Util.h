#pragma once

#include "Field.h"

#include <iostream>

#ifndef UTIL_H
#define UTIL_H

struct vec4 {
	double e, w, n, s;
	vec4() : e(0.0), w(0.0), n(0.0), s(0.0) {}
	vec4(double e, double w, double n, double s) : e(e), w(w), n(n), s(s) {}
};

struct vec6 {
	double InterpEast, InterpWest, InterpNorth, InterpSouth, CrossPlus, CrossMinus;
	vec6() : InterpEast(0.0), InterpWest(0.0), InterpNorth(0.0), InterpSouth(0.0), CrossPlus(0.0), CrossMinus(0.0) {}
	vec6(double InterpEast, double InterpWest, double InterpNorth, double InterpSouth, double CrossPlus, double CrossMinus)
		: InterpEast(InterpEast), InterpWest(InterpWest), InterpNorth(InterpNorth), InterpSouth(InterpSouth), CrossPlus(CrossPlus), CrossMinus(CrossMinus) {}
};

#endif

