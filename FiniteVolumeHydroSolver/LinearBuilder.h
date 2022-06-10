#pragma once

#include "Container.h"
#pragma once

#include "LinearSolver.h"
#include "Container.h"

#ifndef LINEARBUILDER_H
#define LINEARBUILDER_H

class LinearBuilder : public LinearSolver {
private:
	Container p_System;
public:
	LinearBuilder();
	void SetContainer(Container& Container);
	double GetBaseValue();
	Container* GetContainer();

	double GetCornerA();
	double GetWallA();  // For walls running down the sides
	double GetFloorA(); // For walls running across (up and down)
	double GetInteriorA();

	double GetTopRightB();
	double GetTopLeftB();
	double GetBottomRightB();
	double GetBottomLeftB();

	double GetTopSideB(int& i);
	double GetBottomSideB(int& i);
	double GetRightSideB(int& j);
	double GetLeftSideB(int& j);

	double GetInteriorB(int& i, int& j);

	void BuildElementA();
	void BuildElementAip();
	void BuildElementAim();
	void BuildElementAjp();
	void BuildElementAjm();

	void BuildVectorB();
};

#endif