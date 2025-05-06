#include "UI.h"
#include "Scheduler.h"

UI::UI(Scheduler* s)
{
	scheduler = s;
	cout << "Choose Running Mode\nEnter S For Silent Mode\nEnter I For Interactive Mode\n";
	char input;
	cin >> input;
	while (tolower(input) != 's' && tolower(input) != 'i')
	{
		cout << "\nPlease Enter I or S\n";
		cin >> input;
	}
	switch (tolower(input))
	{
	case 's':
		interactive = false;
		break;
	case 'i':
		interactive = true;
		break;
	}
	cout << "Enter Filename to load " << endl;
	cin >> s->filename;
}

bool UI::isInteractive()
{
	return interactive;
}

void UI::printInterface()
{
	system("cls");
	cout << "Current Timestep:   " << scheduler->timestep << endl;
	cout << "==============   ALL List   ==============\n";
	printAllList();

	cout << "==============   Waiting Lists   ==============\n";
	cout << scheduler->EWaitList.getCount() << " E-Therapy patients: ";
	scheduler->EWaitList.print();
	cout << endl;

	cout << scheduler->UWaitList.getCount() << " U-Therapy patients: ";
	scheduler->UWaitList.print();
	cout << endl;

	cout << scheduler->XWaitList.getCount() << " X-Therapy patients: ";
	scheduler->XWaitList.print();
	cout << endl;

	cout << "==============   Early List   ==============\n";
	cout << scheduler->EarlyList.getCount() << " patients : ";
	scheduler->EarlyList.print();
	cout << endl;

	cout << "==============   Late List   ==============\n";
	cout << scheduler->LateList.getCount() << " patients : ";
	scheduler->LateList.print();
	cout << endl;

	cout << "==============   Avail E-Devices   ==============\n";
	cout << scheduler->EDevices.getCount() << " Electro Devices : ";
	scheduler->EDevices.print();
	cout << endl;

	cout << "==============   Avail U-Devices   ==============\n";
	cout << scheduler->UDevices.getCount() << " Ultra Devices : ";
	scheduler->UDevices.print();
	cout << endl;

	cout << "==============   Avail X-Rooms   ==============\n";

	cout << scheduler->XRooms.getCount() << " rooms : ";
	scheduler->XRooms.print();
	cout << endl;

	cout << "==============   In-Treatment List   ==============\n";
	cout << scheduler->InTreatmentList.getCount() << " ==> ";
	scheduler->InTreatmentList.print();
	cout << endl;
	cout << "-----------------------------------------------------\n";
	cout << scheduler->FinishedPatients.getCount() << " Finished patient : ";
	scheduler->FinishedPatients.print();
	cout << endl;
	cout << "Press Any Key To Display Next Timestep\n";
	cin.get();
}

void UI::printAllList()
{
	cout << scheduler->numPatients - scheduler->FinishedPatients.getCount() << " Patients Remaining : ";
	LinkedQueue<Patient*> temp;/// VERY SCARY MIGHT NEED TO BE CHANGED(could corrupt memory)(spoiler alert it did corrupt memory)
	int i = 0;
	while (!scheduler->AllList.isEmpty())
	{
		Patient* p = nullptr;
		scheduler->AllList.dequeue(p);
		if (!p)
			break;
		if (i < 10)
			p->print();
		i++;
		temp.enqueue(p);
	}
	while (!temp.isEmpty())
	{
		Patient* p;
		temp.dequeue(p);
		scheduler->AllList.enqueue(p); 
	}
	cout << endl;
}
