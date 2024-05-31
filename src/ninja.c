#ifndef NINJA_H
#define NINJA_H

#include "raylib.h"

typedef struct Ninja {
    Vector2 position;
    Texture2D attackTexture;
    Rectangle attackRect;
    int attackDamage;
    bool isAttacking;
    int attackFrame;
} Ninja;

typedef struct Enemy {
    Rectangle boundingBox;
    int health;
} Enemy;

void initNinjaAttack();
void ninjaAttack();
void drawNinjaAttackAnimation(bool newAttack);

#define NORMAL_ATTACK_WIDTH 50
#define NORMAL_ATTACK_HEIGHT 50
#define ANIMATION_TIME 0.5f
#define CRITICAL 1
#define NORMAL 0

#endif 
