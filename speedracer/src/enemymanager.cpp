#pragma once

#include "enemymanager.h"
#include "enemy.h"
#include <ResourceLoader.hpp>
#include <string>

using namespace godot;

void EnemyManager::_register_methods()
{
    // Godot Methods
    register_method("_ready", &EnemyManager::_ready);
    register_method("_process", &EnemyManager::_process);
    register_method("_init", &EnemyManager::_init);

    // Received Signals
    register_method("_on_game_start", &EnemyManager::_on_game_start);

    // Properties
    register_property<EnemyManager, int>("numOfEnemies", &EnemyManager::numOfEnemies, 10);
}

EnemyManager::EnemyManager() {
}

EnemyManager::~EnemyManager() {
    delete uiManager;
    delete gameManager;
}

void EnemyManager::_init() {
    numOfEnemies = 10;
    isTimer = false;
}

void EnemyManager::_ready() {
    // In init or ready?
    ResourceLoader* loader = ResourceLoader::get_singleton();
    enemyPrefab = loader->load("res://_scenes/Enemy.tscn");

    uiManager = (Node*)get_node("../UIManager");
    gameManager = (Node*)get_node("/root/Main");
    enemies = std::vector<Enemy*>();
    _on_game_start();
}

void EnemyManager::_process(float delta)
{

}

void EnemyManager::_on_game_start()
{
    enemies.clear();
    while (numOfEnemies > enemies.size()) {
        Enemy* enemy = static_cast<Enemy*>(enemyPrefab->instance());
        add_child(enemy);
        enemy->connect("enemy_death", uiManager, "_on_enemy_death");
        gameManager->connect("on_game_start", enemy, "_on_game_start");
        gameManager->connect("on_game_end", enemy, "_on_game_end");
        enemies.push_back(enemy);
    }
}

// Vector2 EnemyManager::get_random_screenpos() {
//     int screenSizeX = get_viewport_rect().get_size().y;
//     float startX = rand() % screenSizeX;
//     Vector2 startPos = Vector2(startX, 0);
//     return startPos;
// }

// Vector2 EnemyManager::get_random_direction() {
//     float randX = rand() % 200 - 100;
//     float randY = rand() % 100 + 1;
//     return Vector2(randX, randY).normalized();
// }

// float EnemyManager::get_random_speed(Enemy* enemy) {
//     //enemy->min_speed
//     float min_speed = 1000;
//     float max_speed = 2000;
//     int randInterval = max_speed - min_speed;
//     return (rand() % randInterval + min_speed)/3;
// }

