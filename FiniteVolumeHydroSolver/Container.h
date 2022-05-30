#pragma once

#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>

#include "Util.h"
#include "Field.h"
#include "SystemVariables.h"

#ifndef CONTAINER_H
#define CONTAINER_H

class Container {
private:

	int  SimSteps;
	double dt, di, dj, BoxScale, TrueTime;

	// TODO: Consider compressible case:
	//		 allow energy field to influence mechanical fields

	//Field Energy;  // <= Not strictly needed but useful for expansion
	Field Density;   // <= to compressible flows. For incompressible flow,
	Field Pressure;  //    density can be constant throughout the field.
	Field MomentumI;
	Field MomentumJ;
	Field InterimMomentumI;
	Field InterimMomentumJ;
	Field DynamicViscosity; // <= a consequence of variable density field.
	SystemVariables SysVars;
public:
	Container();
	~Container();

	Field* GetDensityField();
	Field* GetPressureField();
	Field* GetMomentumFieldI();
	Field* GetMomentumFieldJ();
	Field* GetInterimMomentumFieldI();
	Field* GetInterimMomentumFieldJ();
	Field* GetDynamicViscosityField();
	SystemVariables* GetSysVars();

	double GetDt();
	int GetSimSteps();
	double GetBoxScale();
	double GetTrueTime();
	double GetDifferenceI();
	double GetDifferenceJ();

	void SetDt();
	void SetBoxScale();
	void SetSimSteps();
	void SetTrueTime();
	void SetDifferenceI();
	void SetDifferenceJ();
};

#endif
