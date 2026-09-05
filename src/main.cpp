#include "main.hpp"

#include <chrono>
#include <print>
#include <thread>

#include "simulation.hpp"

int main()
{
    Simulation* simulation = new Simulation(2);

    while (true) {
        simulation->tick();
        std::println("tick");
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    delete simulation;

    return 0;
}
