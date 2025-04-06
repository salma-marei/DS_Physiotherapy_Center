#pragma once
#include"Treatment.h"
#include"resources.h"
class X_therapy :public Treatment
{
	X_therapy(int dur):Treatment(dur){}
	bool CanAssign(resources* AssignedResource);
    void MoveToWait(Scheduler* scheduler);
};

