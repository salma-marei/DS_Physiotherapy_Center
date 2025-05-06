#pragma once
#include <fstream>
#include <iostream>
#include "LinkedQueue.h"
#include "priQueue.h"
#include "EarlyPList.h"
#include "resources.h"
#include "ArrayStack.h"
#include "Patient.h"
#include "UI.h"
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
	UI* pUI;
	string filename;
public:
	Scheduler();
	void loadPatients(); //only function we need to implement for phase 1.2
	void simulate();
	void RandomWaitingEnqueue(Patient* p);
	void AddToWait_U(Patient* p);
	void AddToWait_E(Patient* p);
	void AddToWait_X(Patient* p);
	bool isEAvailable();
	bool isUAvailable();
	bool isXAvailable();
	void checkAllList();
	void FromAllToLists();
	void FromE_LToW();
	void moveFromInTreatment();
	void assign_E();
	void assign_U();
	void assign_X();
	Patient* RandomWaitingDequeue();
	friend class UI;
};