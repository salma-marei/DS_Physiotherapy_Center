#pragma once
#include"Treatment.h"
#include"Scheduler.h"
class E_therapy : public Treatment
{
public: 
	E_therapy(int dur) :Treatment(dur) {}
	bool CanAssign(Scheduler* s);
	void MoveToWait(Scheduler* scheduler);
};

