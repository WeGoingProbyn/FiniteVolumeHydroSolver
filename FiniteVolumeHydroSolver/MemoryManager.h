#pragma once

#include "Container.h"

#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

class MemoryManager {
private:
	Point* arr;
	Field* manager;
	int p_NumFields, Occupied;
	const int MaxItems = 4096;

public:
	MemoryManager();

	Field* AllocateMemoryToRam();
    void DestroyAllocatedMemory();
};

#endif

