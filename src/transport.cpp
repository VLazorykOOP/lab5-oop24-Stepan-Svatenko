#include <iostream>
#include <string>
#include <map>
#include "tasks.h"

using namespace std;

class Transport {
protected:
    string name;
public:
    Transport(const string& name = "Unknown Transport") : name(name) {
        cout << "Transport constructor: " << name << endl;
    }

    virtual ~Transport() {
        cout << "Transport destructor: " << name << endl;
    }

    virtual void print() const {
        cout << "Transport: " << name << endl;
    }
};

class Car : public Transport {
protected:
    int seats;
public:
    Car(const string& name = "Car", int seats = 4) : Transport(name), seats(seats) {
        cout << "Car constructor: " << name << endl;
    }

    ~Car() override {
        cout << "Car destructor: " << name << endl;
    }

    void print() const override {
        cout << "Car: " << name << ", seats: " << seats << endl;
    }
};

class Truck : public Car {
    double loadCapacity;
public:
    Truck(const string& name = "Truck", int seats = 2, double loadCapacity = 5.0)
        : Car(name, seats), loadCapacity(loadCapacity) {
        cout << "Truck constructor: " << name << endl;
    }

    ~Truck() override {
        cout << "Truck destructor: " << name << endl;
    }

    void print() const override {
        cout << "Truck: " << name << ", seats: " << seats
             << ", load capacity: " << loadCapacity << " tons" << endl;
    }
};

class Ship : public Transport {
    int crewSize;
public:
    Ship(const string& name = "Ship", int crewSize = 10)
        : Transport(name), crewSize(crewSize) {
        cout << "Ship constructor: " << name << endl;
    }

    ~Ship() override {
        cout << "Ship destructor: " << name << endl;
    }

    void print() const override {
        cout << "Ship: " << name << ", crew size: " << crewSize << endl;
    }
};

class Plane : public Transport {
    int maxAltitude;
public:
    Plane(const string& name = "Plane", int maxAltitude = 10000)
        : Transport(name), maxAltitude(maxAltitude) {
        cout << "Plane constructor: " << name << endl;
    }

    ~Plane() override {
        cout << "Plane destructor: " << name << endl;
    }

    void print() const override {
        cout << "Plane: " << name << ", max altitude: " << maxAltitude << " meters" << endl;
    }
};

void transport_unit() {

    Transport* t[] = {
        new Car("BMW", 5),
        new Truck("Volvo Truck", 2, 8.5),
        new Ship("Titanic", 30),
        new Plane("Boeing 737", 12000)
    };

    cout << "\n--- Calling print() ---\n";
    for (int i = 0; i < 4; ++i) {
        t[i]->print();
    }

    cout << "\n--- Deleting objects ---\n";
    for (int i = 0; i < 4; ++i) {
        delete t[i];
    }

}
