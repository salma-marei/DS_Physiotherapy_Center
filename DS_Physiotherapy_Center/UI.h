#ifndef UICLASS
#define UICLASS

#include <iostream>
#include "cstdlib"

using namespace std;

class Scheduler;
class UI
{
	bool interactive;				

	Scheduler* scheduler;		


public:

	UI(Scheduler* s);

	bool isInteractive();

	void printInterface();
	void printAllList();
};
#endif

