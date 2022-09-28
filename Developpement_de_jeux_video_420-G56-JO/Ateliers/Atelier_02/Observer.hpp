#pragma once

#include <list>

using namespace std;

template <typename T>
class Observer {
public:
    virtual void notification(T data) = 0;
};

template <typename T>
class Observable {
private:
    list<Observer<T>*> observers;

public:
    void subscribe(Observer<T>* observer) {
        observers.push_back(observer);
    }

    void unsubscribe(Observer<T>* observer) {
        observers.remove(observer);
    }

    void notify(T data) {
        for (auto observer : observers) {
            observer->notification(data);
        }
    }
};