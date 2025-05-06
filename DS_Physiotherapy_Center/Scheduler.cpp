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
	NTT = 0;
	RTT = 0;
	
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

void Scheduler::generateOutPutFile()
{
	ofstream outfile("outputfile.txt");
	if (!outfile.is_open())
	{
		cout << "error opening file";
		return;
	}
	outfile << "PID \t" << "Ptype \t" << "PT \t" << "VT \t" << "FT \t" << "WT \t" << "TT \t"
	<< "Cancel \t" << "Reschedule \t" << endl;
	Patient* p = nullptr;	
	int totalPatients=0, numNPatients=0, numRPatients=0;
	int totalWT = 0, totalTT = 0, latePenaltySum = 0;
	int earlyCount = 0, lateCount = 0, cancelCount = 0, rescCount = 0;
	int totalNWT = 0, totalRWT = 0;
	ArrayStack <Patient*> tempstack;
	while (!FinishedPatients.isEmpty()) {
		FinishedPatients.pop(p);
	
		outfile << p->getID() << "\t" << p->getType() << "\t" << p->getPT() << "\t" << p->getVT() << "\t" << p->getFT() << "\t"
			<< p->getWT() << "\t" << p->calcTT() << "\t" << (p->getcancelled() ? "T" : "F") << "\t" << (p->getrescheduled() ? "T" : "F") << endl;;

		totalPatients++;
		totalWT += p->getWT();
		totalTT += p->calcTT();
		if (p->getType() == 'N') {
			numNPatients++;
			totalNWT += p->getWT();
		}
		if (p->getType() == 'R') {
			numRPatients++;
			totalRWT += p->getWT();
		}
		if (p->getVT() < p->getPT()) earlyCount++;
		if (p->getVT() > p->getPT())
		{
			lateCount++;
			latePenaltySum += (p->getVT() - p->getPT() + 1) / 2; 
		}
		if (p->getcancelled()) cancelCount++;
		if (p->getrescheduled()) rescCount++;


		tempstack.push(p);
	}
	while (!tempstack.isEmpty()) {
		tempstack.pop(p);
		FinishedPatients.push(p);
	}
	outfile << "total number of timesteps = " << timestep << endl;
	outfile << "total number of all, N, R patients = " << totalPatients << "\t " << numNPatients << "\t " << numRPatients << endl;
	if (numNPatients != 0 && numRPatients != 0)
	{
		outfile << "Average total waiting time for all, N, and R patients = " << (totalWT / totalPatients) << "\t " << (totalNWT / numNPatients)
			<< "\t " << (totalRWT / numRPatients) << endl;
		outfile << "Average total treatment time for all, N, and R patients = " << (totalTT / totalPatients) << "\t " << (NTT / numNPatients)
			<< "\t " << (RTT / numRPatients) << endl;
	}
	if (totalPatients != 0)
	{
		outfile << "Percentage of patients of an accepted cancellation (%) = " << ((float)cancelCount / totalPatients) * 100 << endl;
		outfile << "Percentage of patients of an accepted reschedule (%) = " << ((float)rescCount / totalPatients) * 100 << endl;
		outfile << "Percentage of early patients (%) = " << ((float)earlyCount / totalPatients) * 100 << endl;
		outfile << "Percentage of late patients (%) = " << ((float)lateCount / totalPatients) * 100 << endl;
		if(lateCount!=0)
			outfile << "Average late penalty = " << (latePenaltySum / lateCount) << "timestep(s)" << endl;
	}

}

void Scheduler::simulate()
{
	//loadPatients();
	while (FinishedPatients.getCount() < numPatients) {
		FromAllToLists();
		CheckEarlyandLateLists();
		moveFromInTreatment();
		assign_E();
		assign_U();
		assign_X();
		EarlyList.reschedule(pResc); //need to check
		XWaitList.cancel(); //need to check 
		pUI->printInterface();
		timestep++;
	}
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
	p->setStartWait(timestep); // set start wait time
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
	p->setStartWait(timestep); // set start wait time
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
	p->setStartWait(timestep); // set start wait time
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
		t= p->dequeueTreatment();
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
		if (p->getType() == 'N') {
			NTT += t->getDuration();
		}
		if (p->getType() == 'R') {
			RTT += t->getDuration();
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
void Scheduler::assign_E()
{
	Patient* p = nullptr;
	resources* eDevices = nullptr;
	while (!EWaitList.isEmpty() && isEAvailable()) {
		p = nullptr;
		eDevices = nullptr;

		EWaitList.dequeue(p);
		if (!p)
			return;
		EDevices.dequeue(eDevices);
		//if (!eDevices)
			//return;
		eDevices->setAvailability(false);
		p->peekCurrentTreatment()->setAssignedResource(eDevices);
		p->peekCurrentTreatment()->setAssignmentTime(timestep);
		//isEAvailable() == false;
		int finishTime = timestep + p->peekCurrentTreatment()->getDuration();
		InTreatmentList.enqueue(p, - finishTime);
		p->setStatus(Patient::SERV);
		p->setendWait(timestep - p->getStartWait());
		p->setWT(p->getWT() + p->getendWait());
	}

}

void Scheduler::assign_U()
{
	Patient* p=nullptr;
	resources* uDevices = nullptr;
	while (!UWaitList.isEmpty() && isUAvailable()) {
		p = nullptr;
		uDevices = nullptr;
		UWaitList.dequeue(p);
		if (!p)
			return;
		UDevices.dequeue(uDevices);
		//if (!uDevices)
			//return;
		uDevices->setAvailability(false);
		p->peekCurrentTreatment()->setAssignedResource(uDevices);
		p->peekCurrentTreatment()->setAssignmentTime(timestep);
		//isUAvailable() == false;
		int finishTime = timestep + p->peekCurrentTreatment()->getDuration();
		InTreatmentList.enqueue(p, - finishTime);
		p->setStatus(Patient::SERV);
		p->setendWait(timestep - p->getStartWait());
		p->setWT(p->getWT() + p->getendWait());
	}

}

void Scheduler::assign_X() {
	Patient* p = nullptr;
	resources* xDevices = nullptr;
	//XRooms.getCount();
	while (!XWaitList.isEmpty() && isXAvailable()) {
		p = nullptr;
		xDevices = nullptr;
		XWaitList.dequeue(p);
		if (p==nullptr)
			return;
		//XRooms.dequeue(xDevices);
		XRooms.peek(xDevices);
		//if (!xDevices)
			//return;
		p->peekCurrentTreatment()->setAssignedResource(xDevices);
		p->peekCurrentTreatment()->setAssignmentTime(timestep);
		xDevices->addpatient();
		//isUAvailable() == false;
		int finishTime = timestep + p->peekCurrentTreatment()->getDuration();
		InTreatmentList.enqueue(p, - finishTime);
		p->setStatus(Patient::SERV);
		if (xDevices->isFull())
		{
			xDevices->setAvailability(false);
			XRooms.dequeue(xDevices);
		}
		p->setendWait(timestep - p->getStartWait());
		p->setWT(p->getWT() + p->getendWait());
	}

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
		LateList.dequeue(p, time);
		Treatment* treatment = p->peekCurrentTreatment();
		treatment->MoveToWait(this);
		p = nullptr;
		LateList.peek(p, time);
		time = -time;
	}
}

void Scheduler::RPhandling(Patient* p)
{
	bool X = false, U = false, E = false;
	int TLU = 0, TLE = 0, TLX = 0;
	LinkedQueue<Treatment*> temp;
	LinkedQueue<Treatment*> temp2;
	Treatment* t = nullptr;

	while (t = p->dequeueTreatment()) {
		temp.enqueue(t);

		//resources* r;
		//r = t->getAssignedResource();
		//ResourceType type = ResourceType::Electro;
		if(dynamic_cast<E_therapy*>(t))
			TLE = EWaitList.calcTreatmentLatency(t);
		if (dynamic_cast<U_therapy*>(t))
			TLU = UWaitList.calcTreatmentLatency(t);
		if (dynamic_cast<X_therapy*>(t))
			TLX = XWaitList.XTreatmentLatency();
		t = nullptr;
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
	while (temp.dequeue(t))
	{
		if (X && dynamic_cast<X_therapy*>(t))
		{
			p->enqueueTreatment(t);
		}
		else if (E && dynamic_cast<E_therapy*>(t))
		{
			p->enqueueTreatment(t);
		}
		else if (U && dynamic_cast<U_therapy*>(t))
		{
			p->enqueueTreatment(t);
		}
		else
		{
			temp2.enqueue(t);
		}
	}
	t = nullptr;
	while (temp2.dequeue(t)) p->enqueueTreatment(t);

	p->peekCurrentTreatment()->MoveToWait(this);
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