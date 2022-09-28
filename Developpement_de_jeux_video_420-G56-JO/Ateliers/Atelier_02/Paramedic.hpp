#pragma once

#include <iostream>

#include "Observer.hpp"

using namespace std;

class Paramedic : public Observer<string> {
public:
    string name;

    Paramedic(string name) {
        this->name = name;
    }

    ~Paramedic(){}
    
    void notification(string data) {
        cout << data;
    }
};
