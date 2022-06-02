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
	Diffusion p_diffusion;
public:
	Physics();

	Container* GetSystem();
	Interpolation* GetInterpolation();

	void SetSystem(Container& Container);
	void SetInterpolation(Interpolation& Interp);
	void SetAdvection(Advection& Advection);
	void SetDiffusion(Diffusion& Diffusion);
};

#endif