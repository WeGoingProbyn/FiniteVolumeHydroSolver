#pragma once

#ifndef TEMPORALVARIABLES_H
#define TEMPORALVARIABLES_H

class TemporalVariables {
private:
	double dt, Cfl, MaxTime, TrueTime;
public:
	double GetDt();
	double GetCfl();
	double GetMaxTime();
	double GetTrueTime();

	void SetDt(double & dt);
	void SetCfl(double& Cfl);
	void SetMaxTime(double &MaxTime);
	void SetTrueTime(double &TrueTime);
};

#endif