#pragma once
#include <fstream>
#include <iostream>
#include "LinkedQueue.h"
#include "priQueue.h"
#include "EarlyPList.h"
#include "resources.h"
#include "ArrayStack.h"
#include "Patient.h"
#include "EU_WaitList.h"
#include "X_WaitList.h"

//class resources;
//class Patient;
class Scheduler {
private:
	LinkedQueue<Patient*> AllList;
	EarlyPList EarlyList;
	priQueue<Patient*> LateList;
	EU_WaitList UWaitList;
	EU_WaitList EWaitList;
	X_WaitList XWaitList;
	LinkedQueue<resources*> EDevices;
	LinkedQueue<resources*> UDevices;
	LinkedQueue<resources*> XRooms;
	priQueue<Patient*> InTreatmentList;
	ArrayStack<Patient*> FinishedPatients;
	int timestep;
	int numPatients;
	int numE, numU, numX;//Total number of devices
	int pResc;
	//UI* pUI;
	string filename;
public:
	Scheduler();
	void loadPatients(string filename); //only function we need to implement for phase 1.2
};