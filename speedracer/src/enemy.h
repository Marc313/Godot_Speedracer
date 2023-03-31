#pragma once

#include <Godot.hpp>
#include <Node.hpp>
#include <KinematicBody2D.hpp>
#include <time.h>
#include <RandomNumberGenerator.hpp>

namespace godot {

class Enemy : public KinematicBody2D {
    GODOT_CLASS(Enemy, KinematicBody2D)

private:
    const float spriteWidth = 50;
    const float spriteHeight = 100;

    float min_speed;
    float max_speed;
    float speed_increment;
    float speed;
    Vector2 startPosition;
    Vector2 direction;
    Ref<RandomNumberGenerator> random;

    void on_death();
    void _on_speedtimer_timeout();
    const Vector2 get_random_screenpos();
    const Vector2 get_random_direction();
    const float get_random_speed();

public:
    static void _register_methods();

    Enemy();
    ~Enemy();

    void _init();
    void _ready();
    void _physics_process(float delta);
    void _process(float delta);
    void _on_game_end();
};}