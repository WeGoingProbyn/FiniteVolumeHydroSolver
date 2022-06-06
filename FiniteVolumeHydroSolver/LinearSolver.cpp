#include "LinearSolver.h"

LinearSolver::LinearSolver() : 
	p_Builder(LinearBuilder()), p_System(Container()), p_MatrixA(LinearField()), p_VectorB(Field()) {}

LinearField* LinearSolver::GetMatrixA() { return &p_MatrixA; }

Field* LinearSolver::GetVectorB() { return &p_VectorB; }

void LinearSolver::SetContainer(Container& Container) { 
	p_System = Container;
	p_Builder.SetContainer(Container);
}

void LinearSolver::BuildMatrixA() {
	int ni = p_System.GetPressureField()->GetTotal();
	int nj = 5;
	p_MatrixA.SetDimensionSizeI(ni);
	p_MatrixA.SetDimensionSizeJ(nj);
	p_MatrixA.AllocateMemory();
	double diagonal, iPlus, iMinus, jPlus, jMinus;
	for (int index = 0; index < p_System.GetPressureField()->GetTotal(); index++) {
		if (index == 0) {
			diagonal = p_Builder.GetCornerA();
			iPlus = p_Builder.GetBaseValue();
			iMinus = 0.0;
			jPlus = 0.0;
			jMinus = p_Builder.GetBaseValue();
		}
		else if (index > 0 && index < p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			diagonal = p_Builder.GetFloorA();
			iPlus = p_Builder.GetBaseValue();;
			iMinus = p_Builder.GetBaseValue();
			jPlus = 0.0;
			jMinus = p_Builder.GetBaseValue();
		}
		else if (index == p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			diagonal = p_Builder.GetCornerA();
			iPlus = 0.0;
			iMinus = p_Builder.GetBaseValue();
			jPlus = 0.0;
			jMinus = p_Builder.GetBaseValue();
		}
		else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
			index < p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			if (index % p_System.GetPressureField()->GetDimensionSizeI() == 0 ) {
				diagonal = p_Builder.GetWallA();
				iPlus = p_Builder.GetBaseValue();
				iMinus = 0.0;
				jPlus = p_Builder.GetBaseValue();
				jMinus = p_Builder.GetBaseValue();
			}
			else if (index % p_System.GetPressureField()->GetDimensionSizeI() ==
				p_System.GetPressureField()->GetDimensionSizeI() - 1) {
				diagonal = p_Builder.GetWallA();
				iPlus = 0.0;
				iMinus = p_Builder.GetBaseValue();
				jPlus = p_Builder.GetBaseValue();;
				jMinus = p_Builder.GetBaseValue();
			}
			else {
				diagonal = p_Builder.GetInteriorA();
				iPlus = p_Builder.GetBaseValue();
				iMinus = p_Builder.GetBaseValue();
				jPlus = p_Builder.GetBaseValue();
				jMinus = p_Builder.GetBaseValue();
			}
		}
		else if (index == p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			diagonal = p_Builder.GetCornerA();
			iPlus = p_Builder.GetBaseValue();
			iMinus = 0.0;
			jPlus = p_Builder.GetBaseValue();
			jMinus = 0.0;
		}
		else if (index > p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
			p_System.GetPressureField()->GetTotal() - 1) {
			diagonal = p_Builder.GetFloorA();
			iPlus = p_Builder.GetBaseValue();
			iMinus = p_Builder.GetBaseValue();
			jPlus = p_Builder.GetBaseValue();
			jMinus = 0.0;
		}
		else {
			diagonal = p_Builder.GetCornerA();
			iPlus = 0.0;
			iMinus = p_Builder.GetBaseValue();
			jPlus = p_Builder.GetBaseValue();
			jMinus = 0.0;
		}
		p_MatrixA.BuildMainDiagonal(index, diagonal);
		p_MatrixA.BuildOffDiagonalPlusI(index, iPlus);
		p_MatrixA.BuildOffDiagonalMinusI(index, iMinus);
		p_MatrixA.BuildOffDiagonalPlusJ(index, jPlus);
		p_MatrixA.BuildOffDiagonalMinusJ(index, jMinus);
	}
}

void LinearSolver::BuildVectorB() {
	double var;
	int ni = p_System.GetPressureField()->GetTotal();
	int nj = 1;
	p_VectorB.SetDimensionSizeI(ni);
	p_VectorB.SetDimensionSizeJ(nj);
	p_VectorB.AllocateMemory();
	for (int index = 0; index < p_System.GetPressureField()->GetTotal(); index++) {
		Point Instance = Point();
		int i = index % p_System.GetPressureField()->GetDimensionSizeI();
		int j = 0;
		if (index == 0) {
			var = p_Builder.GetTopLeftB();
		}
		else if (index > 0 && index < p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = p_Builder.GetTopSideB(i);
		}
		else if (index == p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = p_Builder.GetTopRightB();
		}
		else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
			index < p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			if (index % p_System.GetPressureField()->GetDimensionSizeI() == 0) {
				var = p_Builder.GetLeftSideB(j);
			}
			else if (index % p_System.GetPressureField()->GetDimensionSizeI() ==
				p_System.GetPressureField()->GetDimensionSizeI() - 1) {
				var = p_Builder.GetRightSideB(j);
			}
			else {
				var = p_Builder.GetInteriorB(i, j);
			}
		}
		else if (index == p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = p_Builder.GetBottomLeftB();
		}
		else if (index > p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
			p_System.GetPressureField()->GetTotal() - 1) {
			var = p_Builder.GetBottomSideB(i);
		}
		else {
			var = p_Builder.GetBottomRightB();
		}
		Instance.SetVar(var);
		Instance.SetIndexI(index);
		Instance.SetIndexJ(j);
		p_VectorB.SetPoint(Instance, index);
	}
}