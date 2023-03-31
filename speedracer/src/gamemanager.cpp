#pragma once

#include "gamemanager.h"
#include "Input.hpp"
#include "time.h"

using namespace godot;

void GameManager::_register_methods() {
    register_method("_ready", &GameManager::_ready);
    register_method("_process", &GameManager::_process);
    //register_method("_input", &GameManager::_input);

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
    srand(time(NULL));
    input = Input::get_singleton();
}

void GameManager::_process(float delta) {
    // Change to press any key to continue
    if (!isGamePlaying && input->is_action_just_pressed("ui_accept")) {
        isGamePlaying = true;
        emit_signal("on_game_start");
    }

    if (isTimer) {
        timer -= delta;
        if (timer <= 0.0f) {
            isTimer = false;
            isGamePlaying = false;
            //emit_signal("on_game_start");
        }
    }
}

// void GameManager::_input(InputEvent& event) {
//     if (isGamePlaying) return;

//     InputEventKey& eventKey = static_cast<InputEventKey&>(event);
//     if (eventKey != nullptr && eventKey->pressed)
// }

void GameManager::_on_player_death() {
    emit_signal("on_game_end");
    timer = time_to_restart;
    isTimer = true;
}