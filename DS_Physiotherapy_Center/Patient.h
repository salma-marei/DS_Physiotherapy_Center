#pragma once
#include"iostream"
#include "LinkedQueue.h"
#include "Treatment.h"
using namespace std;

class Treatment;

class Patient {

private:
    int nextID;
    const int id;
    const char type;
    int appointmentTime;
    const int arrivalTime;
    int status;
    int finishTime;

    LinkedQueue<Treatment*> required_treatment_list;

public:

    Patient(char t, int pt, int vt) :
        id(nextID++),type(t), appointmentTime(pt), arrivalTime(vt),
        status(0), finishTime(-1) {}


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
		required_treatment_list.enqueue(t);
	}

    // ha implement hena al required treatment list 

    void setPT(int pt) { appointmentTime = pt; }
    
    void print() {
        cout << "P" << id << " ";

        if (type == 'N')
            cout << "N" << " ";
        else {
            cout << "R" << " ";
        }

        cout << appointmentTime << " " << arrivalTime << endl;

    }
    
    /* ~Patient() {

         Treatment* temp;
         while (treatments->dequeue(temp)) {
             delete temp;
         }
         delete treatments;
     }*/
   

};






















