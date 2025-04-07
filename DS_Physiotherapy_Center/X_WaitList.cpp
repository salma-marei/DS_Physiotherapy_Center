#include "X_WaitList.h"

Patient* X_WaitList::cancel(int id)
{
	if (isEmpty())
		return nullptr;
	Patient* p = nullptr;
	int randNum = rand() % counter + 1;
	Node<Patient*>* current = frontPtr;
	if (randNum == 1)
	{
		p = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		counter--;
		if (counter == 0) backPtr = nullptr;
		return p;
	}
	for (int i = 0; i < randNum-2; i++)
	{
		current = current->getNext();
	}
	Node<Patient*>* temp = current->getNext();
	current->setNext(temp->getNext());
	p = temp->getItem();
	delete temp;
	counter--;
	if (!current->getNext()) backPtr = current;
	return p;
}