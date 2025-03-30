#pragma once
#include"Patient.h"
#include"resources.h"
class Treatment
{
	int Duration;
	int AssignmentTime;
	Patient* Patient;
	resources* AssignedResource;
public:
	Treatment(int d = 0, int AT = 0) :Patient(nullptr), AssignedResource(nullptr) {
		Duration = d;
		AssignmentTime = AT;
	}
	virtual bool CanAssign(resources* AssignedResource)=0;
	//virtual void MoveToWait(Schedular*schedular)=0;
	void setDuration(int d) {
		Duration = d;
	}
	int getDuration() {
		return Duration;
	}
	void setAssignmentTime(int T) {
		AssignmentTime = T;
	}
	int getAssignmentTime() {
		return AssignmentTime;
	}
	void setPatient(class Patient* p) {
		Patient = p;
	}
	class Patient* getPatient() {
		return Patient;
	}
	void setAssignedResource(resources*AR){
	   AssignedResource=AR;
	}
};

