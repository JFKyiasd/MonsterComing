#ifndef NINJA_C
#define NINJA_C

#include "ninja.h"
#include "raylib.h"
#include "zombies.h"
#include "mainPlayer.h"
#include "basic.h"
#include <stdlib.h>
#include <stdio.h>

Vector2 ninjaAttackAnimationCenter;
Texture2D ninjaAttackTexture;

void initNinjaAttack() {
    ninjaAttackTexture = LoadTexture("resources/NinjaAttack.png");
}

void ninjaAttack() {
    zombie *currZombie = getZombies();
    enum MAINPLAYERFACING facing = getMainPlayerFacing();
    Rectangle attackRange;

    // Generate Attack Range
    if (facing == NORTH) {
        attackRange = (Rectangle){getMainPlayerCenter().x - NORMAL_ATTACK_WIDTH / 2, getMainPlayerCenter().y - NORMAL_ATTACK_HEIGHT, NORMAL_ATTACK_WIDTH, NORMAL_ATTACK_HEIGHT};
    } else if (facing == WEST) {
        attackRange = (Rectangle){getMainPlayerCenter().x - NORMAL_ATTACK_WIDTH, getMainPlayerCenter().y - NORMAL_ATTACK_HEIGHT / 2, NORMAL_ATTACK_HEIGHT, NORMAL_ATTACK_WIDTH};
    } else if (facing == EAST) {
        attackRange = (Rectangle){getMainPlayerCenter().x, getMainPlayerCenter().y - NORMAL_ATTACK_HEIGHT / 2, NORMAL_ATTACK_HEIGHT, NORMAL_ATTACK_WIDTH};
    } else if (facing == SOUTH) {
        attackRange = (Rectangle){getMainPlayerCenter().x - NORMAL_ATTACK_WIDTH / 2, getMainPlayerCenter().y, NORMAL_ATTACK_WIDTH, NORMAL_ATTACK_HEIGHT};
    }

    // For Attack Animation Position
    ninjaAttackAnimationCenter = (Vector2){attackRange.x + attackRange.width / 2, attackRange.y + attackRange.height / 2};
    drawNinjaAttackAnimation(true);

    if (DEBUG == 1)
        DrawRectangleLines((int)attackRange.x, (int)attackRange.y, (int)attackRange.width, (int)attackRange.height, RED);

    // Check if Zombie is in Attack Range
    while (currZombie != NULL) {
        if (currZombie->zombieType != FIRSTNODEZOMBIE) {
            if (CheckCollisionRecs(currZombie->hitbox, attackRange)) {
                int damage = getNormalAttackDamage();
                currZombie->health -= damage;
                // Draw Damage Value (with critical damage calculation)
                if ((rand() % 100 + 1) <= getCriticalHitPercentage() * 100) {
                    // Critical Hit
                    addZombieDamageAnimation(currZombie, damage * 2, CRITICAL);
                } else {
                    // Normal Hit
                    addZombieDamageAnimation(currZombie, damage, NORMAL);
                }
            }
        }
        currZombie = currZombie->nextZombie;
    }

    return;
}

void drawNinjaAttackAnimation(bool newAttack) {
    static float currTime = 0.0;

    currTime += GetFrameTime();
    if (currTime >= ANIMATION_TIME) currTime = ANIMATION_TIME;

    if (newAttack) currTime = 0.0; 

    if (currTime < ANIMATION_TIME) {
        DrawCircleLines(ninjaAttackAnimationCenter.x, ninjaAttackAnimationCenter.y, 30.0, RED);
        DrawTexture(ninjaAttackTexture, ninjaAttackAnimationCenter.x - ninjaAttackTexture.width / 2, ninjaAttackAnimationCenter.y - ninjaAttackTexture.height / 2, WHITE);
    }

    return;
}

#endif
