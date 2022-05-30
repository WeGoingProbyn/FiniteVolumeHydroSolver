#pragma once

#include "Point.h"

#ifndef FIELD_H
#define FIELD_H

class Field {
private:
	Point* arr;
	int ni, nj;
public:
	Field();

	int GetTotal();
	int GetDimensionSizeI();
	int GetDimensionSizeJ();

	void SetDimensionSizeI(int &ni);
	void SetDimensionSizeJ(int &nj);

	void BuildField();
	void SetPoint(Point &instance, int &index);
	Point GetPoint(int &i, int &j);
};

#endif

