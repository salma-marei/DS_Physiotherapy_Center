#include "scheduler.h"
using namespace std;
int  main() {
	Scheduler S;
	S.loadPatients("test1.txt");
	cout << "test1.txt loaded successfully" << endl;
}