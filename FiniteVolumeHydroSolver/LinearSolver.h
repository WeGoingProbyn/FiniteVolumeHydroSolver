#pragma once

#include "LinearBuilder.h"
#include "BiCGSTAB.h"
#include "Field.h"
#include "LinearField.h"

#ifndef LINEARSOLVER_H
#define LINEARSOLVER_H

class LinearSolver {
private:
	LinearBuilder p_Builder;
	//BiCGSTAB p_BiCGSTAB;
	Container p_System;
	LinearField p_MatrixA;
	Field p_VectorB;
public:
	LinearSolver();

	LinearField* GetMatrixA();
	Field* GetVectorB();

	void SetContainer(Container& Container);
	void BuildMatrixA();
	void BuildVectorB();
};
#endif