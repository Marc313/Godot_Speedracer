#pragma once

#include <Godot.hpp>
#include <Node2D.hpp>
#include <Label.hpp>

namespace godot {

class UIManager : public Node2D {
    GODOT_CLASS(UIManager, Node2D)

private:
    Label* scoreLabel;
    Label* endLabel;
    Label* pressToContinueLabel;

    int score;
    void UpdateScoreText();

    // Receiving Signals
    void _on_enemy_death();
    void _on_player_death();
    void _on_game_start();

public:
    static void _register_methods();

    UIManager();
    ~UIManager();

    void _init();
    void _ready();
    //void _process(float delta);
};}