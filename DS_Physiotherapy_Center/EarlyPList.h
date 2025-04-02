#pragma once
#include "priQueue.h"
#include "Patient.h"
#include <cstdlib>  
#include <ctime>  

class EarlyPList : public priQueue<Patient*> {
public:
	bool reschedule(int Presc) {}
};