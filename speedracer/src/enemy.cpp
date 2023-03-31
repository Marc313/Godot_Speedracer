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
    register_method("_on_speedtimer_timeout", &Enemy::_on_speedtimer_timeout);
    register_signal<Enemy>("enemy_death");

    // Properties
    register_property<Enemy, float>("min_speed", &Enemy::min_speed, 100.0f);
    register_property<Enemy, float>("max_speed", &Enemy::max_speed, 1000.0f);
    register_property<Enemy, float>("speed_increment", &Enemy::speed_increment, 250.0f);
}

Enemy::Enemy() {
}

Enemy::~Enemy() {

}

void Enemy::_init() {
    speed = 5000.0f;
    direction = Vector2(0.0f, 1.0f);
}

void Enemy::_ready() {
    random = static_cast<Ref<RandomNumberGenerator>>(RandomNumberGenerator::_new());

    speed = get_random_speed();
    direction = get_random_direction();
    set_position(get_random_screenpos());
}

void Enemy::_process(float delta) {
    if (get_position().y > get_viewport_rect().get_size().y + spriteHeight) 
    {
        on_death();
    }
}

void Enemy::_physics_process(float delta) {
    move_and_slide(speed * direction * delta);

    const Vector2 pos = get_position();

    // Inverse enemies xdirection on collision with border
    if (pos.x - spriteWidth/2 < 0 
        || pos.x + spriteWidth/2 > get_viewport_rect().get_size().x) 
    {
        direction.x = -direction.x;
    }
}

void Enemy::_on_game_end() {
    this->queue_free();
}

void Enemy::on_death() {
    emit_signal("enemy_death");
    _ready();
}

void godot::Enemy::_on_speedtimer_timeout()
{
    min_speed += speed_increment;
    max_speed += speed_increment;
    speed = get_random_speed();
}

const Vector2 Enemy::get_random_screenpos() {
    random->randomize();
    const int screenSizeX = get_viewport_rect().get_size().y;
    const float startX = random->randi() % screenSizeX;
    const Vector2 startPos = Vector2(startX, 0);
    return startPos;
}

const Vector2 Enemy::get_random_direction() {
    random->randomize();
    const float randX = random->randi() % 100 - 50;    // Value between -50 and 50
    const float randY = 100;    
    // randX is only -50 to 50, so the enemies can not go at and angle bigger than 45 degrees.
    return Vector2(randX, randY).normalized();
}

const float Enemy::get_random_speed() {
    random->randomize();
    const int randInterval = max_speed - min_speed;
    return (random->randi() % randInterval + min_speed);
}
