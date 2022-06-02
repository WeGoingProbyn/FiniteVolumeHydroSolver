#pragma once

#include "Interpolation.h"
#include "Container.h"

#ifndef ADVECTION_H
#define ADVECTION_H

class Advection {
private:
	Container p_System;
	Interpolation p_Interp;
public:
	Advection();

	double GetAdvectionI();
	double GetAdvectionJ();
	
	void SetSystem(Container& Container);
	void SetInterpolation(Interpolation& Interp);
};

#endif
