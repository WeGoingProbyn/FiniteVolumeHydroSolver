#include "Container.h"

Container::Container() : Nu(0.0), BoxScale(0.0), di(0), dj(0), SimSteps(0) {
	SysVars = SystemVariables();
	TimeVars = TemporalVariables();
}

Field Container::GetDensityField() { return Density; }

Field Container::GetPressureField() { return Pressure; }

Field Container::GetMomentumFieldI() { return MomentumI; }

Field Container::GetMomentumFieldJ() { return MomentumJ; }

SystemVariables Container::GetSysVars() { return SysVars; }

TemporalVariables Container::GetTimeVars() { return TimeVars; }

double Container::GetNu() { return Nu; }

int Container::GetSimSteps() { return SimSteps; }

int Container::GetDifferenceI() { return di; }

int Container::GetDifferenceJ() { return dj; }

double Container::GetBoxScale() { return BoxScale; }