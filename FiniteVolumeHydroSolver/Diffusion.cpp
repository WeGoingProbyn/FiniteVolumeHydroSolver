#include "Diffusion.h"

Diffusion::Diffusion() : p_System(Container()) {}

void Diffusion::SetContainer(Container& Container) { p_System = Container; }

double Diffusion::GetDiffusionI(int& i, int& j) {
	int k = i + 1;
	double CompareEast = -2 * 
		p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldI()->GetPoint(k, j)->GetVar() - 
			p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar()) / 
			p_System.GetDifferenceI();
	k = i - 1;
	double CompareWest = -2 *
		p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar() -
			p_System.GetMomentumFieldI()->GetPoint(k, j)->GetVar()) /
			p_System.GetDifferenceI();
	int v = i - 1;
	k = j + 1;
	double CompareNorth = 
		- p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldI()->GetPoint(i, k)->GetVar() - 
			p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar()) /
		p_System.GetDifferenceJ() - 
		p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldJ()->GetPoint(i, k)->GetVar() - 
			p_System.GetMomentumFieldJ()->GetPoint(v, k)->GetVar()) / 
		p_System.GetDifferenceI();
	k = j - 1;
	double CompareSouth =
		- p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar() -
			p_System.GetMomentumFieldI()->GetPoint(i, k)->GetVar()) /
		p_System.GetDifferenceJ() -
		p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar() -
			p_System.GetMomentumFieldJ()->GetPoint(v, j)->GetVar()) /
		p_System.GetDifferenceI();
	return (CompareEast - CompareWest) / p_System.GetDifferenceI() + 
		(CompareNorth - CompareSouth) / p_System.GetDifferenceJ();
}

double Diffusion::GetDiffusionJ(int& i, int& j) {
	int v = i + 1;
	int k = j - 1;
	double CompareEast = 
		-p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldJ()->GetPoint(v, j)->GetVar() -
			p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar()) /
		p_System.GetDifferenceI() -
		p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldI()->GetPoint(v, j)->GetVar() -
			p_System.GetMomentumFieldI()->GetPoint(v, k)->GetVar()) /
		p_System.GetDifferenceJ();
	v = i - 1;
	double CompareWest = 
		-p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar() -
			p_System.GetMomentumFieldJ()->GetPoint(v, j)->GetVar()) /
		p_System.GetDifferenceI() -
		p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar() -
			p_System.GetMomentumFieldI()->GetPoint(i, k)->GetVar()) /
		p_System.GetDifferenceJ();
	k = j + 1;
	double CompareNorth = - 2 *
		p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldJ()->GetPoint(i, k)->GetVar() -
			p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar()) /
			p_System.GetDifferenceJ();
	k = j - 1;
	double CompareSouth = -2 *
		p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar() -
			p_System.GetMomentumFieldJ()->GetPoint(i, k)->GetVar()) /
		p_System.GetDifferenceJ();
	return (CompareNorth - CompareSouth) / p_System.GetDifferenceJ() +
		(CompareEast - CompareWest) / p_System.GetDifferenceI();
}

double Diffusion::GetDiffusionI(int& i, int& j, double& var) {
	int k = i + 1;
	double CompareEast = -2 *
		p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldI()->GetPoint(k, j)->GetVar() -
			p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar()) /
		p_System.GetDifferenceI();
	k = i - 1;
	double CompareWest = -2 *
		p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar() -
			p_System.GetMomentumFieldI()->GetPoint(k, j)->GetVar()) /
		p_System.GetDifferenceI();
	int v = i - 1;
	if (j == 0) {
		k = j + 1;
	double CompareNorth =
		-p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldI()->GetPoint(i, k)->GetVar() -
			p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar()) /
		p_System.GetDifferenceJ() -
		p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldJ()->GetPoint(i, k)->GetVar() -
			p_System.GetMomentumFieldJ()->GetPoint(v, k)->GetVar()) /
		p_System.GetDifferenceI();
	double CompareSouth =
		-p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar() -
			var) / (p_System.GetDifferenceJ() / 2) -
		p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar() -
			p_System.GetMomentumFieldJ()->GetPoint(v, j)->GetVar()) /
		p_System.GetDifferenceI();
	return (CompareEast - CompareWest) / p_System.GetDifferenceI() +
		(CompareNorth - CompareSouth) / p_System.GetDifferenceJ();
	}
	else if (j == p_System.GetPressureField()->GetDimensionSizeJ() - 1) {
		k = j + 1;
		double CompareNorth =
			-p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
			(var - p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar()) /
			p_System.GetDifferenceJ() -
			p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
			(p_System.GetMomentumFieldJ()->GetPoint(i, k)->GetVar() -
				p_System.GetMomentumFieldJ()->GetPoint(v, k)->GetVar()) /
			p_System.GetDifferenceI();
		k = j - 1;
		double CompareSouth =
			-p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
			(p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar() -
				p_System.GetMomentumFieldI()->GetPoint(i, k)->GetVar()) /
			p_System.GetDifferenceJ() -
			p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
			(p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar() -
				p_System.GetMomentumFieldJ()->GetPoint(v, j)->GetVar()) /
			p_System.GetDifferenceI();
		return (CompareEast - CompareWest) / p_System.GetDifferenceI() +
			(CompareNorth - CompareSouth) / p_System.GetDifferenceJ();
	}
	return NULL;
}

double Diffusion::GetDiffusionJ(int& i, int& j, double& var) {
	int v = i + 1;
	int k = j + 1;
	double CompareNorth = -2 *
		p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldJ()->GetPoint(i, k)->GetVar() -
			p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar()) /
		p_System.GetDifferenceJ();
	k = j - 1;
	double CompareSouth = -2 *
		p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
		(p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar() -
			p_System.GetMomentumFieldJ()->GetPoint(i, k)->GetVar()) /
		p_System.GetDifferenceJ();
	if (i == 0) {
		k = j - 1;
		double CompareEast =
			-p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
			(p_System.GetMomentumFieldJ()->GetPoint(v, j)->GetVar() -
				p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar()) /
			p_System.GetDifferenceI() -
			p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
			(p_System.GetMomentumFieldI()->GetPoint(v, j)->GetVar() -
				p_System.GetMomentumFieldI()->GetPoint(v, k)->GetVar()) /
			p_System.GetDifferenceJ();
		v = i - 1;
		double CompareWest =
			-p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
			(p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar() -
				var) /(p_System.GetDifferenceI() / 2) -
			p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
			(p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar() -
				p_System.GetMomentumFieldI()->GetPoint(i, k)->GetVar()) /
			p_System.GetDifferenceJ();
		return (CompareNorth - CompareSouth) / p_System.GetDifferenceJ() +
			(CompareEast - CompareWest) / p_System.GetDifferenceI();
	}
	else if (i == p_System.GetPressureField()->GetDimensionSizeI() - 1) {
		double CompareEast =
			-p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
			(var - p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar()) /
			(p_System.GetDifferenceI() / 2) -
			p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
			(p_System.GetMomentumFieldI()->GetPoint(v, j)->GetVar() -
				p_System.GetMomentumFieldI()->GetPoint(v, k)->GetVar()) /
			p_System.GetDifferenceJ();
		v = i - 1;
		double CompareWest =
			-p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
			(p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar() -
				p_System.GetMomentumFieldJ()->GetPoint(v, j)->GetVar()) /
			p_System.GetDifferenceI() -
			p_System.GetDynamicViscosityField()->GetPoint(i, j)->GetVar() *
			(p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar() -
				p_System.GetMomentumFieldI()->GetPoint(i, k)->GetVar()) /
			p_System.GetDifferenceJ();
		return (CompareNorth - CompareSouth) / p_System.GetDifferenceJ() +
			(CompareEast - CompareWest) / p_System.GetDifferenceI();
	}
	return NULL;
}