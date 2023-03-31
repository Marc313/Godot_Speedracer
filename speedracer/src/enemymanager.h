#pragma once

#include "enemy.h"
#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <PackedScene.hpp>
#include <Node2D.hpp>
#include <time.h>
#include <vector>
#include <Timer.hpp>

namespace godot {

class EnemyManager : public Node2D {
    GODOT_CLASS(EnemyManager, Node2D)

private:
    std::vector<Enemy*> enemies;
    Ref<PackedScene> enemyPrefab;
    Node* uiManager;
    Node* gameManager;
    Timer* enemySpeedTimer;
    Timer* extraEnemyTimer;

    int numOfEnemiesOnStart;   // Property
    float enemySpawnInterval;   // Property
    float enemyTimerWaitTime;

    void add_enemy();
    // Registered Signals
    void _on_game_start();
    void _on_game_end();
    void _on_ExtraEnemyTimer_timeout();

public:
    static void _register_methods();

    EnemyManager();
    ~EnemyManager();

    void _init();
    void _ready();
    void _process(float delta);
};}