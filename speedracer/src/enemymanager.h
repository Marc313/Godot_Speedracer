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

public:
    static void _register_methods();

    EnemyManager();
    ~EnemyManager();

    void _init();
    void _ready();
    void _process(float delta);
    Vector2 get_random_screenpos();
};}