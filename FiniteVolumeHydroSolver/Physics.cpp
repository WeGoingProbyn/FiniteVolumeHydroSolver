#include "Physics.h"

Physics::Physics() : 
	p_System(Container()), p_Advection(Advection()), p_Diffusion(Diffusion()), p_Interp(Interpolation()) {

}

Advection* Physics::GetAdvection() { return &p_Advection; }

Diffusion* Physics::GetDiffusion() { return &p_Diffusion; }

Interpolation* Physics::GetInterpolation() { return &p_Interp; }

void Physics::SetContainer(Container& Container) {
	p_System = Container;
	p_Interp.SetContainer(p_System);
	p_Advection.SetContainer(p_System);
	p_Diffusion.SetContainer(p_System);
}

void Physics::SetAdvection(Advection& Advection) { p_Advection = Advection; }

void Physics::SetDiffusion(Diffusion& Diffusion) { p_Diffusion = Diffusion; }

void Physics::SetInterpolation(Interpolation& Interp) { p_Interp = Interp; }

void Physics::ComputeInterimMomentumI() {
	double Diffusion;
	vec4 BoundaryI = p_System.GetSysVars()->GetVelocityBoundariesI();

	for (int j = 0; j < p_System.GetMomentumFieldI()->GetDimensionSizeJ(); j++) {
		for (int i = 1; i < p_System.GetMomentumFieldI()->GetDimensionSizeI(); i++) {
			p_Interp.SetUInterpolationEast(i, j);
			p_Interp.SetUInterpolationWest(i, j);
			p_Interp.SetUInterpolationCrossPlus(i, j);
			p_Interp.SetUInterpolationCrossMinus(i, j);

			if (j == 0) {
				Diffusion = p_Diffusion.GetDiffusionI(i, j, BoundaryI.n);
				p_Interp.SetUInterpolationNorth(i, j, BoundaryI.n);
				p_Interp.SetUInterpolationSouth(i, j);
			}
			else if (j == p_System.GetMomentumFieldI()->GetDimensionSizeJ() - 1) {
				p_Interp.SetUInterpolationNorth(i, j);
				p_Interp.SetUInterpolationSouth(i, j, BoundaryI.s);
				Diffusion = p_Diffusion.GetDiffusionI(i, j, BoundaryI.s);
			}
			else {
				p_Interp.SetUInterpolationNorth(i, j);
				p_Interp.SetUInterpolationSouth(i, j);
				Diffusion = p_Diffusion.GetDiffusionI(i, j);
			}

			p_Advection.SetInterpolation(p_Interp);
			double var = p_Advection.GetAdvectionI() - Diffusion;
			p_System.GetInterimMomentumFieldI()->GetPoint(i, j)->SetVar(var);
		}
	}
}

void Physics::ComputeInterimMomentumJ() {
	double Diffusion;
	vec4 BoundaryJ = p_System.GetSysVars()->GetVelocityBoundariesJ();

	for (int j = 1; j < p_System.GetMomentumFieldJ()->GetDimensionSizeJ(); j++) {
		for (int i = 0; i < p_System.GetMomentumFieldJ()->GetDimensionSizeI(); i++) {
			p_Interp.SetVInterpolationNorth(i, j);
			p_Interp.SetVInterpolationSouth(i, j);
			p_Interp.SetVInterpolationCrossPlus(i, j);
			p_Interp.SetVInterpolationCrossMinus(i, j);

			if (i == 0) {
				Diffusion = p_Diffusion.GetDiffusionJ(i, j, BoundaryJ.e);
				p_Interp.SetVInterpolationEast(i, j, BoundaryJ.e);
				p_Interp.SetVInterpolationWest(i, j);
			}
			else if (i == p_System.GetMomentumFieldJ()->GetDimensionSizeI() - 1) {
				p_Interp.SetVInterpolationEast(i, j);
				p_Interp.SetVInterpolationWest(i, j, BoundaryJ.w);
				Diffusion = p_Diffusion.GetDiffusionJ(i, j, BoundaryJ.w);
			}
			else {
				p_Interp.SetVInterpolationEast(i, j);
				p_Interp.SetVInterpolationWest(i, j);
				Diffusion = p_Diffusion.GetDiffusionJ(i, j);
			}

			p_Advection.SetInterpolation(p_Interp);
			double var = p_Advection.GetAdvectionJ() - Diffusion;
			p_System.GetInterimMomentumFieldJ()->GetPoint(i, j)->SetVar(var);
		}
	}
}