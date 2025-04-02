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
	resources(int id, ResourceType T) {}
	resources(int id, ResourceType T, int cap) {}
	int getID() {}
	ResourceType getType() {
		return type;
	}
	bool getAvailability() {}
	void setAvailability(bool A) {}
	int getCapacity() {}
	int getCurrentOccupancy() {}
	bool isFull() {}
	void addpatient() {}
	void removepatient() {}
};