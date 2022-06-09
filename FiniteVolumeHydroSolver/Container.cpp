#include "Container.h"

Container::Container() : 
	dt(0.0), BoxScale(0.0), TrueTime(0.0), di(0.0), dj(0.0), SimSteps(0) {
	Energy = Field();
	Density = Field();
	Pressure = Field();
	MomentumI = Field();
	MomentumJ = Field();
	InterimMomentumI = Field();
	InterimMomentumJ = Field();
	DynamicViscosity = Field();
	SysVars = SystemVariables();

	Energy.AllocateMemory();
	Density.AllocateMemory();
	Pressure.AllocateMemory();
	MomentumI.AllocateMemory();
	MomentumJ.AllocateMemory();
	InterimMomentumI.AllocateMemory();
	InterimMomentumJ.AllocateMemory();
	DynamicViscosity.AllocateMemory();
}

void Container::DestroyPoints() {
	Energy.DestroyMemory();
	Density.DestroyMemory();
	Pressure.DestroyMemory();
	MomentumI.DestroyMemory();
	MomentumJ.DestroyMemory();
	InterimMomentumI.DestroyMemory();
	InterimMomentumJ.DestroyMemory();
	DynamicViscosity.DestroyMemory();
}

void Container::BuildFields(int& ni, int& nj) {
	Energy.SetDimensionSizeI(ni);
	Energy.SetDimensionSizeJ(nj);

	Density.SetDimensionSizeI(ni);
	Density.SetDimensionSizeJ(nj);

	Pressure.SetDimensionSizeI(ni);
	Pressure.SetDimensionSizeJ(nj);

	int tmpI1 = ni + 1;
	int tmpJ1 = nj + 1;
	int tmpI2 = ni + 2;
	int tmpJ2 = ni + 2;

	MomentumI.SetDimensionSizeI(tmpI2);
	MomentumI.SetDimensionSizeJ(tmpJ1);

	MomentumJ.SetDimensionSizeI(tmpI1);
	MomentumJ.SetDimensionSizeJ(tmpJ2);

	InterimMomentumI.SetDimensionSizeI(tmpI2);
	InterimMomentumI.SetDimensionSizeJ(tmpJ1);

	InterimMomentumJ.SetDimensionSizeI(tmpI1);
	InterimMomentumJ.SetDimensionSizeJ(tmpJ2);

	DynamicViscosity.SetDimensionSizeI(ni);
	DynamicViscosity.SetDimensionSizeJ(nj);

	this->SetDifferenceI();
	this->SetDifferenceJ();

	std::vector<double> Velocities = { SysVars.GetVelocityBoundariesI().e, 
		SysVars.GetVelocityBoundariesI().w, SysVars.GetVelocityBoundariesI().n, 
		SysVars.GetVelocityBoundariesI().s, SysVars.GetVelocityBoundariesJ().e, 
		SysVars.GetVelocityBoundariesJ().w, SysVars.GetVelocityBoundariesJ().n, 
		SysVars.GetVelocityBoundariesJ().s };
	double varDensity = 1;
	double var = 0;
	double varNu;
	for (int index = 0; index < Pressure.GetTotal(); index++) {
		Energy.BuildField(index, var);
		Density.BuildField(index, varDensity);
		Pressure.BuildField(index, var);
		varNu = *std::max_element(std::begin(Velocities), std::end(Velocities)) * 
			(dj * ni * Density.GetPoint(index)->GetVar()) / SysVars.GetRe();
		DynamicViscosity.BuildField(index, varNu);
	}
	for (int index = 0; index < MomentumI.GetTotal(); index++) {
		MomentumI.BuildField(index, var);
		MomentumJ.BuildField(index, var);
		InterimMomentumI.BuildField(index, var);
		InterimMomentumJ.BuildField(index, var);   // This would need to be updated
	}											   // outisde this function
}												   // for compressible flow 

void Container::SetBoundariesI() {
	int i = 0;
	int j = 0;
	int endI = this->GetMomentumFieldI()->GetDimensionSizeI() - 1;
	int endJ = this->GetMomentumFieldI()->GetDimensionSizeJ() - 1;
	vec4 var = this->GetSysVars()->GetVelocityBoundariesI();
	for (int j = 0; j < this->GetMomentumFieldI()->GetDimensionSizeJ(); j++) {
		this->GetMomentumFieldI()->GetPoint(i, j)->SetVar(var.e);
		this->GetInterimMomentumFieldI()->GetPoint(i, j)->SetVar(var.e);

		this->GetMomentumFieldI()->GetPoint(endI, j)->SetVar(var.w);
		this->GetInterimMomentumFieldI()->GetPoint(endI, j)->SetVar(var.w);
	}
	j = 0;
	for (int i = 0; i < this->GetMomentumFieldJ()->GetDimensionSizeI(); i++) {
		this->GetMomentumFieldI()->GetPoint(i, j)->SetVar(var.n);
		this->GetInterimMomentumFieldI()->GetPoint(i, j)->SetVar(var.n);

		this->GetMomentumFieldI()->GetPoint(i, endJ)->SetVar(var.s);
		this->GetInterimMomentumFieldI()->GetPoint(i, endJ)->SetVar(var.s);
	}
}

void Container::SetBoundariesJ() {
	int j = 0;
	int i = 0;
	int endJ = this->GetMomentumFieldJ()->GetDimensionSizeJ() - 1;
	int endI = this->GetMomentumFieldJ()->GetDimensionSizeI() - 1;
	vec4 var = this->GetSysVars()->GetVelocityBoundariesJ();
	for (int i = 0; i < this->GetMomentumFieldJ()->GetDimensionSizeI(); i++) {
		this->GetMomentumFieldJ()->GetPoint(i, j)->SetVar(var.n);
		this->GetInterimMomentumFieldJ()->GetPoint(i, j)->SetVar(var.n);

		this->GetMomentumFieldJ()->GetPoint(i, endJ)->SetVar(var.s);
		this->GetInterimMomentumFieldJ()->GetPoint(i, endJ)->SetVar(var.s);
	}
	i = 0;
	for (int j = 0; j < this->GetMomentumFieldI()->GetDimensionSizeJ(); j++) {
		this->GetMomentumFieldJ()->GetPoint(i, j)->SetVar(var.e);
		this->GetInterimMomentumFieldJ()->GetPoint(i, j)->SetVar(var.e);

		this->GetMomentumFieldJ()->GetPoint(endI, j)->SetVar(var.w);
		this->GetInterimMomentumFieldJ()->GetPoint(endI, j)->SetVar(var.w);
	}
}

Field* Container::GetEnergyField() { return &Energy; }

Field* Container::GetDensityField() { return &Density; }

Field* Container::GetPressureField() { return &Pressure; }

Field* Container::GetMomentumFieldI() { return &MomentumI; }

Field* Container::GetMomentumFieldJ() { return &MomentumJ; }

Field* Container::GetInterimMomentumFieldI() { return &InterimMomentumI; }

Field* Container::GetInterimMomentumFieldJ() { return &InterimMomentumJ; }

Field* Container::GetDynamicViscosityField() { return &DynamicViscosity; }

SystemVariables* Container::GetSysVars() { return &SysVars; }

int Container::GetSimSteps() { return SimSteps; }

double Container::GetDifferenceI() { return di; }

double Container::GetDifferenceJ() { return dj; }

double Container::GetBoxScale() { return BoxScale; }

double Container::GetTrueTime() { return TrueTime; }

double Container::GetDt() { return dt; }

void Container::SetDifferenceI() {
	int ni = Pressure.GetDimensionSizeI();
	double tmp = (double)ni;
	std::vector<double> X = std::vector<double>(ni);
	std::generate_n(std::begin(X), ni, [n = 0, &tmp]() mutable { return n++ / tmp; });
	di = X[1] - X[0];
}

void Container::SetDifferenceJ() {
	int nj = Pressure.GetDimensionSizeJ();
	double tmp = (double)nj;
	std::vector<double> Y = std::vector<double>(nj);
	std::generate_n(std::begin(Y), nj, [n = 0, &tmp]() mutable { return n++ / tmp; });
	dj = Y[1] - Y[0];
}

void Container::SetBoxScale() {
	BoxScale = SysVars.GetSizeX() + SysVars.GetSizeY();
	std::vector<double> Velocities = { SysVars.GetVelocityBoundariesI().e, 
		SysVars.GetVelocityBoundariesI().w, SysVars.GetVelocityBoundariesI().n, 
		SysVars.GetVelocityBoundariesI().s, SysVars.GetVelocityBoundariesJ().e, 
		SysVars.GetVelocityBoundariesJ().w, SysVars.GetVelocityBoundariesJ().n, 
		SysVars.GetVelocityBoundariesJ().s };
	BoxScale /= (2 / *std::max_element(std::begin(Velocities), std::end(Velocities)));
}

void Container::SetTrueTime() { TrueTime = BoxScale * SysVars.GetMaxTime(); }

void Container::SetDt() {
	std::vector<double> tmp = { GetDifferenceI(), GetDifferenceJ() };
	std::vector<double> Velocities = { SysVars.GetVelocityBoundariesI().e,
		SysVars.GetVelocityBoundariesI().w, SysVars.GetVelocityBoundariesI().n,
		SysVars.GetVelocityBoundariesI().s, SysVars.GetVelocityBoundariesJ().e,
		SysVars.GetVelocityBoundariesJ().w, SysVars.GetVelocityBoundariesJ().n,
		SysVars.GetVelocityBoundariesJ().s };
	dt = SysVars.GetCfl() * *std::min_element(std::begin(tmp), std::end(tmp)) / 
		*std::max_element(std::begin(Velocities), std::end(Velocities));
}

void Container::SetSimSteps() { SimSteps = (int)(TrueTime / dt); dt = TrueTime / SimSteps; }