#pragma once

#include "Util.h"

#ifndef SYSTEMVARIABLES_H
#define SYSTEMVARIABLES_H

class SystemVariables {
private:
	int nx, ny;
	vec4 DirchletVelocity;
	double Re, Cfl, MaxTime, Tolerance;
public:
	SystemVariables();

	int GetSizeX();
	int GetSizeY();
	double GetRe();
	double GetCfl();
	double GetMaxTime();
	double GetTolerance();
	vec4 GetDirchletVelocity();
	
	void SetSizeX(int &nx);
	void SetSizeY(int &ny);
	void SetRe(double &Re);
	void SetCfl(double& Cfl);
	void SetMaxTime(double& MaxTime);
	void SetTolerance(double &Tolerance);
	void SetDirchletVelocity(vec4 &DirchletVelocity);
};

#endif