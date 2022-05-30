#include "Field.h"

#include <iostream>

Field::Field() : p_ni(0), p_nj(0), arr(nullptr) {}

void Field::AllocateMemory() { arr = new Point[MaxItems]; }

void Field::DestroyMemory() { delete arr; }

int Field::GetTotal() { return p_ni * p_nj; }

int Field::GetDimensionSizeI() { return p_ni; }

int Field::GetDimensionSizeJ() { return p_nj; }

void Field::SetDimensionSizeI(int& ni) { p_ni = ni; }

void Field::SetDimensionSizeJ(int& nj) { p_nj = nj; }

void Field::SetPoint(Point& instance, int& index) { arr[index] = instance; }

void Field::BuildField() {
	int i, j;
	for (int index = 0; index < GetTotal(); index++) {
		arr[index] = Point();
		if (index > 0) {
			if (index / p_ni < 1) {
				i = 0;
				j = index % p_nj;
			}
			else {
				i = index / p_ni;
				j = index % p_nj;
			}
		}
		else {
			i = 0;
			j = 0;
		}
		arr[index].SetIndexI(i);
		arr[index].SetIndexJ(j);
	}
}

Point* Field::GetPoint(int& i, int& j) {
	int index = (i * p_ni) + j;
	return &arr[index];
}