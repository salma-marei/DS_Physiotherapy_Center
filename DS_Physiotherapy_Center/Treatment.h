#pragma once
#include"Patient.h"
class Treatment
{
	int duration;
	int assignmentTime;
	Patient* Patient;
	// pointer to assigned resource lma roaa t3mlo
	// Resource* AssignedResource;
public:
	Treatment(int d=0, int AT=0):Patient(nullptr) {
		duration = d;
		assignmentTime = AT;
	}
	virtual bool CanAssign();
	virtual void MoveToWait();

};

