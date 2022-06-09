#include "BiCGSTAB.h"


void BiCGSTAB::CombineVectorAndElementsA(Field& Vector) {
	int j = 0;
	for (int index = 0; index < p_System.GetPressureField()->GetTotal(); index++) {
		double var = p_ElementA.GetPoint(index)->GetVar();
		Point point = Point(var);
		point.SetIndexI(index);
		point.SetIndexJ(j);
		p_Combined.SetPoint(point, index);
	}
	for (int index = 0; index < p_System.GetPressureField()->GetTotal(); index++) {
		if (index < p_System.GetPressureField()->GetTotal() - 1) {
			double var = p_Combined.GetPoint(index)->GetVar();
			var += p_ElementAip.GetPoint(index)->GetVar();
			p_Combined.GetPoint(index)->SetVar(var);
		}
		if (index > 0) {
			double var = p_Combined.GetPoint(index)->GetVar();
			var += p_ElementAim.GetPoint(index)->GetVar();
			p_Combined.GetPoint(index)->SetVar(var);
		}
		if (index > p_System.GetPressureField()->GetDimensionSizeI() - 1) {
			double var = p_Combined.GetPoint(index)->GetVar();
			var += p_ElementAjp.GetPoint(index)->GetVar();
			p_Combined.GetPoint(index)->SetVar(var);
		}
		if (index < p_System.GetPressureField()->GetTotal() - p_System.GetPressureField()->GetDimensionSizeI()) {
			double var = p_Combined.GetPoint(index)->GetVar();
			var += p_ElementAjm.GetPoint(index)->GetVar();
			p_Combined.GetPoint(index)->SetVar(var);
		}
	}
	for (int index = 0; index < p_System.GetPressureField()->GetTotal(); index++) {
		double var = p_Combined.GetPoint(index)->GetVar() * Vector.GetPoint(index)->GetVar();
		p_Combined.GetPoint(index)->SetVar(var);
	}
}

double BiCGSTAB::FindDotProduct(Field& VectorA, Field& VectorB) {
	double var = 0;
	for (int index = 0; index < VectorA.GetDimensionSizeI(); index++) {
		var += VectorA.GetPoint(index)->GetVar() * VectorB.GetPoint(index)->GetVar();
	}
	return var;
}