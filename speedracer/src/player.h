#include <Godot.hpp>
#include <Sprite.hpp>
#include <Input.hpp>
#include <KinematicBody2D.hpp>

namespace godot {

class Player : public KinematicBody2D {
    GODOT_CLASS(Player, KinematicBody2D)

private:
    float time_passed;
    float time_emit;
    float speed;
    float acceleration;
    float friciton;
    Vector2 velocity;
    Vector2 startPos;

    Input* input;
    //Vector2 position;

    void check_collisions();

public:
    static void _register_methods();

    Player();
    ~Player();

    void _init();
    void _ready();
    void _process(float delta);
    void _physics_process(float delta);

    void _on_start();
    void set_speed(float p_speed);
    float get_speed();
};
}