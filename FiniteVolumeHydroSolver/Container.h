#pragma once

#include "Field.h"
#include "SystemVariables.h"
#include "TemporalVariables.h"

#ifndef CONTAINER_H
#define CONTAINER_H

class Container {
private:
	double BoxScale;
	int di, dj, SimSteps;
	
	SystemVariables SysVars;
	TemporalVariables TimeVars;
public:
	Container();

	int GetSimSteps();
	int GetDifferenceI();
	int GetDifferenceJ();
	double GetBoxScale();

	SystemVariables GetSysVars();
	TemporalVariables GetTimeVars();

	void SetBoxScale();
	void SetSimSteps();
	void SetDifferenceI();
	void SetDifferenceJ();
};

#endif
