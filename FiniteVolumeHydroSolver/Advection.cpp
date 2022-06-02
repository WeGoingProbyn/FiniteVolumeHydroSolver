#include "Advection.h"

Advection::Advection() : p_System(Container()), p_Interp(Interpolation()) {}

double Advection::GetAdvectionI() {
	double CompareI = 
		(p_Interp.GetUInterpolation().InterpEast * 
			p_Interp.GetUInterpolation().InterpEast -
		p_Interp.GetUInterpolation().InterpWest *
			p_Interp.GetUInterpolation().InterpWest) / 
		p_System.GetDifferenceI();
	double CompareJ = 
		(p_Interp.GetUInterpolation().InterpNorth * 
			p_Interp.GetUInterpolation().CrossPlus -
		p_Interp.GetUInterpolation().InterpSouth *
			p_Interp.GetVInterpolation().CrossMinus) / 
		p_System.GetDifferenceJ();
	return -(CompareI + CompareJ);
}

double Advection::GetAdvectionJ() {
	double CompareI = 
		(p_Interp.GetVInterpolation().InterpNorth *
			p_Interp.GetUInterpolation().InterpNorth -
		p_Interp.GetUInterpolation().InterpSouth *
			p_Interp.GetUInterpolation().InterpSouth) / 
		p_System.GetDifferenceJ();
	double CompareJ = 
		(p_Interp.GetVInterpolation().InterpEast *
			p_Interp.GetVInterpolation().CrossPlus -
		p_Interp.GetVInterpolation().InterpWest *
			p_Interp.GetVInterpolation().CrossMinus) / 
		p_System.GetDifferenceI();
	return -(CompareI + CompareJ);
}

void Advection::SetContainer(Container& Container) { p_System = Container; }

void Advection::SetInterpolation(Interpolation& Interp) { p_Interp = Interp; }