#include "main.hpp"

#include <chrono>
#include <print>
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

    Body body1(glm::dvec2(-20.0, 20.0), 1, 1);
    Body body2(glm::dvec2(+20.0, 20.0), 5, 5);

    body1.applyAcceleration(glm::dvec2(500.0, 0.0));
    body2.applyAcceleration(glm::dvec2(-500.0, 0.0));

    simulation->addBody(body1);
    simulation->addBody(body2);

    InitWindow(WIDTH, HEIGHT, "phys");

    while (!WindowShouldClose()) {
        simulation->tick();
        const std::vector<Body>& bodies = simulation->getBodies();

        BeginDrawing();
        ClearBackground(BLACK);
        for (auto body : bodies) {
            std::println("Position: {}, {}", body.getPosition().x, body.getPosition().y);

            glm::dvec2 screen_position = worldToScreen(body.getPosition());
            DrawCircle(static_cast<int>(screen_position.x), static_cast<int>(screen_position.y),
                       static_cast<float>(body.getRadius() * 10), RED);
        }

        simulation->getBoundingBox().debugDraw(GREEN);

        EndDrawing();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    CloseWindow();

    delete simulation;

    return 0;
}
