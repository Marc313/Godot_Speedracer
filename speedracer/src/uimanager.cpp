#include "uimanager.h"
#include <string>

using namespace std;
using namespace godot;

void UIManager::_register_methods() {
    register_method("_ready", &UIManager::_ready);
    register_method("_process", &UIManager::_process);
    register_method("_on_enemy_death", &UIManager::_on_enemy_death);
}

UIManager::UIManager() {
}

UIManager::~UIManager() {

}

void UIManager::UpdateScoreText() {
    std::string newText = "Score: " + std::to_string(score);
    set_text(newText.c_str());
}

void UIManager::_init() {
    score = 0;
}

void UIManager::_ready() {
    UpdateScoreText();
    Godot::print("Ready");
}

void UIManager::_process(float delta) {

}

void UIManager::_on_enemy_death() {
    Godot::print("Death");
    score++;
    UpdateScoreText();
}
