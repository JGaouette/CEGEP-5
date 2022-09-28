#pragma once

#include <iostream>

#include "Observer.hpp"

using namespace std;

class Firefighter : public Observer<string> {
public:
    string name;

    Firefighter(string name) {
        this->name = name;
    }

    ~Firefighter(){}
    
    void notification(string data) {
        cout << data;
    }
};
