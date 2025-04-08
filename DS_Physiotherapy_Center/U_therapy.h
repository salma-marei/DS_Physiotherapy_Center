#pragma once
#include"Treatment.h"
#include"Scheduler.h"
class U_therapy : public Treatment
{
	U_therapy(int dur) :Treatment(dur) {}
	bool CanAssign(Scheduler* s);
	void MoveToWait(Scheduler* scheduler);
};

