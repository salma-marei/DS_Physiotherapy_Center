#include "X_WaitList.h"

Patient * X_WaitList::cancel(int id)
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
	}
	if (counter == randNum)
	{
		backPtr = nullptr;
	}
	for (int i = 0; i < counter-2; i++)
	{
		current = current->getNext();
	}

	counter--;
	Node<Patient*>* current = frontPtr;
	while(current && current->getItem()->getID()!=id)
}
