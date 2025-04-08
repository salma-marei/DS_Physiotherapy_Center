#pragma once
#include"iostream"
#include "LinkedQueue.h"
#include "Treatment.h"
#include "X_therapy.h"
#include "E_therapy.h"
#include "U_therapy.h"
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
    LinkedQueue<Treatment*> treatmentList;

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
		treatmentList.enqueue(t);
	}

    Treatment* peekCurrentTreatment() {
        Treatment* currentTreatment = nullptr;
        treatmentList.peek(currentTreatment);
        return currentTreatment;
    }

    Treatment* dequeueTreatment() {
        Treatment* t = nullptr;
        treatmentList.dequeue(t);
        return t;
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

    int getTreatmentTime(Treatment* type) {
        LinkedQueue<Treatment*> temp;
        int time = 0;
        Treatment* t = nullptr;
        treatmentList.dequeue(t);
        while (t)
        {
            temp.enqueue(t);
            if (dynamic_cast<X_therapy*>(t) && dynamic_cast<X_therapy*>(type))
                time = t->getDuration();
            else if (dynamic_cast<U_therapy*>(t) && dynamic_cast<U_therapy*>(type))
                time = t->getDuration();
            else if (dynamic_cast<E_therapy*>(t) && dynamic_cast<E_therapy*>(type))
                time = t->getDuration();
            t = nullptr;
            treatmentList.dequeue(t);
        }
        return time;
    }
    
    /* ~Patient() {

         Treatment* temp;
         while (treatments->dequeue(temp)) {
             delete temp;
         }
         delete treatments;
     }*/
   

};






















