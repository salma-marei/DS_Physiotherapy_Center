#include "Treatment.h"

Treatment::Treatment(int d , int AT ) :Patient(nullptr), AssignedResource(nullptr) {
	Duration = d;
	AssignmentTime = AT;
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
void Treatment::setPatient(class Patient* p) {
	Patient = p;
}
class Patient* Treatment::getPatient() {
	return Patient;
}
void Treatment::setAssignedResource(resources* AR) {
	AssignedResource = AR;
}