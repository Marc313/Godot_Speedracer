#include "gdexample.h"

using namespace godot;

void GDExample::_register_methods() {
    register_method("_process", &GDExample::_process);
    register_property<GDExample, float>("amplitude", &GDExample::amplitude, 10.0);
    register_property<GDExample, float>("speed", &GDExample::set_speed, &GDExample::get_speed, 1.0);

    register_signal<GDExample>((char *)"position_changed", "node", GODOT_VARIANT_TYPE_OBJECT, "new_pos", GODOT_VARIANT_TYPE_VECTOR2);
}

GDExample::GDExample() {
    input = Input::get_singleton();
}

GDExample::~GDExample() {
    // add your cleanup here
}

void GDExample::_init() {
    // initialize any variables here
    position = Vector2(0, 0);
    time_passed = 0.0;
    time_emit = 0.0;
    amplitude = 10.0;
    speed = 1.0;
}

void GDExample::_process(float delta) {
    //time_passed += speed * delta;

    // Vector2 new_position = Vector2(
    //     amplitude + (amplitude * sin(time_passed * 2.0)),
    //     amplitude + (amplitude * cos(time_passed * 1.5))
    // );

    Vector2 direction(0, 0);
    if (input->is_action_pressed("move_left")) 
    {
        direction.x = -1;
    }
    if (input->is_action_pressed("move_right")) 
    {
        direction.x = 1;
    }

    position = position + direction * speed * delta;

    set_position(position);

    
    time_emit += delta;
    if (time_emit > 1.0) {
        emit_signal("position_changed", this, position);

        time_emit = 0.0;
    }
}

void GDExample::set_speed(float _speed) {
    speed = _speed;
}

float GDExample::get_speed() {
    return speed;
}