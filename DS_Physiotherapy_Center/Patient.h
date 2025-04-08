#pragma once
#include <iostream>
#include "LinkedQueue.h"
using namespace std;

// ha include class treatment lma rowida tkhalaso
class Treatment;

class Patient {

private:
    static int nextID;
    const int id;
    const char type;
    int appointmentTime;
    const int arrivalTime;
    int status;
    int finishTime;
    //resources* currentResource;
    LinkedQueue<Treatment*> treatmentList;

public:

    Patient(char t, int pt, int vt) :
        id(++nextID),type(t), appointmentTime(pt), arrivalTime(vt),
        status(0), finishTime(-1) 
    {
        //currentResource = nullptr;
    }


    //setters w getters l kol al data members 
    int getID() { return id; }
    char getType() { return type; }
    int getPT() { return appointmentTime; }
    int getVT() { return arrivalTime; }
    int getStatus() { return status; }
    void setStatus(int s) { status = s; }
    int getFT() { return finishTime; }
    void setFT(int ft) { finishTime = ft; }

	void enqueueTreatment(Treatment* t) { // lma a3mel enqueue l treatment 
		treatmentList.enqueue(t);
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
    // ha implement hena al required treatment list 
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






















