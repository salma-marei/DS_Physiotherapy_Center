#pragma once
#include"Patient.h"
//#include"Resources.h"
class Treatment
{
	int Duration;
	int AssignmentTime;
	Patient* Patient;
	// pointer to assigned resource lma roaa t3mlo
	// Resource* AssignedResource;
public:
	Treatment(int d=0, int AT=0):Patient(nullptr) {
		Duration = d;
		AssignmentTime = AT;
	}
	//virtual bool CanAssign(Resource* AssignedResource);
	//virtual void MoveToWait(Schedular*schedular);
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
	//void setAssignedResource(Resource*AR){
	//AssignedResource=AR;}
};

