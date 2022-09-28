#include "Observer.hpp"

#include <map>
#include <string>

using namespace std;

class Dispatcher {
private:
    map<string, Observable<string>*> incidents;
public:
    void addIncident(string name){
        incidents[name] = new Observable<string>();
    }

    void removeIncident(string name){
        delete incidents[name];
        incidents.erase(name);
    }

    void available(string incident, Observer<string>* responder){
        incidents[incident]->subscribe(responder);
    }

    void unavailable(string incident, Observer<string>* responder){
        incidents[incident]->unsubscribe(responder);
    }

    void notify(string incident, string address){
        incidents[incident]->notify(address);
    }
};