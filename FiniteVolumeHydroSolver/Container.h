#pragma once

#include "Field.h"
#include "SystemVariables.h"
#include "TemporalVariables.h"

#ifndef CONTAINER_H
#define CONTAINER_H

class Container {
private:
	double Nu, BoxScale;
	int di, dj, SimSteps;
	
	// TODO: Consider compressible case:
	//		 allow energy field to influence mechanical fields

	//Field Energy;  // <= Not strictly needed but useful for expansion
	Field Density;   // <= to compressible flows. For incompressible flow,
	Field Pressure;  //    density can be constant throughout the field.
	Field MomentumI;
	Field MomentumJ;
	SystemVariables SysVars;
	TemporalVariables TimeVars;
public:
	Container();

	Field GetDensityField();
	Field GetPressureField();
	Field GetMomentumFieldI();
	Field GetMomentumFieldJ();
	SystemVariables GetSysVars();
	TemporalVariables GetTimeVars();

	double GetNu();
	int GetSimSteps();
	int GetDifferenceI();
	int GetDifferenceJ();
	double GetBoxScale();

	void SetNu();
	void SetBoxScale();
	void SetSimSteps();
	void SetDifferenceI();
	void SetDifferenceJ();
};

#endif
