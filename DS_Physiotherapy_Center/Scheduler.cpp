#include "Scheduler.h"
#include <fstream>
#include <iostream>
#include "Treatment.h"
#include "E_therapy.h"
#include "U_therapy.h"
#include "X_therapy.h"


Scheduler::Scheduler()
{
	timestep = numPatients = numE = numX = numU = 0;
	pUI = nullptr;
	pResc = 10;
	pUI = new UI(this);
	
}

void Scheduler::loadPatients()
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "error loading file";
		exit(1);
		return;
	}												// reading number of resources
		file >> numE >> numU >> numX;

		for (int i = 0; i < numE; i++) {
			resources* Edevice = new resources( i + 1, Electro, 1);				// allocating Edevices
			EDevices.enqueue(Edevice);
		}
		for (int i = 0; i < numU; i++) {
			resources* Udevice = new resources(i + 1, Ultrasound, 1);			// allocating Udevices	
			UDevices.enqueue(Udevice);
		}

		int* capacity = new int[numX];
		for (int i = 0; i < numX; i++)											// reading capacity of each gym room
		{
			file >> capacity[i];
			resources* Xroom = new resources(i + 1, GymRoom, capacity[i]);		// allocating Xrooms
			XRooms.enqueue(Xroom);
		}
		int Pcancel, Presc;
		file >> Pcancel >> Presc;
		
		//int numPatients;
		file >> numPatients;
		
		for (int i = 0; i < numPatients; i++) {
			char PatientType;
			int PT, VT, NT;														// appointment, arrival time and number of treatments
			file >> PatientType >> PT >> VT >> NT;
			Patient* p = new Patient(PatientType, PT, VT);
			for (int j = 0; j < NT; j++) {
				char TreatmentType;
				int TreatmentDuration;
				file >> TreatmentType >> TreatmentDuration;						// reading treatment type and duration
				Treatment* t = nullptr;
				switch (TreatmentType)
				{
				case 'E':
					t = new E_therapy(TreatmentDuration);
					break;
				case 'U':
					t = new U_therapy(TreatmentDuration);
					break;
				case 'X':
					t = new X_therapy(TreatmentDuration);
					break;
				}
				p->enqueueTreatment(t);
				t->setAssignedPatient(p);
			}
			AllList.enqueue(p);	
		}
		file.close();
}

void Scheduler::simulate()
{
	FromAllToLists();
	
	//while (FinishedPatients.getCount()<numPatients)
	//{
	//	checkAllList();
	//	int x = rand() % 100;
	//	if (x < 10)
	//	{
	//		Patient* p = nullptr;
	//		int t;
	//		EarlyList.dequeue(p,t);
	//		if(p)
	//			RandomWaitingEnqueue(p);
	//	}
	//	else if(x<20)
	//	{ 
	//		Patient* p = nullptr;
	//		int t;
	//		LateList.dequeue(p, t);
	//		if (p)
	//			RandomWaitingEnqueue(p);
	//	}
	//	else if (x < 40)
	//	{
	//		Patient* p = RandomWaitingDequeue();
	//		int t=1;//???
	//		if (p)
	//			InTreatmentList.enqueue(p, t);

	//		p = RandomWaitingDequeue();
	//		t = 1;///???
	//		if (p)
	//			InTreatmentList.enqueue(p, t);
	//	}
	//	else if (x < 50)
	//	{
	//		Patient* p = nullptr;
	//		int t;
	//		InTreatmentList.dequeue(p,t);
	//		if (p)
	//			RandomWaitingEnqueue(p);
	//	}
	//	else if (x < 60)
	//	{
	//		Patient* p = nullptr;
	//		int t;
	//		InTreatmentList.dequeue(p, t);
	//		if (p)
	//			FinishedPatients.push(p);
	//	}
	//	else if (x < 70)
	//	{
	//		Patient* p = nullptr;
	//		p = XWaitList.cancel();
	//		if (p)
	//			FinishedPatients.push(p);
	//	}
	//	else if (x < 80)
	//	{
	//		EarlyList.reschedule(pResc); // returns true if rescheduling happened false otherwise
	//	}
		
			pUI->printInterface();
		timestep++;
	//}
}

void Scheduler::RandomWaitingEnqueue(Patient* p)
{
	int random = rand() % 100;
	if (random < 33)
		AddToWait_E(p);
	else if (random < 66)
		AddToWait_U(p);
	else
		AddToWait_X(p);

}

void Scheduler::AddToWait_U(Patient* p)
{
	if(p->getVT()<=p->getPT())
		UWaitList.enqueue(p);
	else
	{
		int penalty = (p->getVT() - p->getPT()) / 2;
		UWaitList.insertSorted(p, penalty);
	}
}

void Scheduler::AddToWait_E(Patient* p)
{
	if (p->getVT() <= p->getPT())
		EWaitList.enqueue(p);
	else
	{
		int penalty = (p->getVT() - p->getPT()) / 2;
		EWaitList.insertSorted(p, penalty);
	}
}

void Scheduler::AddToWait_X(Patient* p)
{
	if (p->getVT() <= p->getPT())
		XWaitList.enqueue(p);
	else
	{
		int penalty = (p->getVT() - p->getPT()) / 2;
		XWaitList.insertSorted(p, penalty);
	}
}

bool Scheduler::isEAvailable()
{
	return !EDevices.isEmpty();
}

bool Scheduler::isUAvailable()
{
	return !UDevices.isEmpty();

}

bool Scheduler::isXAvailable()
{
	return !XRooms.isEmpty();
}

void Scheduler::checkAllList()
{
	Patient* p = nullptr;
	AllList.peek(p);
	while (p && p->getVT() <= timestep)
	{
		AllList.dequeue(p);
		if (p->getPT() < p->getVT())
		{
			int penalty = (p->getPT() + p->getVT()) / 2;
			LateList.enqueue(p,-(p->getVT() + penalty));
		}
		else if (p->getPT() > p->getVT())
			EarlyList.enqueue(p,-p->getPT());
		else
			p->peekCurrentTreatment()->MoveToWait(this);
		p = nullptr;
		AllList.peek(p);
	}
}

void Scheduler::FromAllToLists()
{
	Patient* p = nullptr;
	AllList.peek(p);
	while (p && p->getVT() <= timestep) // while (p->getStatus()!=IDLE)
	{
		AllList.dequeue(p);
		if (p->getPT() < p->getVT())
		{
			int penalty = (p->getPT() + p->getVT()) / 2;
			LateList.enqueue(p, -(p->getVT() + penalty));
			p->setStatus(Patient::LATE);
		}
		else if (p->getPT() > p->getVT()) {
			EarlyList.enqueue(p, -p->getPT());
			p->setStatus(Patient::ERLY);
		}
		else {
			if (p->getType() == 'N') 
				p->peekCurrentTreatment()->MoveToWait(this);
			else if (p->getType() == 'R') {
				RPhandling(p);
			}
			p->setStatus(Patient::WAIT);
		}
		p = nullptr;
		AllList.peek(p);
	}

}

void Scheduler::moveFromInTreatment()
{
	Patient* p = nullptr;
	int priority;
	InTreatmentList.peek(p,priority);
	priority = -priority;
	while (p && priority <= timestep) {
		InTreatmentList.dequeue(p, priority);

		Treatment* t = nullptr;
		p->dequeueTreatment(t);
		resources* r= t->getAssignedResource();
		t->setAssignedResource(nullptr);
		switch (r->getType())
		{
		case Electro:
			EDevices.enqueue(r);
			break;
		case Ultrasound:
			UDevices.enqueue(r);
			break;
		case GymRoom:
			if (r->isFull())
			{
				XRooms.enqueue(r);
			}
			r->removepatient();
			break;
		}
		delete t;
		t = nullptr;
		t = p->peekCurrentTreatment();
		if (!t) {
			FinishedPatients.push(p);
			p->setStatus(Patient::FNSH);
		}
		else {
			if (p->getType() == 'N') t->MoveToWait(this);

			else  RPhandling(p);
			p->setStatus(Patient::WAIT);
		}
		p = nullptr;
		InTreatmentList.peek(p, priority);
		priority = -priority;

	}

}
void Scheduler::assign_E(int timestep, resources* eDevices, Patient* p)
{

	while (isEAvailable()) {
		EWaitList.dequeue(p);
		EDevices.dequeue(eDevices);
		p->peekCurrentTreatment()->setAssignedResource(eDevices);
		p->peekCurrentTreatment()->setAssignmentTime(timestep);
		//isEAvailable() == false;
		int finishTime = timestep + p->peekCurrentTreatment()->getDuration();
		InTreatmentList.enqueue(p, finishTime);
		p->setStatus(Patient::SERV);
	}
}

void Scheduler::assign_U(int timestep, resources* uDevices, Patient* p)
{
	while (isUAvailable()) {
		UWaitList.dequeue(p);
		UDevices.dequeue(uDevices);
		p->peekCurrentTreatment()->setAssignedResource(uDevices);
		p->peekCurrentTreatment()->setAssignmentTime(timestep);
		//isUAvailable() == false;
		int finishTime = timestep + p->peekCurrentTreatment()->getDuration();
		InTreatmentList.enqueue(p, finishTime);
		p->setStatus(Patient::SERV);
	}
}

void Scheduler::assign_X(int timestep, resources* UDevices, Patient* p)
{

}



void Scheduler::CheckEarlyandLateLists()
{
	Patient* p = nullptr;
	int time;
	EarlyList.peek(p,time);
	time = -time;
	while (p && p->getPT() <= timestep)
	{
		EarlyList.dequeue(p, time);
		Treatment* treatment = p->peekCurrentTreatment();
		treatment->MoveToWait(this);
		p = nullptr;
		EarlyList.peek(p, time);
		time = -time;
	}
	LateList.peek(p, time);
	time = -time;
	while (p && p->getPT() <= timestep)
	{
		EarlyList.dequeue(p, time);
		Treatment* treatment = p->peekCurrentTreatment();
		treatment->MoveToWait(this);
		p = nullptr;
		EarlyList.peek(p, time);
		time = -time;
	}
}

void Scheduler::RPhandling(Patient* p)
{
	bool X = false, U = false, E = false;
	int TLU = 0, TLE = 0, TLX = 0;
	LinkedQueue<Treatment*> temp;
	Treatment* t = nullptr;

	while (p->dequeueTreatment(t)) {
		temp.enqueue(t);

		resources* r;
		r = t->getAssignedResource();
		ResourceType type = ResourceType::Electro;
		if (type == ResourceType::Electro) TLE = EWaitList.calcTreatmentLatency(t);
		else if (type == ResourceType::Ultrasound) TLU = UWaitList.calcTreatmentLatency(t);
		else TLX = XWaitList.XTreatmentLatency();
	}

	int minimum;

	if (TLU <= TLE && TLU <= TLX) {
		minimum = TLU;
		U = true;
	}
	else if (TLE <= TLU && TLE <= TLX) {
		minimum = TLE;
		E = true;
	}
	else {
		minimum = TLX;
		X = true;
	}

	if (X) XWaitList.enqueue(p);
	else if (E) EWaitList.enqueue(p);
	else UWaitList.enqueue(p);

	while (temp.dequeue(t)) p->enqueueTreatment(t);
}



//delete
Patient* Scheduler::RandomWaitingDequeue()
{
	Patient* p = nullptr;
	int random = rand() % 100;
	if (random < 33)
		EWaitList.dequeue(p);
	else if(random < 66)
		UWaitList.dequeue(p);
	else
		XWaitList.dequeue(p);
	return p;
}

//MoveServing()
//peak inTreatment
//check if patient finished current treatment
//