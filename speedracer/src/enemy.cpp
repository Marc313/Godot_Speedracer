#include "enemy.h"
#include <string>

using namespace godot;

void Enemy::_register_methods() {
    register_method("_ready", &Enemy::_ready);
    register_method("_process", &Enemy::_process);
    register_method("_physics_process", &Enemy::_physics_process);

    register_property<Enemy, float>("speed", &Enemy::speed, 100.0f);

    register_signal<Enemy>("enemy_death");
}

Enemy::Enemy() {
    // int screenSizeX = get_viewport_rect().get_size().y;
    // float startX = rand() % screenSizeX;

}

Enemy::~Enemy() {

}

void Enemy::_init() {
    speed = 1000.0f;
}

void Enemy::_ready() {
    int screenSizeX = get_viewport_rect().get_size().y;
    float startX = rand() % screenSizeX;
    Vector2 startPos = Vector2(startX, 0);
    set_position(startPos);
    Godot::print("Position: " + startPos);
    Godot::print(("Speed: " + std::to_string(speed)).c_str());
}

void Enemy::_process(float delta) {
    move_and_slide(speed * Vector2(0, delta));

    if (get_position().y > get_viewport_rect().get_size().y + 100) 
    {
        onDeath();
    }

}

void Enemy::_physics_process(float delta) {

}

void Enemy::onDeath() {
    queue_free();
    emit_signal("enemy_death");
    Godot::print("Enemy died");
}
