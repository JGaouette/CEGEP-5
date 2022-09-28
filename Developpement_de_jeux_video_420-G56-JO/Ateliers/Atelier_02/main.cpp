#include "Dispatcher.hpp"
#include "Policeman.hpp"
#include "Firefighter.hpp"
#include "Paramedic.hpp"


    int main(){
        Dispatcher dispatcher;

        Policeman* policeman = new Policeman("John");
        Firefighter* firefighter = new Firefighter("Mike");
        Paramedic* paramedic = new Paramedic("Mary");

        dispatcher.addIncident("Feu");
        dispatcher.addIncident("Accident");
        dispatcher.addIncident("Hospitalisation");
        dispatcher.addIncident("Catastrophe");


        dispatcher.available("Feu", firefighter);
        dispatcher.available("Accident", policeman);
        dispatcher.available("Hospitalisation", paramedic);
        dispatcher.available("Catastrophe", policeman);
        dispatcher.available("Catastrophe", paramedic);
        dispatcher.available("Catastrophe", paramedic);


        dispatcher.notify("Feu", "Rue de la Paix");
        dispatcher.notify("Catastrophe", "Destruction city mf");

        return 0;
    }
