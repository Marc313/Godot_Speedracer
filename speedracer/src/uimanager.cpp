#include "uimanager.h"
#include <string>

using namespace std;
using namespace godot;

void UIManager::_register_methods() {
    // Godot Methods
    register_method("_ready", &UIManager::_ready);
    register_method("_on_enemy_death", &UIManager::_on_enemy_death);
    register_method("_on_game_end", &UIManager::_on_player_death);
    register_method("_on_game_start", &UIManager::_on_game_start);
}

UIManager::UIManager() {
}

UIManager::~UIManager() {
    delete scoreLabel;
    delete endLabel;
    delete pressToContinueLabel;
}

void UIManager::_init() {
    score = 0;
}

void UIManager::_ready() {
    scoreLabel = static_cast<Label*>(get_node("Score"));
    endLabel = static_cast<Label*>(get_node("End Screen"));
    pressToContinueLabel = static_cast<Label*>(get_node("PressToCont"));

    if(pressToContinueLabel) pressToContinueLabel->set_visible(true);
    if(scoreLabel) scoreLabel->set_visible(false);

    UpdateScoreText();
}

void UIManager::UpdateScoreText() {
    if (!scoreLabel) return;
    std::string newText = "Score: " + std::to_string(score);
    scoreLabel->set_text(newText.c_str());
}

void UIManager::_on_enemy_death() {
    score++;
    UpdateScoreText();
}

void UIManager::_on_player_death() {
    if(scoreLabel) scoreLabel->set_visible(false);
    if(pressToContinueLabel) pressToContinueLabel->set_visible(true);
    if(endLabel) endLabel->set_visible(true);
}

void UIManager::_on_game_start() {
    if(scoreLabel) scoreLabel->set_visible(true);
    if(endLabel) endLabel->set_visible(false);
    if(pressToContinueLabel) pressToContinueLabel->set_visible(false);

    score = 0;
    UpdateScoreText();
}
