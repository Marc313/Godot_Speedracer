#pragma once

#include "enemymanager.h"
#include "enemy.h"
#include <ResourceLoader.hpp>

using namespace godot;

void EnemyManager::_register_methods() {
    register_method("_process", &EnemyManager::_process);
    register_method("_ready", &EnemyManager::_ready);
}

EnemyManager::EnemyManager() {
}

EnemyManager::~EnemyManager() {

}

void EnemyManager::_init() {
}

void EnemyManager::_ready() {
    // In init or ready?
    ResourceLoader* loader = ResourceLoader::get_singleton();
    enemyPrefab = loader->load("res://_scenes/Enemy.tscn");

    for (int i = 0; i < 10; i++) {
        Enemy* enemy = static_cast<Enemy*>(enemyPrefab->instance());
        enemy->_init();
        enemy->set_position(get_random_screenpos());
        enemy->connect("enemy_death", get_node("../Score"), "_on_enemy_death");
        enemies.push_back(enemy);
        add_child(enemy);
    }
}

void EnemyManager::_process(float delta) {
    
}

Vector2 EnemyManager::get_random_screenpos() {
    srand(time(NULL));
    int screenSizeX = get_viewport_rect().get_size().y;
    float startX = rand() % screenSizeX;
    Vector2 startPos = Vector2(startX, 0);
    return startPos;
}

