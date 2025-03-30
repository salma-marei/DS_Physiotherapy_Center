#pragma once
#include"iostream"
using namespace std;
enum ResourceType { Electro, Ultrasound, GymRoom };
class resources {
private:
	int ID;
	ResourceType type;
	bool isAvailable;
	int capacity; // for gym
	int CurrentOccupants; // for gym
public:
	resources(int id, ResourceType T) :ID(id), type(T), isAvailable(true) {
		if (T == GymRoom) {
			cout << "gym must have a capacity ";
		}
	}
	resources(int id, ResourceType T, int cap) :ID(id), type(T), isAvailable(true), capacity(cap), CurrentOccupants(0) {
		if (T != GymRoom) {
			cout << "ultrasound and electro devices may have only one occupant ";
		}
	}
	int getID() {
		return ID;
	}
	ResourceType getType() {
		return type;
	}
	bool getAvailability() {
		return isAvailable;
	}
	void setAvailability(bool A) {
		isAvailable = A;
	}
	int getCapacity() {
		if (type == GymRoom) {
			return capacity;
		}
		/*else {
			cout << "error! attempted to get capacity of other devices ";
			return -1;
		}*/ 

		//mesh arfa mfrod a3ml el validations di wla laa, same for kol el validations ele taht
	}
	int getCurrentOccupancy() {
		if (type == GymRoom) {
			return CurrentOccupants;
		}
		/*else {
			cout << "error! attempted to get current occupancy of other devices ";
			return -1;
		}*/	

		if (type == GymRoom) {
			return CurrentOccupants;
		}
		/*else {
			cout << "error! attempted to get current occupancy of other devices ";
			return -1;
		}*/
	}
	bool isFull() {
		if (type == GymRoom) {
			if (CurrentOccupants <= capacity) {
				return false;
			}
			else {
				return true;
			}
		}
	}
	void addpatient() {
		if (type == GymRoom && !isFull()) {
			CurrentOccupants++;
		}
		else {
			cout << "gym is full ";
		
		}
	}
	void removepatient() {
		if (type == GymRoom && CurrentOccupants>0) {
			CurrentOccupants--;
		}
	}
};