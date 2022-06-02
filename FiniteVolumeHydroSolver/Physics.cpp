#include "Physics.h"

Physics::Physics() : p_System(Container()), p_Advection(Advection()), p_Diffusion(Diffusion()), p_Interp(Interpolation()) {}

Advection* Physics::GetAdvection() { return &p_Advection; }

Diffusion* Physics::GetDiffusion() { return &p_Diffusion; }

Interpolation* Physics::GetInterpolation() { return &p_Interp; }

void Physics::SetContainer(Container& Container) { p_System = Container; }

void Physics::SetAdvection(Advection& Advection) { p_Advection = Advection; }

void Physics::SetDiffusion(Diffusion& Diffusion) { p_Diffusion = Diffusion; }

void Physics::SetInterpolation(Interpolation& Interp) { p_Interp = Interp; }

void Physics::ComputeInterimMomentum() {
	double var;
	p_Advection.SetContainer(p_System);
	p_Diffusion.SetContainer(p_System);
	Field MomentumI = *p_System.GetMomentumFieldI();
	Field MomentumJ = *p_System.GetMomentumFieldJ();
	p_Interp.SetMomentumFields(MomentumI, MomentumJ);
	vec4 BoundaryI = p_System.GetSysVars()->GetVelocityBoundariesI();
	vec4 BoundaryJ = p_System.GetSysVars()->GetVelocityBoundariesJ();
	int CompareI = p_System.GetMomentumFieldI()->GetDimensionSizeJ() - 1;
	int CompareJ = p_System.GetMomentumFieldJ()->GetDimensionSizeI() - 1;

	for (int j = 0; j < p_System.GetMomentumFieldI()->GetDimensionSizeJ(); j++) {
		for (int i = 1; i < p_System.GetMomentumFieldI()->GetDimensionSizeI(); i++) {
			p_Interp.SetUInterpolationEast(i, j);
			p_Interp.SetUInterpolationWest(i, j);
			p_Interp.SetUInterpolationCrossPlus(i, j);
			p_Interp.SetUInterpolationCrossMinus(i, j);

			if (j == 0) { 
				p_Interp.SetUInterpolationNorth(i, j, BoundaryI.n);
				p_Interp.SetUInterpolationSouth(i, j);
			}
			else if (j == CompareI) {
				p_Interp.SetUInterpolationNorth(i, j);
				p_Interp.SetUInterpolationSouth(i, j, BoundaryI.s); 
			}
			else {
				p_Interp.SetUInterpolationNorth(i, j);
				p_Interp.SetUInterpolationSouth(i, j);
			}

			p_Advection.SetInterpolation(p_Interp);
			double var = p_Advection.GetAdvectionI() - p_Diffusion.GetDiffusionI(i, j);
			p_System.GetInterimMomentumFieldI()->GetPoint(i, j)->SetVar(var);
		}
	}
	for (int j = 1; j < p_System.GetMomentumFieldJ()->GetDimensionSizeJ(); j++) {
		for (int i = 0; i < p_System.GetMomentumFieldJ()->GetDimensionSizeI(); i++) {
			p_Interp.SetVInterpolationNorth(i, j);
			p_Interp.SetVInterpolationSouth(i, j);
			p_Interp.SetVInterpolationCrossPlus(i, j);
			p_Interp.SetVInterpolationCrossMinus(i, j);

			if (i == 0) { 
				p_Interp.SetUInterpolationEast(i, j, BoundaryI.e); 
				p_Interp.SetVInterpolationWest(i, j);
			}
			else if (i == CompareJ) { 
				p_Interp.SetVInterpolationEast(i, j);
				p_Interp.SetUInterpolationWest(i, j, BoundaryI.w); 
			}
			else {
				p_Interp.SetVInterpolationEast(i, j);
				p_Interp.SetVInterpolationWest(i, j);
			}
			
			p_Advection.SetInterpolation(p_Interp);
			double var = p_Advection.GetAdvectionJ() - p_Diffusion.GetDiffusionJ(i, j);
			p_System.GetInterimMomentumFieldJ()->GetPoint(i, j)->SetVar(var);
		}
	}
}