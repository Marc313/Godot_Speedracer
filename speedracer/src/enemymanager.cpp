#pragma once

#include "enemymanager.h"
#include "enemy.h"
#include <ResourceLoader.hpp>
#include <string>

using namespace godot;

void EnemyManager::_register_methods()
{
    register_method("_ready", &EnemyManager::_ready);
    register_method("_process", &EnemyManager::_process);
    register_method("_init", &EnemyManager::_init);

    register_method("_on_game_start", &EnemyManager::_on_game_start);

    register_property<EnemyManager, int>("numOfEnemies", &EnemyManager::numOfEnemies, 10);
}

EnemyManager::EnemyManager() {
}

EnemyManager::~EnemyManager() {
    delete uiManager;
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
    enemies = std::vector<Enemy*>();
    _on_game_start();
}

void godot::EnemyManager::_process(float delta)
{
    if (isTimer) 
    {
        timer -= delta;
        if (timer < 0.0f) 
        {
            start_enemies();
            isTimer = false;
            timer = 0.5f;
        }
    }
}

void godot::EnemyManager::_on_game_start()
{
    //Godot::print(std::to_string(enemies.size()).c_str());

    // If there are not enough enemies, create new enemies.
    while (numOfEnemies > enemies.size()) {
        Enemy* enemy = static_cast<Enemy*>(enemyPrefab->instance());
        add_child(enemy);
        //enemy->connect("enemy_death", uiManager, "_on_enemy_death");
        enemies.push_back(enemy);

        Vector2 startPos = Vector2(100.0f, 100.0f);//get_random_screenpos();
        Vector2 direction = Vector2(1.0f, 1.0f);//get_random_direction();
        float speed = 5000.0f;//get_random_speed(enemyPtr);

        isTimer = true;
        timer = 0.5f;
        //enemy->set_position(startPos);
        //enemy->direction = direction;
        //enemy->speed = speed;
    }

    // Make sure to reset all enemies, including enemies that were already in enemies
    // for (size_t i = 0; i < enemies.size(); i++) {
    //     Enemy* enemyPtr = enemies.at(i);
    //     Vector2 startPos = Vector2(100.0f, 100.0f);//get_random_screenpos();
    //     Vector2 direction = Vector2(1.0f, 1.0f);//get_random_direction();
    //     float speed = 5.0f;//get_random_speed(enemyPtr);

    //     enemies.at(i)->on_start(startPos, direction, speed);
    // }

    // Godot::print(enemies.size());

}

void EnemyManager::start_enemies() 
{
    for (size_t i = 0; i < enemies.size(); i++) {
        Enemy* enemyPtr = enemies.at(i);
        Vector2 startPos = Vector2(100.0f, 100.0f); //get_random_screenpos();
        Vector2 direction = Vector2(1.0f, 1.0f); //get_random_direction();
        float speed = 5.0f; //get_random_speed(enemyPtr);

        enemyPtr->on_start(startPos, direction, speed);
    }
}

Vector2 EnemyManager::get_random_screenpos() {
    int screenSizeX = get_viewport_rect().get_size().y;
    float startX = rand() % screenSizeX;
    Vector2 startPos = Vector2(startX, 0);
    return startPos;
}

Vector2 EnemyManager::get_random_direction() {
    float randX = rand() % 200 - 100;
    float randY = rand() % 100 + 1;
    return Vector2(randX, randY).normalized();
}

float EnemyManager::get_random_speed(Enemy* enemy) {
    //enemy->min_speed
    float min_speed = 1000;
    float max_speed = 2000;
    int randInterval = max_speed - min_speed;
    return (rand() % randInterval + min_speed)/3;
}

