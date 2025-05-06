#pragma once
#include "EU_WaitList.h"
#include "Treatment.h"
class X_WaitList : public EU_WaitList
{
public:
	Patient* cancel();
	int XTreatmentLatency();
};

