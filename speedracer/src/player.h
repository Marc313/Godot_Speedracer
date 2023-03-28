#include <Godot.hpp>
#include <Sprite.hpp>
#include <Input.hpp>
#include <KinematicBody2D.hpp>

namespace godot {

class Player : public KinematicBody2D {
    GODOT_CLASS(Player, KinematicBody2D)

private:
    float speed;
    float acceleration;
    float friciton;
    Vector2 velocity;
    Vector2 startPos;
    float spriteWidth;

    Input* input;

    void check_collisions();
    void _on_start();
    void on_death();
    void set_speed(float p_speed);
    float get_speed();

public:
    static void _register_methods();

    Player();
    ~Player();

    void _init();
    void _ready();
    void _process(float delta);
    void _physics_process(float delta);
};
}