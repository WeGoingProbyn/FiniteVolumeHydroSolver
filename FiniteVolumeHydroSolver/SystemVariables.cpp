#include "SystemVariables.h"

SystemVariables::SystemVariables() :
	p_nx(0.0), p_ny(0.0), p_Re(0.0), p_Cfl(0.0), p_MaxTime(0.0), p_Tolerance(0.0), p_DirchletVelocity(vec4()) {}

double SystemVariables::GetSizeX() { return p_nx; }

double SystemVariables::GetSizeY() { return p_ny; }

double SystemVariables::GetRe() { return p_Re; }

double SystemVariables::GetCfl() { return p_Cfl; }

double SystemVariables::GetMaxTime() { return p_MaxTime; }

double SystemVariables::GetTolerance() { return p_Tolerance; }

vec4 SystemVariables::GetDirchletVelocity() { return p_DirchletVelocity; }

void SystemVariables::SetSizeX(double& nx) { p_nx = nx; }

void SystemVariables::SetSizeY(double& ny) { p_ny = ny; }

void SystemVariables::SetRe(double& Re) { p_Re = Re; }

void SystemVariables::SetCfl(double& Cfl) { p_Cfl = Cfl; }

void SystemVariables::SetMaxTime(double& MaxTime) { p_MaxTime = MaxTime; }

void SystemVariables::SetTolerance(double& Tolerance) { p_Tolerance = Tolerance; }

void SystemVariables::SetDirchletVelocity(vec4& DirchletVelocity) { p_DirchletVelocity = DirchletVelocity; }
