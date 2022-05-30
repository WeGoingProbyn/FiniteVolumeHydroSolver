#include "Point.h"

Point::Point() : i(-1), j(-1), var(0.0) {}

int Point::GetIndexI() { return i; }

int Point::GetIndexJ() { return j; }

double Point::GetVar() { return var; }

void Point::SetIndexI(int &i) { i = i; }

void Point::SetIndexJ(int &j) { j = j; }

void Point::SetVar(double &var) { var = var; }