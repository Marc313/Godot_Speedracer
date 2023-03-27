#pragma once

#include "gamemanager.h"
#include "Input.hpp"

using namespace godot;

void GameManager::_register_methods() {
    register_method("_ready", &GameManager::_ready);
    register_method("_process", &GameManager::_process);

    register_method("_on_player_death", &GameManager::_on_player_death);
    register_signal<GameManager>("on_game_end");
    register_signal<GameManager>("on_game_start");
}

GameManager::GameManager() {
}

GameManager::~GameManager() {

}

void GameManager::_init() {
    timer = 100.0f;
    time_to_restart = 3.0f;
    isTimer = false;
}

void GameManager::_ready() {
    
}

void GameManager::_process(float delta) {
    if (isTimer) {
        timer -= delta;
        if (timer <= 0.0f) {
            isTimer = false;
            emit_signal("on_game_start");
        }
    }

    // if (Input::get_singleton()->is_action_just_pressed("move_left")) {
    //     _on_player_death();

    // }
}

void GameManager::_on_player_death() {
    emit_signal("on_game_end");
    timer = time_to_restart;
    isTimer = true;
}