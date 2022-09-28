#pragma once

#include <iostream>

#include "Observer.hpp"

using namespace std;

class Policeman : public Observer<string> {
public:
    string name;

    Policeman(string name) {
        this->name = name;
    }

    void notification(string data) {
        cout << name << "se dirige vers " << data << endl;
    }
};
