#include "scheduler.h"
using namespace std;
int  main() {
	Scheduler* S = new Scheduler();
	S->loadPatients();
	S->simulate();
	S->generateOutPutFile();
	delete S;
}