#include <chrono>

using namespace std::chrono;


class Chrono {
private:
public:
    steady_clock::time_point start;
    steady_clock::time_point stop;

    Chrono();
    
    void start(){

    }

    void stop();
    void reset();
    double getElapsedTime();
};