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
	Field p_VectorB;
	LinearField p_ElementA, p_ElementAip, p_ElementAim, p_ElementAjp, p_ElementAjm;
public:
	LinearSolver();

	void DestroyPoints();

	void CombineVectorandElemetsA(Field& Vector);
	double FindDotProduct(Field& VectorA, Field& VectorB);

	LinearField* GetElementA();
	LinearField* GetElementAip();
	LinearField* GetElementAim();
	LinearField* GetElementAjp();
	LinearField* GetElementAjm();
	Field* GetVectorB();
	Field* GetCombined();
	Field* GetGuess();

	void SetContainer(Container& Container);
	void SetFieldDimensions();

	void BuildElementA();
	void BuildElementAip();
	void BuildElementAim();
	void BuildElementAjp();
	void BuildElementAjm();

	void BuildVectorB();
};
#endif