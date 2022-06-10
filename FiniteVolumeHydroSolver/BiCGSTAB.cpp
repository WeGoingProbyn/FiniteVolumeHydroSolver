#include "BiCGSTAB.h"

BiCGSTAB::BiCGSTAB() {
	p_Combined = Field();
	p_Residual = Field();
	p_Residual0 = Field();
	p_Guess = Field();
	p_Interim1 = Field();
	p_Interim2 = Field();
	p_Interim3 = Field();
	p_Interim4 = Field();

	p_Combined.AllocateMemory();
	p_Residual.AllocateMemory();
	p_Residual0.AllocateMemory();
	p_Guess.AllocateMemory();
	p_Interim1.AllocateMemory();
	p_Interim2.AllocateMemory();
	p_Interim3.AllocateMemory();
	p_Interim4.AllocateMemory();
}

void BiCGSTAB::DestroyPoints() {
	p_Combined.DestroyMemory();
	p_Residual.DestroyMemory();
	p_Residual0.DestroyMemory();
	p_Guess.DestroyMemory();
	p_Interim1.DestroyMemory();
	p_Interim2.DestroyMemory();
	p_Interim3.DestroyMemory();
	p_Interim4.DestroyMemory();
}

void BiCGSTAB::SetFieldDimensions() {
	int ni = this->GetContainer()->GetPressureField()->GetTotal();
	int nj = 1;

	p_Combined.SetDimensionSizeI(ni);
	p_Combined.SetDimensionSizeJ(nj);

	p_Residual.SetDimensionSizeI(ni);
	p_Residual.SetDimensionSizeJ(nj);

	p_Residual0.SetDimensionSizeI(ni);
	p_Residual0.SetDimensionSizeJ(nj);

	p_Guess.SetDimensionSizeI(ni);
	p_Guess.SetDimensionSizeJ(nj);

	p_Interim1.SetDimensionSizeI(ni);
	p_Interim1.SetDimensionSizeJ(nj);

	p_Interim2.SetDimensionSizeI(ni);
	p_Interim2.SetDimensionSizeJ(nj);

	p_Interim3.SetDimensionSizeI(ni);
	p_Interim3.SetDimensionSizeJ(nj);

	p_Interim4.SetDimensionSizeI(ni);
	p_Interim4.SetDimensionSizeJ(nj);
}


Field* BiCGSTAB::GetCombined() { return &p_Combined; }
Field* BiCGSTAB::GetResidual() { return &p_Residual; }
Field* BiCGSTAB::GetResidual0() { return &p_Residual0; }
Field* BiCGSTAB::GetGuess() { return &p_Guess; }
Field* BiCGSTAB::GetInterim1() { return &p_Interim1; }
Field* BiCGSTAB::GetInterim2() { return &p_Interim2; }
Field* BiCGSTAB::GetInterim3() { return &p_Interim3; }
Field* BiCGSTAB::GetInterim4() { return &p_Interim4; }

void BiCGSTAB::CombineVectorAndElementsA(Field& Vector, Field& Resultant) {
	int j = 0;
	for (int index = 0; index < Vector.GetDimensionSizeI(); index++) {
		double var = GetElementA()->GetPoint(index)->GetVar();
		Point point = Point(var);
		point.SetIndexI(index);
		point.SetIndexJ(j);
		Resultant.SetPoint(point, index);
	}
	for (int index = 0; index < Vector.GetDimensionSizeI() - 1; index++) {
		double var = Resultant.GetPoint(index)->GetVar();
		var += GetElementAip()->GetPoint(index)->GetVar();
		Resultant.GetPoint(index)->SetVar(var);
	}

	for (int index = 1; index < Vector.GetDimensionSizeI(); index++) {
		double var = Resultant.GetPoint(index)->GetVar();
		var += GetElementAjp()->GetPoint(index)->GetVar();
		Resultant.GetPoint(index)->SetVar(var);
	}

	for (int index = 0; index < GetContainer()->GetPressureField()->GetDimensionSizeI(); index++) {
		double var = Resultant.GetPoint(index)->GetVar();
		var += GetElementAjp()->GetPoint(index)->GetVar();
		Resultant.GetPoint(index)->SetVar(var);
	}

	for (int index = 0; index < GetContainer()->GetPressureField()->GetTotal() - GetContainer()->GetPressureField()->GetDimensionSizeI(); index++) {
		double var = Resultant.GetPoint(index)->GetVar();
		var += GetElementAjm()->GetPoint(index)->GetVar();
		Resultant.GetPoint(index)->SetVar(var);
	}
	for (int index = 0; index < GetContainer()->GetPressureField()->GetTotal(); index++) {
		double var = Resultant.GetPoint(index)->GetVar() * Vector.GetPoint(index)->GetVar();
		Resultant.GetPoint(index)->SetVar(var);
	}
}

double BiCGSTAB::FindDotProduct(Field& VectorA, Field& VectorB) {
	double var = 0;
	for (int index = 0; index < VectorA.GetDimensionSizeI(); index++) {
		var += VectorA.GetPoint(index)->GetVar() * VectorB.GetPoint(index)->GetVar();
	}
	return var;
}

void BiCGSTAB::Solve() {
	double rho, rhoTilde, alpha, beta, omega;
	for (int index = 0; index < GetVectorB()->GetDimensionSizeI(); index++) {
		int i = index % GetVectorB()->GetDimensionSizeI();
		int j = 0;
		double var = 0;
		double var1 = 1;
		Point point = Point(var1);
		Point point1 = Point(var);
		Point point2 = Point(var);
		Point point3 = Point(var);
		point.SetIndexI(i);
		point.SetIndexJ(j);

		point1.SetIndexI(i);
		point1.SetIndexJ(j);

		point2.SetIndexI(i);
		point2.SetIndexJ(j);

		point3.SetIndexI(i);
		point3.SetIndexJ(j);
		p_Guess.SetPoint(point, index);
		p_Interim1.SetPoint(point1, index);
		p_Interim2.SetPoint(point2, index);
		p_Interim3.SetPoint(point3, index);
	}
	CombineVectorAndElementsA(p_Guess, p_Combined);
	p_Guess.FieldToConsoleOutput();
	p_Combined.FieldToConsoleOutput();
	for (int index = 0; index < GetVectorB()->GetDimensionSizeI(); index++) {
		int i = index % GetVectorB()->GetDimensionSizeI();
		int j = 0;
		double var = GetVectorB()->GetPoint(index)->GetVar() - p_Combined.GetPoint(index)->GetVar();
		Point point = Point(var);
		Point point0 = Point(var);
		point.SetIndexI(i);
		point.SetIndexJ(j);
		point0.SetIndexI(i);
		point0.SetIndexJ(j);
		p_Residual.SetPoint(point, index);
		p_Residual0.SetPoint(point0, index);
	}
	rho = 1.;
	alpha = 1.;
	omega = 1.;
	rhoTilde = FindDotProduct(p_Residual, p_Residual0);

	for (int index = 0; index < 1; index++) {
		beta = (rhoTilde / rho) * (alpha / omega);
		rho = rhoTilde;
		for (int index = 0; index < GetVectorB()->GetDimensionSizeI(); index++) {
			int i = index % GetVectorB()->GetDimensionSizeI();
			int j = 0;
			double var = p_Residual.GetPoint(index)->GetVar() + beta *
				p_Interim1.GetPoint(index)->GetVar() - omega *
				p_Interim2.GetPoint(index)->GetVar();
			Point point = Point(var);
			point.SetIndexI(i);
			point.SetIndexJ(j);
			p_Interim1.SetPoint(point, index);
		}
		CombineVectorAndElementsA(p_Interim1, p_Interim2);
		alpha = rho / FindDotProduct(p_Residual0, p_Interim2);

		for (int index = 0; index < GetVectorB()->GetDimensionSizeI(); index++) {
			int i = index % GetVectorB()->GetDimensionSizeI();
			int j = 0;
			double var = p_Residual.GetPoint(index)->GetVar() - alpha *
				p_Interim2.GetPoint(index)->GetVar();
			Point point = Point(var);
			point.SetIndexI(i);
			point.SetIndexJ(j);
			p_Interim3.SetPoint(point, index);
		}
		CombineVectorAndElementsA(p_Interim3, p_Interim4);
		omega = FindDotProduct(p_Interim4, p_Interim3) / FindDotProduct(p_Interim4, p_Interim4);

		for (int index = 0; index < GetVectorB()->GetDimensionSizeI(); index++) {
			int i = index % GetVectorB()->GetDimensionSizeI();
			int j = 0;
			double var = p_Guess.GetPoint(index)->GetVar() +
				alpha * p_Interim4.GetPoint(index)->GetVar() + omega *
				p_Interim3.GetPoint(index)->GetVar();
			Point point = Point(var);
			point.SetIndexI(i);
			point.SetIndexJ(j);
			p_Guess.SetPoint(point, index);
		}
		for (int index = 0; index < GetVectorB()->GetDimensionSizeI(); index++) {
			int i = index % GetVectorB()->GetDimensionSizeI();
			int j = 0;
			double var = p_Interim3.GetPoint(index)->GetVar() - omega *
				p_Interim4.GetPoint(index)->GetVar();
			Point point = Point(var);
			point.SetIndexI(i);
			point.SetIndexJ(j);
			p_Residual.SetPoint(point, index);
		}
		rhoTilde = -omega * FindDotProduct(p_Residual0, p_Interim4);
	}
}