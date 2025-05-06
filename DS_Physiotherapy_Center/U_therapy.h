#pragma once
#include"Treatment.h"
class Scheduler;
class U_therapy : public Treatment
{
public:
	U_therapy(int dur) :Treatment(dur) {}
	bool CanAssign(Scheduler* s);
	void MoveToWait(Scheduler* scheduler);
};

