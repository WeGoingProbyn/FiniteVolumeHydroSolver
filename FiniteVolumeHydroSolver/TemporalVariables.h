#pragma once

#ifndef TEMPORALVARIABLES_H
#define TEMPORALVARIABLES_H

class TemporalVariables {
private:
	double Dt, MaxTime, TrueTime;
public:
	double GetDt();
	double GetMaxTime();
	double GetTrueTime();

	void SetDt(double &Dt);
	void SetMaxTime(double &MaxTime);
	void SetTrueTime(double &TrueTime);
};

#endif