#include <string>
#include <algorithm>
#include "enemy.h"
#include "enemymanager.h"
#include "CollisionShape2D.hpp"

using namespace godot;
using namespace std;

void Enemy::_register_methods() {
    // Godot methods
    register_method("_init", &Enemy::_init);
    register_method("_ready", &Enemy::_ready);
    register_method("_process", &Enemy::_process);
    register_method("_physics_process", &Enemy::_physics_process);

    // Signals
    register_method("_on_game_end", &Enemy::_on_game_end);
    register_method("_on_game_start", &Enemy::_ready);
    register_signal<Enemy>("enemy_death");

    // Properties
    register_property<Enemy, float>("min_speed", &Enemy::min_speed, 100.0f);
    register_property<Enemy, float>("max_speed", &Enemy::max_speed, 1000.0f);
}

Enemy::Enemy() {
}

Enemy::~Enemy() {

}

void Enemy::_init() {
    min_speed = 100.0f;

    speed = 5000.0f;
    direction = Vector2(0.0f, 1.0f);
}

void Enemy::_ready() {
    speed = get_random_speed();
    set_position(get_random_screenpos());
    direction = get_random_direction();

    //spriteWidth = static_cast<CollisionShape2D*>(get_node("CollisionShape2D"))->get_shape();
    spriteWidth = 50.0f;

    Godot::print(("Speed: " + std::to_string(speed)).c_str());
    Godot::print(("Min_Speed: " + std::to_string(min_speed)).c_str());
    Godot::print(("Max_Speed: " + std::to_string(max_speed)).c_str());
}

void Enemy::_process(float delta) {
    if (get_position().y > get_viewport_rect().get_size().y + 100) 
    {
        onDeath();
    }
}

void Enemy::_physics_process(float delta) {
    move_and_slide(speed * direction * delta);

    const Vector2 pos = get_position();
    // Variant 1: Clamp enemy pos
    // if (pos.x - spriteWidth/2 < 0 || pos.x + spriteWidth/2 > get_viewport_rect().get_size().x) 
    // {
    //     set_position(Vector2(std::clamp(pos.x, 0.0f + spriteWidth/2, get_viewport_rect().get_size().x - spriteWidth/2), pos.y));
    // }

    // Variant 2: Change enemy xdirection
    if (pos.x - spriteWidth/2 < 0 
        || pos.x + spriteWidth/2 > get_viewport_rect().get_size().x) 
    {
        direction.x = get_random_direction().x;
    }
}

// void Enemy::on_start() {
//     speed = get_random_speed();
//     direction = get_random_direction();
//     set_position(get_random_screenpos());

//     Godot::print(("Speed: " + std::to_string(speed)).c_str());
// }

void Enemy::_on_game_end() {
    this->queue_free();
}

void Enemy::onDeath() {
    emit_signal("enemy_death");
    _ready();
    //on_start();
}

const Vector2 Enemy::get_random_screenpos() {
    const int screenSizeX = get_viewport_rect().get_size().y;
    const float startX = rand() % screenSizeX;
    const Vector2 startPos = Vector2(startX, 0);
    return startPos;
}

const Vector2 Enemy::get_random_direction() {
    const float randX = rand() % 100 - 50;    // Value between -50 and 50
    const float randY = 100;    
    // randX is only -50 to 50, so the enemies can not go at and angle bigger than 45 degrees.
    return Vector2(randX, randY).normalized();
}

const float Enemy::get_random_speed() {
    const int randInterval = max_speed - min_speed;
    return (rand() % randInterval + min_speed);
}
