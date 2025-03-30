#pragma once
#include "priQueue.h"
#include "Patient.h"
#include <cstdlib>  
#include <ctime>  

class EarlyPList : public priQueue<Patient*> {
public:
	bool reschedule(int Presc) {
		int randNum = rand() % 101;
		if (isEmpty() || randNum >= Presc) return false;
		int totalPatients = getCount();
		int randPat = rand() % totalPatients; //generates number from 0->totalPatients-1

		Patient* rescPatient;
		int rescPriority;
		Patient* tempPatient;
		int tempPri;
		priQueue<Patient*> tempQueue;

		for (int i = 0; i < randPat; i++) {
			dequeue(tempPatient, tempPri);
			tempQueue.enqueue(tempPatient, tempPri);
		}

		dequeue(rescPatient, rescPriority);

		while (!tempQueue.isEmpty()) {
			tempQueue.dequeue(tempPatient, tempPri);
			enqueue(tempPatient, tempPri);
		}

		int oldPT = -rescPriority;
		int newPT = oldPT + (rand() % 10) + 1; //adds to the oldPT a random number between 1-10
		//rescPatient->setPT(newPT);
		enqueue(rescPatient, -newPT);
		return true;
	}
};