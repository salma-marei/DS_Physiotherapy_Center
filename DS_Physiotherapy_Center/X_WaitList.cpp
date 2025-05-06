#include "X_WaitList.h"
#include <iostream>
Patient* X_WaitList::cancel()
{
	if (!counter)
		return nullptr;
	Patient* p = nullptr;
	int randNum = rand() % counter + 1;
	Node<Patient*>* current = frontPtr;
	if (randNum == 1)
	{
		p = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		counter--;
		if (counter == 0)
			backPtr = nullptr;
		return p;
	}
	for (int i = 0; i < randNum - 2; i++)
	{
		current = current->getNext();
	}
	Node<Patient*>* temp = current->getNext();
	current->setNext(temp->getNext());
	p = temp->getItem();
	counter--;
	delete temp;
	if (current->getNext() == nullptr)
		backPtr = current;
	return p;
}

int X_WaitList::XTreatmentLatency()
{
	Node<Patient*>* current = frontPtr;
	int time = 0;
	while (current) {
		time += current->getItem()->peekCurrentTreatment()->getDuration();
		current = current->getNext();
	}
	return time;
}
