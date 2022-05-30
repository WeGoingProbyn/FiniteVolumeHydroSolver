#pragma once

#ifndef POINT_H
#define POINT_H

class Point {
private:
	int i, j;
	double var;

public:
	Point();

	int GetIndexI();
	int GetIndexJ();
	double GetVar();

	void SetIndexI(int &i);
	void SetIndexJ(int &j);
	void SetVar(double &var);
};

#endif