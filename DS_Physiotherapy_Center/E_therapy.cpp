#include "E_therapy.h"
#include"Patient.h"
#include"Scheduler.h"

bool E_therapy::CanAssign(Scheduler* s)
{
	return s->isEAvailable();
}

void E_therapy::MoveToWait(Scheduler* scheduler)
{
	scheduler->AddToWait_E(AssignedPatient);
}
