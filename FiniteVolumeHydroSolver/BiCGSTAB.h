#pragma once

#include "Field.h"
#include "LinearBuilder.h"

#ifndef BICGSTAB_H
#define BICGSTAB_H

class BiCGSTAB : public LinearBuilder {
private:
	const static int MaxIters = 10000;

	Field p_Combined, p_Residual, p_Residual0, p_Guess;
	Field p_Interim1, p_Interim2, p_Interim3, p_Interim4;
public:
	BiCGSTAB();

	void DestroyPoints();

	void SetFieldDimensions();

	Field* GetCombined();
	Field* GetResidual();
	Field* GetResidual0();
	Field* GetGuess();
	Field* GetInterim1();
	Field* GetInterim2();
	Field* GetInterim3();
	Field* GetInterim4();

	void CombineVectorAndElementsA(Field& Vector, Field& Resultant);
	double FindDotProduct(Field& VectorA, Field& VectorB);

	void Solve();
};

#endif