#include <chrono>

using namespace std::chrono;


class Chrono {
private:
public:
    steady_clock::time_point start;

    Chrono();
    
    void start(){
        start = steady_clock::now();
    }


    double delta(){
        return duration_cast<nanoseconds>(steady_clock::now() - start).count() / 1000000000.0;
    }

    void reset(){
        start = steady_clock::now();
    }
};