#include "resources.h"
//resources::resources(int id, ResourceType T) :ID(id), type(T), isAvailable(true) {
//	if (T == GymRoom) {
//		cout << "gym must have a capacity ";
//	}
//}
resources::resources(int id, ResourceType T, int cap) :ID(id), type(T) {
	isAvailable = true;
	CurrentOccupants = 0;
	capacity = cap;
}
int resources::getID() {
	return ID;
}
bool resources::getAvailability() {
	return isAvailable;
}
void resources::setAvailability(bool A) {
	isAvailable = A;
}
int resources::getCapacity() {
	if (type == GymRoom) {
		return capacity;
	}
	/*else {
		cout << "error! attempted to get capacity of other devices ";
		return -1;
	}*/

	//mesh arfa mfrod a3ml el validations di wla laa, same for kol el validations ele taht
}
int resources::getCurrentOccupancy() {
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
bool resources::isFull() {
	if (type == GymRoom) {
		if (CurrentOccupants <= capacity) {
			return false;
		}
		else {
			return true;
		}
	}
}
void resources::addpatient() {
	if (type == GymRoom && !isFull()) {
		CurrentOccupants++;
	}
	else {
		cout << "gym is full ";

	}
}
void resources::removepatient() {
	if (type == GymRoom && CurrentOccupants > 0) {
		CurrentOccupants--;
	}
}
