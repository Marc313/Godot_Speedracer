#pragma once

#include <Godot.hpp>
#include <Node.hpp>
#include <KinematicBody2D.hpp>
#include <time.h>

namespace godot {

class Enemy : public KinematicBody2D {
    GODOT_CLASS(Enemy, KinematicBody2D)

private:
    float speed;

    void onDeath();

public:
    static void _register_methods();

    Enemy();
    ~Enemy();

    void _init();
    void _ready();
    void _physics_process(float delta);
    void _process(float delta);
};}