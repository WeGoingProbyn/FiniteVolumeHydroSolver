#pragma once

#include "Field.h"

#include <iostream>

#ifndef UTIL_H
#define UTIL_H

struct vec4 {
	double x, y, v, w;
	vec4() : x(0.0), y(0.0), v(0.0), w(0.0) {}
	vec4(double x, double y, double v, double w) : x(x), y(y), v(v), w(w) {}
};

#endif

