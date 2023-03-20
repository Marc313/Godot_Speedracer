#pragma once

#include "gamemanager.h"
#include "Input.hpp"

using namespace godot;

void GameManager::_register_methods() {
    register_method("_ready", &GameManager::_ready);
    register_method("_process", &GameManager::_process);

    register_signal<GameManager>("on_game_end");
    register_signal<GameManager>("on_game_start");
}

GameManager::GameManager() {
}

GameManager::~GameManager() {

}

void GameManager::_init() {

}

void GameManager::_ready() {
    
}

void GameManager::_process(float delta) {
    if (Input::get_singleton()->is_action_just_pressed("move_left")) {
        emit_signal("on_game_start");
    }
}
