#include "scheduler.h"
using namespace std;
int  main() {
	Scheduler* S = new Scheduler();
	S->simulate();
	delete S;
}