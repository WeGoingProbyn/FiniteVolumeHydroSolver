#include "TemporalVariables.h"

TemporalVariables::TemporalVariables() :
	dt(0.0), Cfl(0.0), MaxTime(0.0), TrueTime(0.0) {}

double TemporalVariables::GetDt() { return dt; }

double TemporalVariables::GetCfl() { return Cfl; }

double TemporalVariables::GetMaxTime() { return MaxTime; }

double TemporalVariables::GetTrueTime() { return TrueTime; }

void TemporalVariables::SetDt(double& Dt) { dt = dt; }

void TemporalVariables::SetCfl(double& Cfl) { Cfl = Cfl; }

void TemporalVariables::SetMaxTime(double& MaxTime) { MaxTime = MaxTime; }

void TemporalVariables::SetTrueTime(double& TrueTime) { TrueTime = TrueTime; }
