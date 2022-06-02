#include <iostream>
#include "Container.h"

int main() {
	Container tmp = Container();
	int ni = 3;
	double nx = 1;
	double Re = 100;
	double Cfl = 0.5;
	double MaxTime = (60); // Seconds
	double Tolerance = 1e-8;
	vec4 Velocities = vec4(1., 0., 0., 0.);

	tmp.GetSysVars()->SetSizeX(nx);
	tmp.GetSysVars()->SetSizeY(nx);
	tmp.GetSysVars()->SetRe(Re);
	tmp.GetSysVars()->SetCfl(Cfl);
	tmp.GetSysVars()->SetMaxTime(MaxTime);
	tmp.GetSysVars()->SetTolerance(Tolerance);
	tmp.GetSysVars()->SetDirchletVelocity(Velocities);

	tmp.BuildFields(ni, ni);

	tmp.GetDynamicViscosityField()->FieldToConsoleOutput();

	tmp.SetBoxScale();
	tmp.SetTrueTime();
	tmp.SetDt();
	tmp.SetSimSteps();

	tmp.DestroyPoints();
}