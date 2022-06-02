#include "SystemVariables.h"

SystemVariables::SystemVariables() :
	p_nx(0.0), p_ny(0.0), p_Re(0.0), p_Cfl(0.0), p_MaxTime(0.0), 
	p_Tolerance(0.0), p_VelocityBoundariesI(vec4()), p_VelocityBoundariesJ(vec4()) {}

double SystemVariables::GetSizeX() { return p_nx; }

double SystemVariables::GetSizeY() { return p_ny; }

double SystemVariables::GetRe() { return p_Re; }

double SystemVariables::GetCfl() { return p_Cfl; }

double SystemVariables::GetMaxTime() { return p_MaxTime; }

double SystemVariables::GetTolerance() { return p_Tolerance; }

vec4 SystemVariables::GetVelocityBoundariesI() { return p_VelocityBoundariesI; }

vec4 SystemVariables::GetVelocityBoundariesJ() { return p_VelocityBoundariesJ; }

void SystemVariables::SetSizeX(double& nx) { p_nx = nx; }

void SystemVariables::SetSizeY(double& ny) { p_ny = ny; }

void SystemVariables::SetRe(double& Re) { p_Re = Re; }

void SystemVariables::SetCfl(double& Cfl) { p_Cfl = Cfl; }

void SystemVariables::SetMaxTime(double& MaxTime) { p_MaxTime = MaxTime; }

void SystemVariables::SetTolerance(double& Tolerance) { p_Tolerance = Tolerance; }

void SystemVariables::SetVelocityBoundariesI(vec4& VelocityBoundariesI) { p_VelocityBoundariesI = VelocityBoundariesI; }

void SystemVariables::SetVelocityBoundariesJ(vec4& VelocityBoundariesJ) { p_VelocityBoundariesJ = VelocityBoundariesJ; }
