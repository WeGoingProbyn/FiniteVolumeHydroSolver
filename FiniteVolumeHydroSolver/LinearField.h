#pragma once

#include "Field.h"

#ifndef LINEARRFIELD_H
#define LINEARFIELD_H

class LinearField : public Field {
public:
	void BuildMainDiagonal(int& index, double& var);
	
	void BuildOffDiagonalPlusI(int& index, double& var);
	void BuildOffDiagonalMinusI(int& index, double& var);

	void BuildOffDiagonalPlusJ(int& index, double& var);
	void BuildOffDiagonalMinusJ(int& index, double& var);
};

#endif