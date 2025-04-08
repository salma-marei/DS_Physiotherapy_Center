#include "EarlyPList.h"
bool EarlyPList::reschedule(int Presc) {
	int randNum = rand() % 101;
	if (isEmpty() || randNum >= Presc) return false;
	int totalPatients = getCount();
	int randPat = rand() % totalPatients + 1; //generates number from 1->totalPatients

	Patient* rescPatient;
	int rescPriority;
	priNode<Patient*>* current = head;
	if (randPat == 1) {
		rescPatient = head->getItem(rescPriority);
		head = head->getNext();
		counter--;
	}
	else {
		for (int i = 0; i < randPat - 2; i++) {
			current = current->getNext();
		}
		priNode<Patient*>* temp = current->getNext();
		current->setNext(temp->getNext());
		rescPatient = temp->getItem(rescPriority);
		counter--;
		delete temp;
	}

	int oldPT = -rescPriority;
	int newPT = oldPT + (rand() % 10) + 1; //adds to the oldPT a random number between 1-10
	rescPatient->setPT(newPT);
	enqueue(rescPatient, -newPT);
	return true;
}