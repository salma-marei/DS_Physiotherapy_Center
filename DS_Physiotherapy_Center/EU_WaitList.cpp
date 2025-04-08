#include "EU_waitlist.h"

void EU_WaitList::insertSorted(Patient* patient, int penalty)
{
	Node<Patient*>* newNode = new Node<Patient*>(patient);
	if (isEmpty() || patient->getPT() + penalty > frontPtr->getItem()->getPT()) {
		newNode->setNext(frontPtr);
		frontPtr = newNode;
		if (!backPtr) backPtr = frontPtr;
		return;
	}
	Node<Patient*>* current = frontPtr;
	while (current->getNext() && patient->getPT() + penalty <= current->getItem()->getPT())
	{
		current = current->getNext();
	}
	if (current->getNext() == nullptr)
	{
		current->setNext(newNode);
		backPtr = newNode;
	}
	else
	{
		newNode->setNext(current->getNext());
		current->setNext(newNode);
	}
}

int EU_WaitList::calcTreatmentLatency(Treatment* t)
{
	int treatmentLatency = 0;
	Node<Patient*>* current = frontPtr;
	while (current) {
		treatmentLatency += current->getItem()->getTreatmentTime(t);
		current = current->getNext();
	}	
	return treatmentLatency;
}
