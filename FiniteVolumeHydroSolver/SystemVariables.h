#pragma once

#ifndef SYSTEMVARIABLES_H
#define SYSTEMVARIABLES_H

class SystemVariables {
private:
	int nx, ny;
	double Re, Tolerance;
public:
	SystemVariables();

	int GetSizeX();
	int GetSizeY();
	double GetRe();
	double GetTolerance();

	void SetSizeX(int &nx);
	void SetSizeY(int &ny);
	void SetRe(double &Re);
	void SetTolerance(double &Tolerance);
};

#endif