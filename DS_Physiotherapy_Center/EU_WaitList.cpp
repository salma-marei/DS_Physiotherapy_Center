#include "EU_WaitList.h"

void EU_WaitList::insertSorted(Patient*patient,int penalty)
{
	Node<Patient*>* newNode = new Node<Patient*>(patient);
	//insert in beginning
	if (isEmpty() || patient->getPT()+penalty < frontPtr->getItem()->getPT()) {
		newNode->setNext(frontPtr);
		frontPtr = newNode;
		if (!backPtr) backPtr = frontPtr;
		return;
	}
	Node<Patient*>* current = frontPtr;
	while (current->getNext() && patient->getPT() + penalty >= current->getItem()->getPT())
	{
		current = current->getNext();
	}
	if (current->getNext() == nullptr)
	{
		current->setNext(newNode);
		backPtr = newNode;
	}
	elses
	{
		newNode->setNext(current->getNext());
		current->setNext(newNode);
	}
}
