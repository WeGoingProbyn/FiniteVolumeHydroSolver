#include "Field.h"

Field::Field() : ni(0), nj(0), arr(nullptr) {}

int Field::GetTotal() { return ni * nj; }

int Field::GetDimensionSizeI() { return ni; }

int Field::GetDimensionSizeJ() { return nj; }

void Field::SetDimensionSizeI(int &ni) { ni = ni; }

void Field::SetDimensionSizeJ(int &nj) { nj = nj; }

void Field::SetPoint(Point &instance, int &index) { arr[index] = instance; }

void Field::BuildField() {
	for (int index = 0; index < GetTotal(); index++) {
		arr[index] = Point();
		if (index > 0) {
			if (index / ni > 1) {
				int j = index % nj;
				arr[index].SetIndexJ(j);
			}
			else {
				int i = index / ni;
				int j = index % nj;
				arr[index].SetIndexI(i);
				arr[index].SetIndexJ(j);
			}
		}
	}
}

Point Field::GetPoint(int &i, int &j) {
	for (int index = 0; index < GetTotal(); index++) {
		if (index / ni == arr[index].GetIndexI() && index % nj == arr[index].GetIndexJ()) {
			return arr[index];
		}
	}
	return Point();
}