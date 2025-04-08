#include "X_therapy.h"
#include"Patient.h"
#include"Scheduler.h"

bool X_therapy::CanAssign(Scheduler* s)
{
    return s->isXAvailable();;
}

void X_therapy::MoveToWait(Scheduler* scheduler)
{
	scheduler->AddToWait_X(AssignedPatient);
}
