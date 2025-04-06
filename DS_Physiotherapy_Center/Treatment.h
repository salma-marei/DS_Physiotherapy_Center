#pragma once
#include"Patient.h"
#include"resources.h"
#include"Scheduler.h"
class Treatment
{
	int Duration;
	int AssignmentTime;
	Patient* Patient;
	resources* AssignedResource;
public:
	Treatment(int d = 0, int AT = 0) {}
	virtual bool CanAssign(resources* AssignedResource);
	virtual void MoveToWait(Scheduler*scheduler);
	void setDuration(int d) {}
	int getDuration(){}
	void setAssignmentTime(int T) {}
	int getAssignmentTime() {}
	void setPatient(class Patient* p){}
	class Patient* getPatient() {}
	void setAssignedResource(resources*AR){}
};

