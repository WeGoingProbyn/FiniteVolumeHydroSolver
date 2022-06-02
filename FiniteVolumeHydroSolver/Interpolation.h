#pragma once

#include "Field.h"
#include "Util.h"

#ifndef INTERPOLATION_H
#define INTERPOLATION_H


class Interpolation {
private:
	vec6 p_uInterp, p_vInterp;
	Field p_MomentumI, p_MomentumJ;
public:
	Interpolation();

	vec6 GetUInterpolation();
	vec6 GetVInterpolation();

	void SetMomentumFields(Field& MomentumI, Field& MomentumJ);

	void SetUInterpolationEast(int& i, int& j);
	void SetUInterpolationWest(int& i, int& j);
	void SetUInterpolationNorth(int& i, int& j);
	void SetUInterpolationSouth(int& i, int& j);
	void SetUInterpolationCrossPlus(int& i, int& j);
	void SetUInterpolationCrossMinus(int& i, int& j);

	void SetUInterpolationEast(int& i, int& j, double& var);
	void SetUInterpolationWest(int& i, int& j, double& var);
	void SetUInterpolationNorth(int& i, int& j, double& var);
	void SetUInterpolationSouth(int& i, int& j, double& var);

	void SetVInterpolationEast(int& i, int& j);
	void SetVInterpolationWest(int& i, int& j);
	void SetVInterpolationNorth(int& i, int& j);
	void SetVInterpolationSouth(int& i, int& j);
	void SetVInterpolationCrossPlus(int& i, int& j);
	void SetVInterpolationCrossMinus(int& i, int& j);

	void SetVInterpolationEast(int& i, int& j, double& var);
	void SetVInterpolationWest(int& i, int& j, double& var);
	void SetVInterpolationNorth(int& i, int& j, double& var);
	void SetVInterpolationSouth(int& i, int& j, double& var);
};

#endif