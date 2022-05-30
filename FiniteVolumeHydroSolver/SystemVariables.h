#pragma once

#ifndef SYSTEMVARIABLES_H
#define SYSTEMVARIABLES_H

class SystemVariables {
private:
	int nx, ny;
	double Re, Nu, Rho, Cfl, Tolerance;
public:
	SystemVariables();

	int GetSizeX();
	int GetSizeY();
	double GetRe();
	double GetNu();
	double GetRho();
	double GetCfl();
	double GetTolerance();

	void SetSizeX(int &nx);
	void SetSizeY(int &ny);
	void SetRe(double &Re);
	void SetNu(double &Nu);
	void SetRho(double &Rho);
	void SetCfl(double &Cfl);
	void SetTolerance(double &Tolerance);
};

#endif