#include "main.hpp"

#include <chrono>
#include <print>
#include <ratio>
#include <thread>
#include <vector>

#include <glm/ext/vector_double2.hpp>
#include <raylib.h>

#include "body.hpp"
#include "simulation.hpp"
#include "util.hpp"

int main()
{
    Simulation* simulation = new Simulation();

    simulation->addRandomBodies(20);

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, "phys");

    while (!WindowShouldClose()) {
        auto total_start = std::chrono::high_resolution_clock::now();

        simulation->tick();

        auto render_start = std::chrono::high_resolution_clock::now();

        const std::vector<Body>& bodies = simulation->getBodies();
        BeginDrawing();
        ClearBackground(BLACK);
        for (auto body : bodies) {
            glm::dvec2 screen_position = worldToScreen(body.getPosition());
            DrawCircle(static_cast<int>(screen_position.x), static_cast<int>(screen_position.y),
                       static_cast<float>(body.getRadius() * PIXELS_PER_METER), body.getColor());
        }

        simulation->getBoundingBox().debugDraw(GREEN);

        EndDrawing();

        auto render_end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> total_time = render_end - total_start;
        std::chrono::duration<double, std::milli> simulation_time = render_start - total_start;
        std::chrono::duration<double, std::milli> render_time = render_end - render_start;

        std::println("Time: {:.3f}ms total, {:.3f}ms simulation, {:.3f}ms render", total_time.count(),
                     simulation_time.count(), render_time.count());

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    CloseWindow();

    delete simulation;

    return 0;
}
