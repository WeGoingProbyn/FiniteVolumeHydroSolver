#include "Field.h"

#include <iostream>

Field::Field() : p_ni(0), p_nj(0), arr(nullptr) {}

void Field::AllocateMemory() { arr = new Point[MaxItems]; }

void Field::DestroyMemory() { delete[] arr; }

int Field::GetTotal() { return p_ni * p_nj; }

int Field::GetDimensionSizeI() { return p_ni; }

int Field::GetDimensionSizeJ() { return p_nj; }

void Field::SetDimensionSizeI(int& ni) { p_ni = ni; }

void Field::SetDimensionSizeJ(int& nj) { p_nj = nj; }

void Field::SetPoint(Point& instance, int& index) { arr[index] = instance; }

void Field::BuildField(int& index, double& var) {
	arr[index] = Point(var);
	int i, j;
	i = index % p_ni;
	j = index / p_ni;
	arr[index].SetIndexI(i);
	arr[index].SetIndexJ(j);
}


Point* Field::GetPoint(int& i, int& j) {
	int index = (j * p_ni) + i;
	return &arr[index];
}

Point* Field::GetPoint(int& index) { return &arr[index]; }

void Field::FieldToConsoleOutput() {
	for (int j = 0; j < this->GetDimensionSizeJ(); j++) {
		for (int i = 0; i < this->GetDimensionSizeI(); i++) {
			std::cout << "(" << this->GetPoint(i, j)->GetIndexI() << " , " << this->GetPoint(i, j)->GetIndexJ() << " , " << this->GetPoint(i, j)->GetVar() << ") ";
		}
		std::cout << std::endl;
	}
}