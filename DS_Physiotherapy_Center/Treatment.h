#pragma once
//#include"Patient.h"
//#include"resources.h"
//#include"Scheduler.h"
class Patient;
class resources;
class Scheduler;
class Treatment
{
protected:
	int Duration;
	int AssignmentTime;
	resources* AssignedResource;
	Patient* AssignedPatient;
public:

	Treatment(int d = 0, int AT = -1);
	virtual bool CanAssign(Scheduler* s)=0;
	virtual void MoveToWait(Scheduler*scheduler)=0;
	void setDuration(int d);
	int getDuration();
	void setAssignmentTime(int T);
	int getAssignmentTime();
	void setAssignedResource(resources* AR);
	void setAssignedPatient(Patient* p);
	Patient* getAssignedPatient();
	resources* getAssignedResource();
};

