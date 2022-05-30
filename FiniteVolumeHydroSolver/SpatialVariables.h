#pragma once

#ifndef SPATIALVARIABLES_H
#define SPATIALVARIABLES_H

class SpatialVariables {
private:
	int nx, ny, di, dj;
public:
	SpatialVariables();

	int GetContainerSizeI();
	int GetContainerSizeJ();
	int GetDifferenceI();
	int GetDifferenceJ();

	void SetDifferenceI();
	void SetDifferenceJ();
	void SetContainerSizeI(int &nx);
	void SetContainerSizeJ(int &ny);
};

#endif