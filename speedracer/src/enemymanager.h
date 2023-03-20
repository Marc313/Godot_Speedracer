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
    int numOfEnemies;

    std::vector<Enemy*> enemies;
    Ref<PackedScene> enemyPrefab;
    Node* uiManager;

    void _on_game_start();
    void start_enemies();
    Vector2 get_random_screenpos();
    float get_random_speed(Enemy* enemy);

public:
    static void _register_methods();

    EnemyManager();
    ~EnemyManager();

    void _init();
    void _ready();
    void _process(float delta);

    static Vector2 get_random_direction();
    bool isTimer;
    float timer;

};}