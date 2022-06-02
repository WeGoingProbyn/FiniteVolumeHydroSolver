#include "Interpolation.h"

Interpolation::Interpolation() : 
	p_MomentumI(Field()), p_MomentumJ(Field()), p_uInterp(vec6()), p_vInterp(vec6()) {}

vec6 Interpolation::GetUInterpolation() { return p_uInterp; }

vec6 Interpolation::GetVInterpolation() { return p_vInterp; }

void Interpolation::SetMomentumFields(Field& MomentumI, Field& MomentumJ) { p_MomentumI = MomentumI, p_MomentumJ = MomentumJ; }

void Interpolation::SetUInterpolationEast(int& i, int& j) {
	int k = i + 1;
	p_uInterp.InterpEast = 0.5 * (p_MomentumI.GetPoint(k, j)->GetVar() + p_MomentumI.GetPoint(i, j)->GetVar());
}

void Interpolation::SetUInterpolationWest(int& i, int& j) {
	int k = i - 1;
	p_uInterp.InterpWest = 0.5 * (p_MomentumI.GetPoint(i, j)->GetVar() + p_MomentumI.GetPoint(k, j)->GetVar());
}

void Interpolation::SetUInterpolationNorth(int& i, int& j) {
	int k = j + 1;
	p_uInterp.InterpNorth = 0.5 * (p_MomentumI.GetPoint(i, k)->GetVar() + p_MomentumI.GetPoint(i, j)->GetVar());
}

void Interpolation::SetUInterpolationSouth(int& i, int& j) {
	int k = j - 1;
	p_uInterp.InterpSouth = 0.5 * (p_MomentumI.GetPoint(i, j)->GetVar() + p_MomentumI.GetPoint(i, k)->GetVar());
}

void Interpolation::SetUInterpolationCrossPlus(int& i, int& j) {
	int k = i - 1;
	int v = j + 1;
	p_uInterp.CrossPlus = 0.5 * (p_MomentumJ.GetPoint(k, v)->GetVar() + p_MomentumJ.GetPoint(i, v)->GetVar());
}

void Interpolation::SetUInterpolationCrossMinus(int& i, int& j) {
	int k = i - 1;
	p_uInterp.CrossMinus = 0.5 * (p_MomentumJ.GetPoint(k, j)->GetVar() + p_MomentumJ.GetPoint(i, j)->GetVar());
}

void Interpolation::SetUInterpolationEast(int& i, int& j, double& var) {
	p_uInterp.InterpEast = var;
}

void Interpolation::SetUInterpolationWest(int& i, int& j, double& var) {
	p_uInterp.InterpWest = var;
}

void Interpolation::SetUInterpolationNorth(int& i, int& j, double& var) {
	p_uInterp.InterpNorth = var;
}

void Interpolation::SetUInterpolationSouth(int& i, int& j, double& var) {
	p_uInterp.InterpSouth = var;
}

void Interpolation::SetVInterpolationEast(int& i, int& j) {
	int k = i + 1;
	p_vInterp.InterpEast = 0.5 * (p_MomentumJ.GetPoint(k, j)->GetVar() + p_MomentumJ.GetPoint(i, j)->GetVar());
}

void Interpolation::SetVInterpolationWest(int& i, int& j) {
	int k = i - 1;
	p_vInterp.InterpWest = 0.5 * (p_MomentumJ.GetPoint(i, j)->GetVar() + p_MomentumJ.GetPoint(k, j)->GetVar());
}

void Interpolation::SetVInterpolationNorth(int& i, int& j) {
	int k = j + 1;
	p_vInterp.InterpNorth = 0.5 * (p_MomentumJ.GetPoint(i, k)->GetVar() + p_MomentumJ.GetPoint(i, j)->GetVar());
}

void Interpolation::SetVInterpolationSouth(int& i, int& j) {
	int k = j + 1;
	p_vInterp.InterpSouth = 0.5 * (p_MomentumJ.GetPoint(i, j)->GetVar() + p_MomentumJ.GetPoint(i, k)->GetVar());
}

void Interpolation::SetVInterpolationCrossPlus(int& i, int& j) {
	int k = i + 1;
	int v = j - 1;
	p_vInterp.CrossPlus = 0.5 * (p_MomentumJ.GetPoint(k, v)->GetVar() + p_MomentumJ.GetPoint(k, j)->GetVar());
}

void Interpolation::SetVInterpolationCrossMinus(int& i, int& j) {
	int k = j - 1;
	p_vInterp.CrossMinus = 0.5 * (p_MomentumJ.GetPoint(i, k)->GetVar() + p_MomentumJ.GetPoint(i, j)->GetVar());
}

void Interpolation::SetVInterpolationEast(int& i, int& j, double& var) {
	p_vInterp.InterpEast = var;
}

void Interpolation::SetVInterpolationWest(int& i, int& j, double& var) {
	p_vInterp.InterpWest = var;
}

void Interpolation::SetVInterpolationNorth(int& i, int& j, double& var) {
	p_vInterp.InterpNorth = var;
}

void Interpolation::SetVInterpolationSouth(int& i, int& j, double& var) {
	p_vInterp.InterpSouth = var;
}