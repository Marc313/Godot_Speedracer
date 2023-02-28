#include "gdexample.h"
#include "player.h"
#include "enemy.h"
#include "enemymanager.h"
#include "uimanager.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

    // Register Classes
    godot::register_class<godot::GDExample>();
    godot::register_class<godot::Player>();
    godot::register_class<godot::Enemy>();
    godot::register_class<godot::EnemyManager>();
    godot::register_class<godot::UIManager>();
}