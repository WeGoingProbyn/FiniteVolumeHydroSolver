#include "MemoryManager.h"

MemoryManager::MemoryManager() : p_NumFields(7), Occupied(0), manager(), arr() { Field* manager = new Field[p_NumFields]; }

int MemoryManager::AllocateMemoryToRam() {
	Point* arr = new Point[MaxItems];
	manager[Occupied] = arr;
	Occupied++;
}