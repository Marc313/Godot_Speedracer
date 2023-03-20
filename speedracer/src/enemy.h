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


    void onDeath();
    Vector2 get_random_screenpos();
    Vector2 get_random_direction();
    float get_random_speed();

public:
    static void _register_methods();

    Enemy();
    ~Enemy();

    void _init();
    void _ready();
    void _physics_process(float delta);
    void _process(float delta);
    void on_start(Vector2 _startPos, Vector2 _direction, float _speed);
    void test();

// Temp
        float speed;
    Vector2 startPosition;
    Vector2 direction;
};}