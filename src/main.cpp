#include "main.hpp"

#include <chrono>
#include <thread>
#include <vector>

#include <raylib.h>

#include "body.hpp"
#include "simulation.hpp"

constexpr int WIDTH = 1000;
constexpr int HEIGHT = 1000;

int main()
{
    Simulation* simulation = new Simulation();

    InitWindow(WIDTH, HEIGHT, "phys");

    while (!WindowShouldClose()) {
        simulation->tick();
        const std::vector<Body>& bodies = simulation->getBodies();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (auto body : bodies) {
            DrawCircle(static_cast<int>(body.getPosition().x), static_cast<int>(body.getPosition().y),
                       static_cast<float>(body.getRadius()), RED);
        }

        EndDrawing();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    CloseWindow();

    delete simulation;

    return 0;
}
