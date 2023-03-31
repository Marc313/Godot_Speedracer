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

    // Received Signals
    register_method("_on_game_start", &EnemyManager::_on_game_start);
    register_method("_on_game_end", &EnemyManager::_on_game_end);
    register_method("_on_ExtraEnemyTimer_timeout", &EnemyManager::_on_ExtraEnemyTimer_timeout);

    // Properties
    register_property<EnemyManager, int>("numOfEnemies", &EnemyManager::numOfEnemiesOnStart, 10);
    register_property<EnemyManager, float>("enemySpawnInterval", &EnemyManager::enemySpawnInterval, 1.0f);
}

EnemyManager::EnemyManager() {
}

EnemyManager::~EnemyManager() {
    delete uiManager;
    delete gameManager;
    delete enemySpeedTimer;
    delete extraEnemyTimer;
}

void EnemyManager::_init() {
    numOfEnemiesOnStart = 10;
    enemyTimerWaitTime = 30.0f;
    enemySpawnInterval = 1.0f;
}

void EnemyManager::_ready() {
    // In init or ready?
    ResourceLoader* loader = ResourceLoader::get_singleton();
    enemyPrefab = loader->load("res://_scenes/Enemy.tscn");

    uiManager = static_cast<Node*>(get_node("../UIManager"));
    gameManager = static_cast<Node*>(get_node("/root/Main"));
    enemySpeedTimer = static_cast<Timer*>(get_node("EnemySpeedTimer"));
    extraEnemyTimer = static_cast<Timer*>(get_node("ExtraEnemyTimer"));
    enemyTimerWaitTime = extraEnemyTimer->get_wait_time();
    enemies = std::vector<Enemy*>();
}

void EnemyManager::_on_game_start()
{
    enemies.clear();
    add_enemy();

    if (enemySpeedTimer) enemySpeedTimer->start();
    if (extraEnemyTimer) 
    {
        extraEnemyTimer->set_wait_time(enemySpawnInterval);
        extraEnemyTimer->start();
    }
}

void EnemyManager::_on_game_end()
{
    enemySpeedTimer->stop();
    extraEnemyTimer->stop();
}

void EnemyManager::add_enemy() {
    Enemy* enemy = static_cast<Enemy*>(enemyPrefab->instance());
    add_child(enemy);
    enemy->connect("enemy_death", uiManager, "_on_enemy_death");
    gameManager->connect("on_game_start", enemy, "_on_game_start");
    gameManager->connect("on_game_end", enemy, "_on_game_end");
    enemySpeedTimer->connect("timeout", enemy, "_on_speedtimer_timeout");
    enemies.push_back(enemy);

    if (extraEnemyTimer && numOfEnemiesOnStart <= enemies.size()) {
        extraEnemyTimer->stop();
        extraEnemyTimer->set_wait_time(enemyTimerWaitTime);
        extraEnemyTimer->start();
    }
}

void EnemyManager::_on_ExtraEnemyTimer_timeout()
{
    add_enemy();
}
