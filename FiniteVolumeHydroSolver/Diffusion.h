#pragma once

#include "Container.h"

#ifndef DIFFUSION_H
#define DIFFUSION_H

class Diffusion {
private:
	Container p_System;
public:
	Diffusion();

	double GetDiffusionI(int& i, int& j);
	double GetDiffusionJ(int& i, int& j);

	double GetDiffusionI(int& i, int& j, double& var);
	double GetDiffusionJ(int& i, int& j, double& var);

	void SetContainer(Container& Container);
};

#endif