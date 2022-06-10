#pragma once

//#include "BiCGSTAB.h"
#include "Field.h"
#include "LinearField.h"

#ifndef LINEARSOLVER_H
#define LINEARSOLVER_H

class LinearSolver {
private:
	Field p_VectorB;
	LinearField p_ElementA, p_ElementAip, p_ElementAim, p_ElementAjp, p_ElementAjm;
public:
	LinearSolver();
	void DestroyInternalPoints();

	LinearField* GetElementA();
	LinearField* GetElementAip();
	LinearField* GetElementAim();
	LinearField* GetElementAjp();
	LinearField* GetElementAjm();
	Field* GetVectorB();

	void SetInternalFieldDimensions(int& Ni);
};
#endif