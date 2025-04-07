#include "Scheduler.h"
#include <fstream>
#include <iostream>
#include "Treatment.h"

Scheduler::Scheduler()
{
	timestep = 1;
}

void Scheduler::loadPatients(string filename)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "error loading file";
		//cout << "weeeeee";
		return;
	}
		int numE, numU, numX;													// reading number of resources
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
		
		int numPatients;
		file >> numPatients;
		Treatment* treatments[3];// reading number of patients
		treatments[0] = nullptr;
		treatments[1] = nullptr;
		treatments[2] = nullptr;

		for (int i = 0; i < numPatients; i++) {
			char PatientType;
			int PT, VT, NT;														// appointment, arrival time and number of treatments
			file >> PatientType >> PT >> VT >> NT;
			for (int j = 0; j < NT; j++) {
				char TreatmentType;
				int TreatmentDuration;
				file >> TreatmentType >> TreatmentDuration;						// reading treatment type and duration
				//treatments[j] = new Treatment(TreatmentType, TreatmentDuration);	// allocating treatments
			}
			AllList.enqueue(new Patient(PatientType, PT, VT));				// allocating patients
		}
		file.close();
}
