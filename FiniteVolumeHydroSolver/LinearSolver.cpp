#include "LinearSolver.h"

LinearSolver::LinearSolver() : 
	p_Builder(LinearBuilder()), p_System(Container()), p_VectorB(Field()) {
	p_ElementA = LinearField();
	p_ElementAip = LinearField();
	p_ElementAim = LinearField();
	p_ElementAjp = LinearField();
	p_ElementAjm = LinearField();

	p_Combined = Field();
	p_Guess = Field();

	p_ElementA.AllocateMemory();
	p_ElementAip.AllocateMemory();
	p_ElementAim.AllocateMemory();
	p_ElementAjp.AllocateMemory();
	p_ElementAjm.AllocateMemory();
	p_Combined.AllocateMemory();
	p_Guess.AllocateMemory();
}

void LinearSolver::SetFieldDimensions() {
	int ni = p_System.GetPressureField()->GetTotal();
	int nj = 1;

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

	p_Combined.SetDimensionSizeI(ni);
	p_Combined.SetDimensionSizeJ(nj);

	p_Combined.SetDimensionSizeI(ni);
	p_Combined.SetDimensionSizeJ(nj);
}

void LinearSolver::DestroyPoints() {
	p_ElementA.DestroyMemory();
	p_ElementAip.DestroyMemory();
	p_ElementAim.DestroyMemory();
	p_ElementAjp.DestroyMemory();
	p_ElementAjm.DestroyMemory();
	p_Combined.DestroyMemory();
	p_Guess.DestroyMemory();
}

LinearField* LinearSolver::GetElementA() { return &p_ElementA; }
LinearField* LinearSolver::GetElementAip() { return &p_ElementAip; }
LinearField* LinearSolver::GetElementAim() { return &p_ElementAim; }
LinearField* LinearSolver::GetElementAjp() { return &p_ElementAjp; }
LinearField* LinearSolver::GetElementAjm() { return &p_ElementAjm; }

Field* LinearSolver::GetVectorB() { return &p_VectorB; }
Field* LinearSolver::GetCombined() { return &p_Combined; }
Field* LinearSolver::GetGuess() { return &p_Guess; }

void LinearSolver::SetContainer(Container& Container) { 
	p_System = Container;
	p_Builder.SetContainer(Container);
}

void LinearSolver::BuildElementA() {
	double var;
	for (int index = 0; index < p_System.GetPressureField()->GetTotal(); index++) {
		if (index == 0) {
			var = p_Builder.GetCornerA();
		}
		else if (index > 0 && index < p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = p_Builder.GetFloorA();
		}
		else if (index == p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = p_Builder.GetCornerA();
		}
		else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
			index < (p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI())) {
			if (index % p_System.GetPressureField()->GetDimensionSizeI() == 0) {
				var = p_Builder.GetWallA();
			}
			else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
				index < p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI() - 1) {
				var = p_Builder.GetInteriorA();
			}
			else {
				var = p_Builder.GetWallA();
			}
		}
		else if (index == p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = p_Builder.GetCornerA();
		}
		else if (index > p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() &&
			index < p_System.GetPressureField()->GetTotal() - 1) {
			var = p_Builder.GetFloorA();
		}
		else {
			var = p_Builder.GetCornerA();
		}
		p_ElementA.BuildMainDiagonal(index, var);
	}
}

void LinearSolver::BuildElementAip() {
	double var;
	for (int index = 0; index < p_System.GetPressureField()->GetTotal(); index++) {
		if (index == 0) {
			var = p_Builder.GetBaseValue();
		}
		else if (index > 0 && index < p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = p_Builder.GetBaseValue();
		}
		else if (index == p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = 0.0;
		}
		else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
			index < (p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI())) {
			if (index % p_System.GetPressureField()->GetDimensionSizeI() == 0) {
				var = p_Builder.GetBaseValue();
			}
			else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
				index < p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI() - 1) {
				var = p_Builder.GetBaseValue();
			}
			else {
				var = 0.0;
			}
		}
		else if (index == p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = p_Builder.GetCornerA();
		}
		else if (index > p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() &&
			index < p_System.GetPressureField()->GetTotal() - 1) {
			var = p_Builder.GetBaseValue();
		}
		else {
			var = 0.0;
		}
		p_ElementAip.BuildOffDiagonalPlusI(index, var);
	}
}

void LinearSolver::BuildElementAim() {
	double var;
	for (int index = 0; index < p_System.GetPressureField()->GetTotal(); index++) {
		if (index == 0) {
			var = 0.0;
		}
		else if (index > 0 && index < p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = p_Builder.GetBaseValue();
		}
		else if (index == p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = p_Builder.GetBaseValue();
		}
		else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
			index < (p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI())) {
			if (index % p_System.GetPressureField()->GetDimensionSizeI() == 0) {
				var = 0.0;
			}
			else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
				index < p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI() - 1) {
				var = p_Builder.GetBaseValue();
			}
			else {
				var = p_Builder.GetBaseValue();
			}
		}
		else if (index == p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = 0.0;
		}
		else if (index > p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() &&
			index < p_System.GetPressureField()->GetTotal() - 1) {
			var = p_Builder.GetBaseValue();
		}
		else {
			var = p_Builder.GetBaseValue();
		}
		p_ElementAim.BuildOffDiagonalMinusI(index, var);
	}
}

void LinearSolver::BuildElementAjp() {
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
				var = p_Builder.GetBaseValue();
			}
			else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
				index < p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI() - 1) {
				var = p_Builder.GetBaseValue();
			}
			else {
				var = p_Builder.GetBaseValue();
			}
		}
		else if (index == p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = p_Builder.GetBaseValue();
		}
		else if (index > p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI() &&
			index < p_System.GetPressureField()->GetTotal() - 1) {
			var = p_Builder.GetBaseValue();
		}
		else {
			var = p_Builder.GetBaseValue();
		}
		p_ElementAjp.BuildOffDiagonalPlusJ(index, var);
	}
}

void LinearSolver::BuildElementAjm() {
	double var;
	for (int index = 0; index < p_System.GetPressureField()->GetTotal(); index++) {
		if (index == 0) {
			var = p_Builder.GetBaseValue();
		}
		else if (index > 0 && index < p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = p_Builder.GetBaseValue();
		}
		else if (index == p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			var = p_Builder.GetBaseValue();
		}
		else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
			index < (p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI())) {
			if (index % p_System.GetPressureField()->GetDimensionSizeI() == 0) {
				var = p_Builder.GetBaseValue();
			}
			else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
				index < p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI() - 1) {
				var = p_Builder.GetBaseValue();
			}
			else {
				var = p_Builder.GetBaseValue();
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
		p_ElementAjm.BuildOffDiagonalMinusJ(index, var);
	}
}

/*void LinearSolver::BuildMatrixA() {
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
			index < (p_System.GetPressureField()->GetTotal() -
			p_System.GetPressureField()->GetDimensionSizeI())) {
			if (index % p_System.GetPressureField()->GetDimensionSizeI() == 0 ) {
				diagonal = p_Builder.GetWallA();
				iPlus = p_Builder.GetBaseValue();
				iMinus = 0.0;
				jPlus = p_Builder.GetBaseValue();
				jMinus = p_Builder.GetBaseValue();
			}
			else if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1 &&
				index < p_System.GetPressureField()->GetTotal() -
				p_System.GetPressureField()->GetDimensionSizeI() - 1) {
				diagonal = p_Builder.GetInteriorA();
				iPlus = p_Builder.GetBaseValue();
				iMinus = p_Builder.GetBaseValue();
				jPlus = p_Builder.GetBaseValue();
				jMinus = p_Builder.GetBaseValue();
			}
			else {
				diagonal = p_Builder.GetWallA();
				iPlus = 0.0;
				iMinus = p_Builder.GetBaseValue();
				jPlus = p_Builder.GetBaseValue();;
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
			p_System.GetPressureField()->GetDimensionSizeI() &&
			index < p_System.GetPressureField()->GetTotal() - 1) {
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
}*/

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