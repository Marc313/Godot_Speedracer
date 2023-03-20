#include "uimanager.h"
#include <string>

using namespace std;
using namespace godot;

void UIManager::_register_methods() {
    register_method("_ready", &UIManager::_ready);
    register_method("_process", &UIManager::_process);
    register_method("_on_enemy_death", &UIManager::_on_enemy_death);
    register_method("_on_player_death", &UIManager::_on_player_death);
    register_method("_on_game_start", &UIManager::_on_game_start);

}

UIManager::UIManager() {
}

UIManager::~UIManager() {

}

void UIManager::UpdateScoreText() {
    if (!scoreLabel) return;
    std::string newText = "Score: " + std::to_string(score);
    scoreLabel->set_text(newText.c_str());
}

void UIManager::_init() {
    score = 0;
}

void UIManager::_ready() {
    scoreLabel = static_cast<Label*>(get_node("Score"));
    endLabel = static_cast<Label*>(get_node("End Screen"));

    UpdateScoreText();
    Godot::print("Hoi");
}

void UIManager::_process(float delta) {

}

void UIManager::_on_enemy_death() {
    Godot::print("Enemy Death");
    score++;
    UpdateScoreText();
}

void UIManager::_on_player_death() {
    Godot::print("Player Death");
    if(scoreLabel) scoreLabel->set_visible(false);
    if(endLabel) endLabel->set_visible(true);
}

void UIManager::_on_game_start() {
    _init();
    _ready();
}
