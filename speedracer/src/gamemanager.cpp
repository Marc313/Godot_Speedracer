#pragma once

#include "gamemanager.h"
#include "Input.hpp"
#include "time.h"

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
    srand(time(NULL));
}

void GameManager::_process(float delta) {
    // Change to press any key to continue
    if (isTimer) {
        timer -= delta;
        if (timer <= 0.0f) {
            isTimer = false;
            emit_signal("on_game_start");
        }
    }
}

void GameManager::_on_player_death() {
    emit_signal("on_game_end");
    timer = time_to_restart;
    isTimer = true;
}