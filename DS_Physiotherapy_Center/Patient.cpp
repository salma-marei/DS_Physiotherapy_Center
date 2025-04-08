#include "Patient.h"
#include "Treatment.h"
#include "E_therapy.h"
#include "U_therapy.h"
#include "X_therapy.h"
#include "resources.h"

int Patient::nextID = 0;

int Patient::getTreatmentTime(Treatment* type)
{
	LinkedQueue<Treatment*> temp;
	int time = 0;
	Treatment* t=nullptr;
	treatmentList.dequeue(t);
	while (t)
	{
		temp.enqueue(t);
		if (dynamic_cast<X_therapy*>(t) && dynamic_cast<X_therapy*>(type))
			time = t->getDuration();
		else if (dynamic_cast<U_therapy*>(t) && dynamic_cast<U_therapy*>(type))
			time = t->getDuration();
		else if (dynamic_cast<E_therapy*>(t) && dynamic_cast<E_therapy*>(type))
			time = t->getDuration();
		t = nullptr;
		treatmentList.dequeue(t);
	}
	return time;
}
ostream& operator<<(ostream& out, Patient* P)
{

	if (P->peekCurrentTreatment() == nullptr)
		out << P->getID();
	else
	{
		//Since no resource assignment takes place just put placeholder numbers for now
		char type= 'U';
		int ID = P->getID();
		/*switch (P->peekCurrentTreatment()->getAssignedResource()->getType())
		{
		case GymRoom:
			type = 'X';
			break;
		case Ultrasound:
			type = 'U';
			break;
		case Electro:
			type = 'E';
			break;
		}
		int ID=P->peekCurrentTreatment()->getAssignedResource()->getID();
		*/
		out << "P" << P->getID() << "_" << type << ID;
	}
	return out;
}