#include "main.hpp"

#include <chrono>
#include <print>
#include <thread>
#include <vector>

#include <raylib.h>

#include "body.hpp"
#include "simulation.hpp"

constexpr int WIDTH = 1000;
constexpr int HEIGHT = 1000;

Vec2 worldToScreen(Vec2 position)
{
    Vec2 screen_position{};

    screen_position.x = position.x * 10;
    screen_position.y = HEIGHT - position.y * 10;

    return screen_position;
}

int main()
{
    Simulation* simulation = new Simulation();

    Body body1(Vec2{.x = 20, .y = 20}, 1, 1);
    Body body2(Vec2{.x = 80, .y = 20}, 10, 10);

    simulation->addBody(body1);
    simulation->addBody(body2);

    InitWindow(WIDTH, HEIGHT, "phys");

    while (!WindowShouldClose()) {
        simulation->tick();
        const std::vector<Body>& bodies = simulation->getBodies();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (auto body : bodies) {
            std::println("Position: {}, {}", body.getPosition().x, body.getPosition().y);

            Vec2 screen_position = worldToScreen(body.getPosition());
            DrawCircle(static_cast<int>(screen_position.x), static_cast<int>(screen_position.y),
                       static_cast<float>(body.getRadius() * 10), RED);
        }

        EndDrawing();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    CloseWindow();

    delete simulation;

    return 0;
}
