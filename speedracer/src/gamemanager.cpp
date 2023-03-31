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
    delete input;
}

void GameManager::_init() {
    isGamePlaying = false;
    timer = 1.0f;
    time_to_restart = 1.0f;
    isTimer = false;
}

void GameManager::_ready() {
    input = Input::get_singleton();
}

void GameManager::_process(float delta) {
    // Change to press any key to continue
    if (!isGamePlaying && input->is_action_just_pressed("ui_accept")) {
        isGamePlaying = true;
        emit_signal("on_game_start");
    }

    // 'timer' ensures that the player can only restart the game after 1 second.
    // otherwise, the player might accidentally click on a button and restart immediately
    if (isTimer) {
        timer -= delta;
        if (timer <= 0.0f) {
            isTimer = false;
            isGamePlaying = false;
        }
    }
}

void GameManager::_on_player_death() {
    emit_signal("on_game_end");
    timer = time_to_restart;
    isTimer = true;
}