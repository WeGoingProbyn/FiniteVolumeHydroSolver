#pragma once

#include "Point.h"

#ifndef FIELD_H
#define FIELD_H

class Field {
private:
	Point* arr;
	int p_ni, p_nj;
	const static int MaxItems = 4096;
public:
	Field();

	void AllocateMemory();
	void DestroyMemory();

	int GetTotal();
	int GetDimensionSizeI();
	int GetDimensionSizeJ();

	void SetDimensionSizeI(int& ni);
	void SetDimensionSizeJ(int& nj);

	void BuildField();
	void SetPoint(Point& instance, int& index);
	Point* GetPoint(int& i, int& j);
};

#endif

