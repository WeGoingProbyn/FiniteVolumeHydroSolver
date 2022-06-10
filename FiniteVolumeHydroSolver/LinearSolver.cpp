#include "LinearSolver.h"

LinearSolver::LinearSolver() : p_VectorB(Field()) {
	p_ElementA = LinearField();
	p_ElementAip = LinearField();
	p_ElementAim = LinearField();
	p_ElementAjp = LinearField();
	p_ElementAjm = LinearField();

	p_VectorB.AllocateMemory();
	p_ElementA.AllocateMemory();
	p_ElementAip.AllocateMemory();
	p_ElementAim.AllocateMemory();
	p_ElementAjp.AllocateMemory();
	p_ElementAjm.AllocateMemory();
}

//BiCGSTAB* LinearSolver::GetBiCGSTAB() { return &p_BiCGSTAB; }

void LinearSolver::SetInternalFieldDimensions(int& Ni) {
	int ni = Ni;
	int nj = 1;

	p_VectorB.SetDimensionSizeI(ni);
	p_VectorB.SetDimensionSizeJ(nj);

	p_ElementA.SetDimensionSizeI(ni);
	p_ElementA.SetDimensionSizeJ(nj);

	p_ElementAip.SetDimensionSizeI(ni);
	p_ElementAip.SetDimensionSizeJ(nj);

	p_ElementAim.SetDimensionSizeI(ni);
	p_ElementAim.SetDimensionSizeJ(nj);

	p_ElementAjp.SetDimensionSizeI(ni);
	p_ElementAjp.SetDimensionSizeJ(nj);

	p_ElementAjm.SetDimensionSizeI(ni);
	p_ElementAjm.SetDimensionSizeJ(nj);
}

void LinearSolver::DestroyInternalPoints() {
	p_VectorB.DestroyMemory();
	p_ElementA.DestroyMemory();
	p_ElementAip.DestroyMemory();
	p_ElementAim.DestroyMemory();
	p_ElementAjp.DestroyMemory();
	p_ElementAjm.DestroyMemory();
}

LinearField* LinearSolver::GetElementA() { return &p_ElementA; }
LinearField* LinearSolver::GetElementAip() { return &p_ElementAip; }
LinearField* LinearSolver::GetElementAim() { return &p_ElementAim; }
LinearField* LinearSolver::GetElementAjp() { return &p_ElementAjp; }
LinearField* LinearSolver::GetElementAjm() { return &p_ElementAjm; }

Field* LinearSolver::GetVectorB() { return &p_VectorB; }
