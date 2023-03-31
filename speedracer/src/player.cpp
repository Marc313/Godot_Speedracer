#pragma once

#include "player.h"
#include <KinematicCollision2D.hpp>
#include <string>
#include <algorithm>

using namespace godot;

void Player::_register_methods() {
    register_method("_process", &Player::_process);
    register_method("_ready", &Player::_ready);
    register_method("_physics_process", &Player::_physics_process);

    register_method("_on_start", &Player::_on_start);

    register_property<Player, float>("acceleration", &Player::acceleration, 10000.0f);
    register_property<Player, float>("friction", &Player::friciton, 10.0f);

    register_signal<Player>((char *)"player_death");
}

Player::Player() {
}

Player::~Player() {
    delete input;
}

void Player::_init() 
{
    // initialize any variables here
    speed = 1000.0f;
    acceleration = 10000.0f;
    friciton = acceleration/speed;
    velocity = Vector2();
    spriteWidth = 50.0f;
}

void Player::_ready()
{
    input = Input::get_singleton();
    startPos = get_position();
}

void Player::_process(float delta) 
{
    Vector2 direction(0, 0);
    if (input->is_action_pressed("move_left")) 
    {
        direction.x = -1;
    }
    if (input->is_action_pressed("move_right")) 
    {
        direction.x = 1;
    }


    velocity += direction * acceleration * delta;
    velocity -= velocity * friciton * delta;
}

void Player::_physics_process(float delta) 
{
    move_and_slide(velocity);
    const Vector2 pos = get_position();
    if (pos.x - spriteWidth/2 < 0 || pos.x + spriteWidth/2 > get_viewport_rect().get_size().x) 
    {
        set_position(Vector2(std::clamp(pos.x, 0.0f + spriteWidth/2, get_viewport_rect().get_size().x - spriteWidth/2), pos.y));
    }

    check_collisions();
}

void Player::check_collisions() 
{
    for (int i = 0; i < get_slide_count(); i++)
    {
        Ref<KinematicCollision2D> collision = get_slide_collision(i);
        Node2D* colliderNode = static_cast<Node2D*>(collision->get_collider());

        // If collider is in enemy group, player is hit.
        if ((colliderNode->is_in_group("Enemy"))) {
            on_death();
        }
    }
}

void Player::_on_start()
{
    this->set_visible(true);
    set_position(startPos);
}

void Player::on_death() 
{
    this->set_visible(false);
    emit_signal("player_death");
}

void Player::set_speed(float _speed)
{
    speed = _speed;
}

float Player::get_speed() 
{
    return speed;
}
