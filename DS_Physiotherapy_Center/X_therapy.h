#pragma once
#include"Treatment.h"
#include"Scheduler.h"
class X_therapy :public Treatment
{
	X_therapy(int dur):Treatment(dur){}
	bool CanAssign(Scheduler* s);
    void MoveToWait(Scheduler* scheduler);
};

