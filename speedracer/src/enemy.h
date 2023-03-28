#pragma once

#include <Godot.hpp>
#include <Node.hpp>
#include <KinematicBody2D.hpp>
#include <time.h>

namespace godot {

class Enemy : public KinematicBody2D {
    GODOT_CLASS(Enemy, KinematicBody2D)

private:
    float min_speed;
    float max_speed;

    float speed;
    Vector2 startPosition;
    Vector2 direction;
    float spriteWidth;

    void onDeath();
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