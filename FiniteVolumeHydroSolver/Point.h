#pragma once

#ifndef POINT_H
#define POINT_H

class Point {
private:
	int p_i, p_j;
	double p_var;

public:
	Point();

	int GetIndexI();
	int GetIndexJ();
	double GetVar();

	void SetIndexI(int& i);
	void SetIndexJ(int& j);
	void SetVar(double& var);
};

#endif