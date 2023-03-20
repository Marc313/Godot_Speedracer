#include <string>
#include <algorithm>
#include "enemy.h"
#include "enemymanager.h"

using namespace godot;
using namespace std;

void Enemy::_register_methods() {
    // Godot methods
    register_method("_init", &Enemy::_init);
    register_method("_ready", &Enemy::_ready);
    register_method("_process", &Enemy::_process);
    register_method("_physics_process", &Enemy::_physics_process);

    // Signals
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

    speed = 5111.11f;
    direction = Vector2(0.0f, 1.0f);
}

void Enemy::_ready() {
    Godot::print("Hello");
    Godot::print(("Speed: " + std::to_string(speed)).c_str());
    //set_position(Vector2(100.0f, 100.0f));
    //on_start();
}

void Enemy::_process(float delta) {
    if (get_position().y > get_viewport_rect().get_size().y + 100) 
    {
        onDeath();
    }
}

void Enemy::_physics_process(float delta) {
    move_and_slide(speed * direction * delta);

    Vector2 pos = get_position();
    // Variant 1: Clamp enemy pos
    // pos.x = std::clamp(pos.x, 0.0f, get_viewport_rect().get_size().x);
    // set_position(pos);

    // Variant 2: Change enemy xdirection
    //if (pos.x < 0 || pos.x > get_viewport_rect().get_size().x)
    //direction.x = EnemyManager::get_random_direction().x;
}

// void Enemy::on_start() {
//     speed = get_random_speed();
//     direction = get_random_direction();
//     set_position(get_random_screenpos());

//     Godot::print(("Speed: " + std::to_string(speed)).c_str());
// }

void Enemy::on_start(Vector2 _startPos, Vector2 _direction, float _speed) {
    speed = _speed;
    direction = _direction;
    set_position(_startPos);
    //startPosition = _startPos;

    //Godot::print(("Speed: " + std::to_string(speed)).c_str());
}

void godot::Enemy::test()
{
    Godot::print("TEST");
}

void Enemy::onDeath() {
    emit_signal("enemy_death");
    //on_start();
}

// Vector2 Enemy::get_random_screenpos() {
//     int screenSizeX = get_viewport_rect().get_size().y;
//     float startX = rand() % screenSizeX;
//     Vector2 startPos = Vector2(startX, 0);
//     return startPos;
// }

// Vector2 Enemy::get_random_direction() {
//     float randX = rand() % 200 - 100;
//     float randY = rand() % 100 + 1;
//     return Vector2(randX, randY).normalized();
// }

// float Enemy::get_random_speed() {
//     int randInterval = max_speed - min_speed;
//     return (rand() % randInterval + min_speed)/3;
// }
