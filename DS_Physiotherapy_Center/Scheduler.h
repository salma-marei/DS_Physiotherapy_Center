#pragma once
#include <fstream>
#include <iostream>
#include "LinkedQueue.h"
#include "priQueue.h"
#include "EarlyPList.h"
#include "resources.h"
#include "ArrayStack.h"
#include "Patient.h"
//class resources;
//class Patient;
class Scheduler {
private:
	LinkedQueue<Patient*> AllList;
	EarlyPList EarlyList;
	priQueue<Patient*> LateList;
	/* EU_WaitList UWaitList
	* EU_WaitList EWaitList
	X_WaitList XWaitList*/
	LinkedQueue<resources*> EDevices;
	LinkedQueue<resources*> UDevices;
	LinkedQueue<resources*> XRooms;
	priQueue<Patient*> InTreatmentList;
	ArrayStack<Patient*> FinishedPatients;
	int timestep;
public:
	void loadPatients(string filename); //only function we need to implement for phase 1.2
};