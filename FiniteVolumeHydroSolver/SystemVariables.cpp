#include "SystemVariables.h"

SystemVariables::SystemVariables() :
	nx(0), ny(0), Re(0.0), Tolerance(0.0) {}

int SystemVariables::GetSizeX() { return nx; }

int SystemVariables::GetSizeY() { return ny; }

double SystemVariables::GetRe() { return Re; }

double SystemVariables::GetTolerance() { return Tolerance; }

void SystemVariables::SetSizeX(int& nx) { nx = nx; }

void SystemVariables::SetSizeY(int& ny) { ny = ny; }

void SystemVariables::SetRe(double& Re) { Re = Re; }

void SystemVariables::SetTolerance(double& Tolerance) { Tolerance = Tolerance; }