#pragma once
#include"iostream"
#include "LinkedQueue.h"
using namespace std;


// ha include class treatment lma rowida tkhalaso

class Patient {

private:
    int nextID;
    const int id;
    const char type;
    const int appointmentTime;
    const int arrivalTime;
    int status;
    int finishTime;
    //LinkedQueue<Treatment*> required treatment list;

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
    

    // ha implement hena al required treatment list 


    void print() {
        cout << "P" << id;

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






















}