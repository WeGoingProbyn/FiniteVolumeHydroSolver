#include "SpatialVariables.h"

SpatialVariables::SpatialVariables() : nx(0), ny(0), di(0), dj(0) {}

int SpatialVariables::GetContainerSizeI() { return nx; }

int SpatialVariables::GetContainerSizeJ() { return ny; }

int SpatialVariables::GetDifferenceI() { return di; }

int SpatialVariables::GetDifferenceJ() { return dj; }

void SpatialVariables::SetContainerSizeI(int& nx) { nx = nx; }

void SpatialVariables::SetContainerSizeI(int& nx) { ny = ny; }