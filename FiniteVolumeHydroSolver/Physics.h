#pragma once

#include "Advection.h"
#include "Container.h"
#include "Diffusion.h"
#include "Interpolation.h"

#ifndef PHYSICS_H
#define PHYSICS_H

class Physics {
private:
	Container p_System;
	Interpolation  p_Interp;
	Advection p_Advection;
	Diffusion p_Diffusion;
public:
	Physics();

	Advection* GetAdvection();
	Diffusion* GetDiffusion();
	Interpolation* GetInterpolation();

	void SetContainer(Container& Container);
	void SetAdvection(Advection& Advection);
	void SetDiffusion(Diffusion& Diffusion);
	void SetInterpolation(Interpolation& Interp);

	void ComputeInterimMomentumI();
	void ComputeInterimMomentumJ();
};

#endif