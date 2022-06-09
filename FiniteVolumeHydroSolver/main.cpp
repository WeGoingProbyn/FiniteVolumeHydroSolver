#include <iostream>
#include "Container.h"
#include "Physics.h"
#include "LinearSolver.h"

int main() {
	Container tmp = Container();
	Physics physics = Physics();
	LinearSolver solver = LinearSolver();

	int ni = 3;
	double nx = 1;
	double Re = 1000;
	double Cfl = 0.5;
	double MaxTime = (60); // Seconds
	double Tolerance = 1e-8;
	vec4 VelocitiesI = vec4(0., 0., 1., 0.);
	vec4 VelocitiesJ = vec4(0., 0., 0., 0.);

	tmp.GetSysVars()->SetSizeX(nx);
	tmp.GetSysVars()->SetSizeY(nx);
	tmp.GetSysVars()->SetRe(Re);
	tmp.GetSysVars()->SetCfl(Cfl);
	tmp.GetSysVars()->SetMaxTime(MaxTime);
	tmp.GetSysVars()->SetTolerance(Tolerance);
	tmp.GetSysVars()->SetVelocityBoundariesI(VelocitiesI);
	tmp.GetSysVars()->SetVelocityBoundariesJ(VelocitiesJ);

	tmp.BuildFields(ni, ni);
	tmp.SetBoundariesI();
	tmp.SetBoundariesJ();

	tmp.GetMomentumFieldI()->FieldToConsoleOutput();
	tmp.GetMomentumFieldJ()->FieldToConsoleOutput();

	tmp.SetBoxScale();
	tmp.SetTrueTime();
	tmp.SetDt();
	tmp.SetSimSteps();

	physics.SetContainer(tmp);

	physics.ComputeInterimMomentumI();
	physics.ComputeInterimMomentumJ();

	tmp.GetInterimMomentumFieldI()->FieldToConsoleOutput();
	tmp.GetInterimMomentumFieldJ()->FieldToConsoleOutput();

	solver.SetContainer(tmp);
	solver.SetFieldDimensions();

	solver.BuildVectorB();
	solver.GetVectorB()->FieldToConsoleOutput();

	solver.BuildElementA();
	solver.GetElementA()->FieldToConsoleOutput();

	solver.BuildElementAip();
	solver.GetElementAip()->FieldToConsoleOutput();

	solver.BuildElementAim();
	solver.GetElementAim()->FieldToConsoleOutput();

	solver.BuildElementAjp();
	solver.GetElementAjp()->FieldToConsoleOutput();

	solver.BuildElementAjm();
	solver.GetElementAjm()->FieldToConsoleOutput();

	solver.CombineVectorBandElemetsA();
	solver.GetCombined()->FieldToConsoleOutput();

	solver.DestroyPoints();
	tmp.DestroyPoints();
}