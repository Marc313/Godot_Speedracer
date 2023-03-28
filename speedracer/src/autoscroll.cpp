#pragma once

#include "autoscroll.h"

using namespace godot;

void Autoscroll::_register_methods() {
    register_method("_process", &Autoscroll::_process);

    register_property<Autoscroll, float>("Scroll Speed", &Autoscroll::scrollSpeed, 500.0f);
}

Autoscroll::Autoscroll() {
}

Autoscroll::~Autoscroll() {

}

void Autoscroll::_init() {
    scrollSpeed = 500.0f;
}

void Autoscroll::_process(float delta) {
    const float newScrollOffsetY = get_scroll_offset().y + scrollSpeed * delta;
    set_scroll_offset(Vector2(get_scroll_offset().x, newScrollOffsetY));
}
