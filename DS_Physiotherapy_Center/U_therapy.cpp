#include "U_therapy.h"
#include"Patient.h"
#include"Scheduler.h"

bool U_therapy::CanAssign(Scheduler* s)
{
	return s->isUAvailable();;
}

void U_therapy::MoveToWait(Scheduler* scheduler)
{
	scheduler->AddToWait_U(AssignedPatient);
}
