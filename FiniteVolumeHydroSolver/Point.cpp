#include "Point.h"

#include <iostream>

Point::Point() : p_i(-1), p_j(-1), p_var(0.0) {}

int Point::GetIndexI() { return p_i; }

int Point::GetIndexJ() { return p_j; }

double Point::GetVar() { return p_var; }

void Point::SetIndexI(int& i) { p_i = i; }

void Point::SetIndexJ(int& j) { p_j = j; }

void Point::SetVar(double& var) { p_var = var; }