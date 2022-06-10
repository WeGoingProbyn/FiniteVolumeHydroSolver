#include "LinearBuilder.h"

LinearBuilder::LinearBuilder() {}

void LinearBuilder::SetContainer(Container& Container) { p_System = Container; }

Container* LinearBuilder::GetContainer() { return &p_System; }

double LinearBuilder::GetBaseValue() {
	return -p_System.GetDt() * (p_System.GetDifferenceJ() / p_System.GetDifferenceI());
}

double LinearBuilder::GetCornerA() {
	return (p_System.GetDt() * (p_System.GetDifferenceJ() / p_System.GetDifferenceI())) +
		(p_System.GetDt() * (p_System.GetDifferenceI() / p_System.GetDifferenceJ()));
}

double LinearBuilder::GetWallA() {
	return (p_System.GetDt() * (p_System.GetDifferenceJ() / p_System.GetDifferenceI())) +
		(2 * p_System.GetDt() * (p_System.GetDifferenceI() / p_System.GetDifferenceJ()));
}

double LinearBuilder::GetFloorA() {
	return (2 * p_System.GetDt() * (p_System.GetDifferenceJ() / p_System.GetDifferenceI())) +
		(p_System.GetDt() * (p_System.GetDifferenceI() / p_System.GetDifferenceJ()));
}

double LinearBuilder::GetInteriorA() {
	return (2 * p_System.GetDt() * (p_System.GetDifferenceJ() / p_System.GetDifferenceI())) +
		(2 * p_System.GetDt() * (p_System.GetDifferenceI() / p_System.GetDifferenceJ()));
}

double LinearBuilder::GetTopRightB() {
	int i = p_System.GetPressureField()->GetDimensionSizeI() - 1;
	int j = 0;
	int k = i + 1;
	int v = j + 1;
	return -p_System.GetDifferenceJ() * p_System.GetMomentumFieldI()->GetPoint(k, j)->GetVar() +
		p_System.GetDifferenceJ() * (p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar() +
			p_System.GetDt() * p_System.GetInterimMomentumFieldI()->GetPoint(i, j)->GetVar()) -
		p_System.GetDifferenceI() * (p_System.GetMomentumFieldJ()->GetPoint(i, v)->GetVar() +
			p_System.GetDt() * p_System.GetInterimMomentumFieldJ()->GetPoint(i, v)->GetVar()) +
		p_System.GetDifferenceI() * p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar();
}

double LinearBuilder::GetTopLeftB() {
	int i = 0;
	int j = 0;
	int k = i + 1;
	int v = j + 1;
	return -p_System.GetDifferenceJ() * (p_System.GetMomentumFieldI()->GetPoint(k, j)->GetVar() +
		p_System.GetDt() * p_System.GetInterimMomentumFieldI()->GetPoint(k, j)->GetVar()) +
		p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar() - p_System.GetDifferenceI() *
		(p_System.GetMomentumFieldJ()->GetPoint(i, v)->GetVar() + p_System.GetDt() *
			p_System.GetInterimMomentumFieldJ()->GetPoint(i, v)->GetVar()) +
		p_System.GetDifferenceI() * p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar();
}

double LinearBuilder::GetBottomRightB() {
	int i = p_System.GetPressureField()->GetDimensionSizeI() - 1;
	int j = p_System.GetPressureField()->GetDimensionSizeJ() - 1;
	int k = i + 1;
	int v = j + 1;
	return -p_System.GetDifferenceJ() * p_System.GetMomentumFieldI()->GetPoint(k, j)->GetVar() +
		p_System.GetDifferenceJ() * (p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar() +
			p_System.GetDt() * p_System.GetInterimMomentumFieldI()->GetPoint(i, j)->GetVar()) -
		p_System.GetDifferenceI() * p_System.GetMomentumFieldJ()->GetPoint(i, v)->GetVar() +
		p_System.GetDifferenceI() * (p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar() +
			p_System.GetDt() * p_System.GetInterimMomentumFieldJ()->GetPoint(i, j)->GetVar());
}

double LinearBuilder::GetBottomLeftB() {
	int i = 0;
	int j = p_System.GetPressureField()->GetDimensionSizeJ() - 1;
	int k = i + 1;
	int v = j + 1;
	return -p_System.GetDifferenceJ() * (p_System.GetMomentumFieldI()->GetPoint(k, j)->GetVar() + 
			p_System.GetDt() * p_System.GetInterimMomentumFieldI()->GetPoint(k, j)->GetVar()) +
		p_System.GetDifferenceJ() * p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar() -
		p_System.GetDifferenceI() * p_System.GetInterimMomentumFieldI()->GetPoint(i, v)->GetVar() +
		p_System.GetDifferenceI() * (p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar() + 
			p_System.GetDt() * p_System.GetInterimMomentumFieldJ()->GetPoint(i, j)->GetVar());
}

double LinearBuilder::GetTopSideB(int& i) {
	int j = 0;
	int k = i + 1;
	int v = j + 1;
	return -p_System.GetDifferenceJ() * (p_System.GetMomentumFieldI()->GetPoint(k, j)->GetVar() +
			p_System.GetDt() * p_System.GetInterimMomentumFieldI()->GetPoint(k, j)->GetVar()) +
		p_System.GetDifferenceJ() * (p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar() + 
			p_System.GetDt() * p_System.GetInterimMomentumFieldI()->GetPoint(i, j)->GetVar()) -
		p_System.GetDifferenceI() * (p_System.GetMomentumFieldJ()->GetPoint(i, v)->GetVar() + 
			p_System.GetDt() * p_System.GetInterimMomentumFieldJ()->GetPoint(i, v)->GetVar()) +
		p_System.GetDifferenceI() * p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar();
}

double LinearBuilder::GetBottomSideB(int& i) {
	int j = p_System.GetPressureField()->GetDimensionSizeJ() - 1;
	int k = i + 1;
	int v = j + 1;
	return -p_System.GetDifferenceJ() * (p_System.GetMomentumFieldI()->GetPoint(k, j)->GetVar() +
			p_System.GetDt() * p_System.GetInterimMomentumFieldI()->GetPoint(k, j)->GetVar()) +
		p_System.GetDifferenceJ() * (p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar() + 
			p_System.GetDt() * p_System.GetInterimMomentumFieldI()->GetPoint(i, j)->GetVar()) -
		p_System.GetDifferenceI() * p_System.GetMomentumFieldJ()->GetPoint(i, v)->GetVar() +
		p_System.GetDifferenceI() * (p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar() + 
			p_System.GetDt() * p_System.GetInterimMomentumFieldJ()->GetPoint(i, j)->GetVar());
}

double LinearBuilder::GetRightSideB(int& j) {
	int i = p_System.GetPressureField()->GetDimensionSizeI() - 1;
	int k = i + 1;
	int v = j + 1;
	return -p_System.GetDifferenceJ() * p_System.GetMomentumFieldI()->GetPoint(k, j)->GetVar() +
		p_System.GetDifferenceJ() * (p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar() + 
			p_System.GetDt() * p_System.GetInterimMomentumFieldI()->GetPoint(i, j)->GetVar()) -
		p_System.GetDifferenceI() * (p_System.GetMomentumFieldJ()->GetPoint(i, v)->GetVar() + 
			p_System.GetDt() * p_System.GetInterimMomentumFieldJ()->GetPoint(i, v)->GetVar()) +
		p_System.GetDifferenceI() * (p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar() +
			p_System.GetDt() * p_System.GetInterimMomentumFieldJ()->GetPoint(i, j)->GetVar());
}

double LinearBuilder::GetLeftSideB(int& j) {
	int i = 0;
	int k = i + 1;
	int v = j + 1;
	return -p_System.GetDifferenceJ() * (p_System.GetMomentumFieldI()->GetPoint(k, j)->GetVar() +
			p_System.GetDt() * p_System.GetInterimMomentumFieldI()->GetPoint(k, j)->GetVar()) +
		p_System.GetDifferenceJ() * p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar() -
		p_System.GetDifferenceI() * (p_System.GetMomentumFieldJ()->GetPoint(i, v)->GetVar() + 
			p_System.GetDt() * p_System.GetInterimMomentumFieldJ()->GetPoint(i, v)->GetVar()) +
		p_System.GetDifferenceI() * (p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar() + 
			p_System.GetDt() * p_System.GetInterimMomentumFieldJ()->GetPoint(i, j)->GetVar());
}

double LinearBuilder::GetInteriorB(int& i, int& j) {
	int k = i + 1;
	int v = j + 1;
	return p_System.GetDifferenceJ() * (p_System.GetMomentumFieldI()->GetPoint(k, j)->GetVar() +
			p_System.GetDt() * p_System.GetInterimMomentumFieldI()->GetPoint(k, j)->GetVar()) +
		p_System.GetDifferenceJ() * (p_System.GetMomentumFieldI()->GetPoint(i, j)->GetVar() +
			p_System.GetDt() * p_System.GetInterimMomentumFieldI()->GetPoint(i, j)->GetVar()) -
		p_System.GetDifferenceI() * (p_System.GetMomentumFieldJ()->GetPoint(i, v)->GetVar() + 
			p_System.GetDt() * p_System.GetInterimMomentumFieldJ()->GetPoint(i, v)->GetVar()) +
		p_System.GetDifferenceI() * (p_System.GetMomentumFieldJ()->GetPoint(i, j)->GetVar() + 
			p_System.GetDt() * p_System.GetInterimMomentumFieldJ()->GetPoint(i, j)->GetVar());
}

void LinearBuilder::BuildElementA() {
	double var;
	for (int index = 0; index < p_System.GetPressureField()->GetTotal(); index++) {
		if (index == 0) {
			var = GetCornerA();
		}
		else if (index > 0 && index < p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = GetFloorA();
		}
		else if (index == p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = GetCornerA();
		}
		else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
			index < (p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI())) {
			if (index % p_System.GetPressureField()->GetDimensionSizeI() == 0) {
				var = GetWallA();
			}
			else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
				index < p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI() - 1) {
				var = GetInteriorA();
			}
			else {
				var = GetWallA();
			}
		}
		else if (index == p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = GetCornerA();
		}
		else if (index > p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() &&
			index < p_System.GetPressureField()->GetTotal() - 1) {
			var = GetFloorA();
		}
		else {
			var = GetCornerA();
		}
		GetElementA()->BuildMainDiagonal(index, var);
	}
}

void LinearBuilder::BuildElementAip() {
	double var;
	for (int index = 0; index < p_System.GetPressureField()->GetTotal(); index++) {
		if (index == 0) {
			var = GetBaseValue();
		}
		else if (index > 0 && index < p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = GetBaseValue();
		}
		else if (index == p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = 0.0;
		}
		else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
			index < (p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI() + 1)) {
			if (index % p_System.GetPressureField()->GetDimensionSizeI() == 0) {
				var = GetBaseValue();
			}
			else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
				index < p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI() - 1) {
				var = GetBaseValue();
			}
			else {
				var = 0.0;
			}
		}
		else if (index == p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = GetCornerA();
		}
		else if (index > p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() &&
			index < p_System.GetPressureField()->GetTotal() - 1) {
			var = GetBaseValue();
		}
		else {
			var = 0.0;
		}
		GetElementAip()->BuildOffDiagonalPlusI(index, var);
	}
}

void LinearBuilder::BuildElementAim() {
	double var;
	for (int index = 0; index < p_System.GetPressureField()->GetTotal(); index++) {
		if (index == 0) {
			var = 0.0;
		}
		else if (index > 0 && index < p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = GetBaseValue();
		}
		else if (index == p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = GetBaseValue();
		}
		else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
			index < (p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI() + 1)) {
			if (index % p_System.GetPressureField()->GetDimensionSizeI() == 0) {
				var = 0.0;
			}
			else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
				index < p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI() - 1) {
				var = GetBaseValue();
			}
			else {
				var = GetBaseValue();
			}
		}
		else if (index == p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = 0.0;
		}
		else if (index > p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() &&
			index < p_System.GetPressureField()->GetTotal() - 1) {
			var = GetBaseValue();
		}
		else {
			var = GetBaseValue();
		}
		GetElementAim()->BuildOffDiagonalMinusI(index, var);
	}
}

void LinearBuilder::BuildElementAjp() {
	double var;
	for (int index = 0; index < p_System.GetPressureField()->GetTotal(); index++) {
		if (index == 0) {
			var = 0.0;
		}
		else if (index > 0 && index < p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = 0.0;
		}
		else if (index == p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = 0.0;
		}
		else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
			index < (p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI())) {
			if (index % p_System.GetPressureField()->GetDimensionSizeI() == 0) {
				var = GetBaseValue();
			}
			else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
				index < p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI() - 1) {
				var = GetBaseValue();
			}
			else {
				var = GetBaseValue();
			}
		}
		else if (index == p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = GetBaseValue();
		}
		else if (index > p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() &&
			index < p_System.GetPressureField()->GetTotal() - 1) {
			var = GetBaseValue();
		}
		else {
			var = GetBaseValue();
		}
		GetElementAjp()->BuildOffDiagonalPlusJ(index, var);
	}
}

void LinearBuilder::BuildElementAjm() {
	double var;
	for (int index = 0; index < p_System.GetPressureField()->GetTotal(); index++) {
		if (index == 0) {
			var = GetBaseValue();
		}
		else if (index > 0 && index < p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = GetBaseValue();
		}
		else if (index == p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = GetBaseValue();
		}
		else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
			index < (p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI())) {
			if (index % p_System.GetPressureField()->GetDimensionSizeI() == 0) {
				var = GetBaseValue();
			}
			else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
				index < p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI() - 1) {
				var = GetBaseValue();
			}
			else {
				var = GetBaseValue();
			}
		}
		else if (index == p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = 0.0;
		}
		else if (index > p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() &&
			index < p_System.GetPressureField()->GetTotal() - 1) {
			var = 0.0;
		}
		else {
			var = 0.0;
		}
		GetElementAjm()->BuildOffDiagonalMinusJ(index, var);
	}
}

void LinearBuilder::BuildVectorB() {
	double var;
	int ni = p_System.GetPressureField()->GetTotal();
	int nj = 1;
	GetVectorB()->SetDimensionSizeI(ni);
	GetVectorB()->SetDimensionSizeJ(nj);
	GetVectorB()->AllocateMemory();
	for (int index = 0; index < p_System.GetPressureField()->GetTotal(); index++) {
		Point Instance = Point();
		int i = index % p_System.GetPressureField()->GetDimensionSizeI();
		int j = 0;
		if (index == 0) {
			var = GetTopLeftB();
		}
		else if (index > 0 && index < p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = GetTopSideB(i);
		}
		else if (index == p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = GetTopRightB();
		}
		else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
			index < p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			if (index % p_System.GetPressureField()->GetDimensionSizeI() == 0) {
				var = GetLeftSideB(j);
			}
			else if (index % p_System.GetPressureField()->GetDimensionSizeI() ==
				p_System.GetPressureField()->GetDimensionSizeI() - 1) {
				var = GetRightSideB(j);
			}
			else {
				var = GetInteriorB(i, j);
			}
		}
		else if (index == p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = GetBottomLeftB();
		}
		else if (index > p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
			p_System.GetPressureField()->GetTotal() - 1) {
			var = GetBottomSideB(i);
		}
		else {
			var = GetBottomRightB();
		}
		Instance.SetVar(var);
		Instance.SetIndexI(index);
		Instance.SetIndexJ(j);
		GetVectorB()->SetPoint(Instance, index);
	}
}