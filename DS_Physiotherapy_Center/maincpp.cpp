#include "scheduler.h"
using namespace std;
int  main() {
	Scheduler* S = new Scheduler();
	S->loadPatients();
	while (true)
	S->simulate();
	delete S;
}