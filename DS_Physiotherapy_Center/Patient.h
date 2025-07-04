#pragma once
#include <iostream>
#include "LinkedQueue.h"
using namespace std;

// ha include class treatment lma rowida tkhalaso
class Treatment;

class Patient {
public:
    enum Status {
        IDLE,   // Patient hasn't arrived yet
        ERLY,   // Patient arrived before PT
        LATE,   // Patient arrived after PT
        WAIT,   // Waiting for treatment
        SERV,   // In treatment session
        FNSH    // Finished all treatments
    };

private:
    static int nextID;
    const int id;
    const char type;
    int appointmentTime;
    const int arrivalTime;
    Status status;
    int finishTime;
    int WT;
	int TT;
    int startWait;
    int endWait;
    bool cancelled;
    bool rescheduled;
    //resources* currentResource;
    LinkedQueue<Treatment*> treatmentList;

public:
    
    Patient(char t, int pt, int vt) :
        id(++nextID),type(t), appointmentTime(pt), arrivalTime(vt),
        status(IDLE), finishTime(-1) 
    {
		cancelled = false;
		rescheduled = false;
        WT = 0;
        TT = 0;
        //currentResource = nullptr;
    }
    int calcTT();

    //setters w getters l kol al data members 
    int getID() { return id; }
    char getType() { return type; }
    int getPT() { return appointmentTime; }
    int getVT() { return arrivalTime; }
    int getStatus() { return status; }
    void setStatus(Status s) { status = s; }
    int getFT() { return finishTime; }
    void setFT(int ft) { finishTime = ft; }
	int getWT() { return WT; }
	void setWT(int wt) { WT = wt; }
	int getStartWait() { return startWait; }
	void setStartWait(int st) { startWait = st; }
	int getendWait() { return endWait; }
	void setendWait(int et) { endWait = et; }
    bool getcancelled () {return cancelled;}
    bool getrescheduled() { return rescheduled;  }
    void setCancelled(bool canc);
    void setRescheduled(bool resc);

	bool enqueueTreatment(Treatment* t) { // lma a3mel enqueue l treatment 
		return treatmentList.enqueue(t);
	}
    //void setCurrentTreatment(resources* r)
    //{
        //currentResource = r;
    //}
    Treatment* peekCurrentTreatment()
    {
       // return currentResource;
        Treatment* t = nullptr;
        treatmentList.peek(t);
        return t;
    }
     
    Treatment* dequeueTreatment()
    {
        Treatment* t=nullptr;
        treatmentList.dequeue(t);
        return t;
    }
    void setPT(int pt) { appointmentTime = pt; }
    
    void print() {
        cout << "P" << appointmentTime << "_" << arrivalTime << ", ";
    }
    int getTreatmentTime(Treatment* type);
    /* ~Patient() {

         Treatment* temp;
         while (treatments->dequeue(temp)) {
             delete temp;
         }
         delete treatments;
     }*/
   
};
ostream& operator << (ostream& out, Patient* P);






















