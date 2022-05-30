#pragma once

#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>

#include "Util.h"
#include "Field.h"
#include "SystemVariables.h"
#include "TemporalVariables.h"

#ifndef CONTAINER_H
#define CONTAINER_H

class Container {
private:

	int di, dj, SimSteps;
	double dt, BoxScale, TrueTime;

	// TODO: Consider compressible case:
	//		 allow energy field to influence mechanical fields

	//Field Energy;  // <= Not strictly needed but useful for expansion
	Field Density;   // <= to compressible flows. For incompressible flow,
	Field Pressure;  //    density can be constant throughout the field.
	Field MomentumI;
	Field MomentumJ;
	Field DynamicViscosity; // <= a consequence of variable density field.
	SystemVariables SysVars;
public:
	Container();

	Field GetDensityField();
	Field GetPressureField();
	Field GetMomentumFieldI();
	Field GetMomentumFieldJ();
	Field GetDynamicViscosityField();
	SystemVariables GetSysVars();

	double GetDt();
	int GetSimSteps();
	int GetDifferenceI();
	int GetDifferenceJ();
	double GetBoxScale();
	double GetTrueTime();

	void SetDt();
	void SetBoxScale();
	void SetSimSteps();
	void SetTrueTime();
	void SetDifferenceI();
	void SetDifferenceJ();
};

#endif
