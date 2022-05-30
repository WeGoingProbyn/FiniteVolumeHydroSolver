#include "Container.h"

Container::Container() : 
	dt(0.0), BoxScale(0.0), TrueTime(0.0), di(0), dj(0), SimSteps(0) {
	//Energy = Field();
	Density = Field();
	Pressure = Field();
	MomentumI = Field();
	MomentumJ = Field();
	DynamicViscosity = Field();
	SysVars = SystemVariables();
}

Field Container::GetDensityField() { return Density; }

Field Container::GetPressureField() { return Pressure; }

Field Container::GetMomentumFieldI() { return MomentumI; }

Field Container::GetMomentumFieldJ() { return MomentumJ; }

Field Container::GetDynamicViscosityField() { return DynamicViscosity; }

SystemVariables Container::GetSysVars() { return SysVars; }

int Container::GetSimSteps() { return SimSteps; }

int Container::GetDifferenceI() { return di; }

int Container::GetDifferenceJ() { return dj; }

double Container::GetBoxScale() { return BoxScale; }

double Container::GetTrueTime() { return TrueTime; }

double Container::GetDt() { return dt; }

void Container::SetDifferenceI() {
	int ni = Pressure.GetDimensionSizeI() - 1;
	std::vector<double> X = std::vector<double>(ni);
	std::generate_n(std::begin(X), ni, [n = 0, &ni]() mutable { return n++ / ni; });
	di = X[1] - X[0];
}

void Container::SetDifferenceJ() {
	int nj = Pressure.GetDimensionSizeJ() - 1;
	std::vector<double> Y = std::vector<double>(nj);
	std::generate_n(std::begin(Y), nj, [n = 0, &nj]() mutable { return n++ / nj; });
	dj = Y[1] - Y[0];
}

void Container::SetBoxScale() {
	BoxScale = (double)Pressure.GetDimensionSizeI() + (double)Pressure.GetDimensionSizeJ();
	std::vector<double> Velocities = { SysVars.GetDirchletVelocity().x, SysVars.GetDirchletVelocity().y, SysVars.GetDirchletVelocity().v, SysVars.GetDirchletVelocity().w };
	BoxScale /= (2 / *std::max_element(std::begin(Velocities), std::end(Velocities)));
}

void Container::SetTrueTime() { TrueTime = BoxScale * SysVars.GetMaxTime();}

void Container::SetDt() {
	std::vector<int> tmp = { di, dj };
	std::vector<double> Velocities = { SysVars.GetDirchletVelocity().x, SysVars.GetDirchletVelocity().y, SysVars.GetDirchletVelocity().v, SysVars.GetDirchletVelocity().w };
	dt = SysVars.GetCfl() * *std::min_element(std::begin(tmp), std::end(tmp)) / *std::max_element(std::begin(Velocities), std::end(Velocities));
}

void Container::SetSimSteps() { SimSteps = TrueTime / dt; dt = TrueTime / (int)SimSteps; }