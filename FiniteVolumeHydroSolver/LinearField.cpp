#include "LinearField.h"
#include <iostream>

void LinearField::BuildMainDiagonal(int& index, double& var) {
	int i = index % this->GetDimensionSizeI();
	Point instance = Point(var);
	instance.SetIndexI(i);
	instance.SetIndexJ(i);
	this->SetPoint(instance, index);
}

void LinearField::BuildOffDiagonalPlusI(int& index, double& var) {
	int i = (index % this->GetDimensionSizeI()) + 1;
	int j = i - 1;
	Point instance = Point(var);
	instance.SetIndexI(i);
	instance.SetIndexJ(j);
	int adjusted = index + this->GetDimensionSizeI() - 2;
	this->SetPoint(instance, index);
}

void LinearField::BuildOffDiagonalMinusI(int& index, double& var) {
	int i = (index % this->GetDimensionSizeI()) - 1;
	int j = i + 1;
	Point instance = Point(var);
	instance.SetIndexI(i);
	instance.SetIndexJ(j);
	int adjusted = index + (2 * (this->GetDimensionSizeI() - 1));
	this->SetPoint(instance, index);
}

void LinearField::BuildOffDiagonalPlusJ(int& index, double& var) {
	int reduced = (int)std::pow(this->GetDimensionSizeI(), 0.5);
	int i = (index % this->GetDimensionSizeI());
	int j = i - reduced;
	Point instance = Point(var);
	instance.SetIndexI(i);
	instance.SetIndexJ(j);
	int adjusted = index + (3 * (this->GetDimensionSizeI() - 1));
	this->SetPoint(instance, index);
}

void LinearField::BuildOffDiagonalMinusJ(int& index, double& var) {
	int reduced = (int)std::pow(this->GetDimensionSizeI(), 0.5);
	int i = index % this->GetDimensionSizeI();
	int j = i + reduced;
	Point instance = Point(var);
	instance.SetIndexI(i);
	instance.SetIndexJ(j);
	int adjusted = index + (4 * (this->GetDimensionSizeI() - 1));
	this->SetPoint(instance, index);
}