#pragma once

#include <Godot.hpp>
#include <Node.hpp>
#include <Label.hpp>

namespace godot {

class UIManager : public Label {
    GODOT_CLASS(UIManager, Label)

private:
    int score;

    void UpdateScoreText();

public:
    static void _register_methods();

    UIManager();
    ~UIManager();

    void _init();
    void _ready();
    void _process(float delta);

    // Public or private?
    void _on_enemy_death();
};}