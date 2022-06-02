#pragma once

#include "Util.h"

#ifndef SYSTEMVARIABLES_H
#define SYSTEMVARIABLES_H

class SystemVariables {
private:
	vec4 p_VelocityBoundariesI, p_VelocityBoundariesJ;
	double p_nx, p_ny, p_Re, p_Cfl, p_MaxTime, p_Tolerance;
public:
	SystemVariables();

	double GetSizeX();
	double GetSizeY();
	double GetRe();
	double GetCfl();
	double GetMaxTime();
	double GetTolerance();
	vec4 GetVelocityBoundariesI();
	vec4 GetVelocityBoundariesJ();
	
	void SetSizeX(double& nx);
	void SetSizeY(double& ny);
	void SetRe(double& Re);
	void SetCfl(double& Cfl);
	void SetMaxTime(double& MaxTime);
	void SetTolerance(double& Tolerance);
	void SetVelocityBoundariesI(vec4& VelocityBoundariesI);
	void SetVelocityBoundariesJ(vec4& VelocityBoundariesJ);
};

#endif