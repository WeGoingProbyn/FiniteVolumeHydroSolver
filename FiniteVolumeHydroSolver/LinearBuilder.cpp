#include "LinearBuilder.h"

LinearBuilder::LinearBuilder() : p_System(Container()) {}

void LinearBuilder::SetContainer(Container& Container) { p_System = Container; }

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