#include "Treatment.h"

Treatment::Treatment(int d , int AT ) : AssignedResource(nullptr) {
	Duration = d;
	AssignmentTime = AT;
	AssignedPatient = nullptr;
}
void Treatment::setDuration(int d) {
	Duration = d;
}
int Treatment::getDuration() {
	return Duration;
}
void Treatment::setAssignmentTime(int T) {
	AssignmentTime = T;
}
int Treatment::getAssignmentTime() {
	return AssignmentTime;
}

void Treatment::setAssignedResource(resources* AR) {
	AssignedResource = AR;
}

void Treatment::setAssignedPatient(Patient* p)
{
	AssignedPatient = p;
}

Patient* Treatment::getAssignedPatient()
{
	return AssignedPatient;
}

resources* Treatment::getAssignedResource()
{
	return AssignedResource;
}
