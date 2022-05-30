#include "TemporalVariables.h"

TemporalVariables::TemporalVariables() :
	Dt(0.0), MaxTime(0.0), TrueTime(0.0) {}

double TemporalVariables::GetDt() { return Dt; }

double TemporalVariables::GetMaxTime() { return MaxTime; }

double TemporalVariables::GetTrueTime() { return TrueTime; }

void TemporalVariables::SetDt(double& Dt) { Dt = Dt; }

void TemporalVariables::SetMaxTime(double& MaxTime) { MaxTime = MaxTime; }

void TemporalVariables::SetTrueTime(double& TrueTime) { TrueTime = TrueTime; }
