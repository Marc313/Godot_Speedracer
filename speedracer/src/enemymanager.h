#pragma once

#include "enemy.h"
#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <PackedScene.hpp>
#include <Node2D.hpp>
#include <time.h>
#include <vector>

namespace godot {

class EnemyManager : public Node2D {
    GODOT_CLASS(EnemyManager, Node2D)

private:
    std::vector<Enemy*> enemies;
    Ref<PackedScene> enemyPrefab;
    Node* uiManager;
    Node* gameManager;

    int numOfEnemies;   // Property
    void _on_game_start();  // Registered Signal
    bool isTimer;
    float timer;
    // Vector2 get_random_screenpos();
    // float get_random_speed(Enemy* enemy);
    // static Vector2 get_random_direction();

public:
    static void _register_methods();

    EnemyManager();
    ~EnemyManager();

    void _init();
    void _ready();
    void _process(float delta);
};}