// game stage

#include "common.hpp"
#include "draw.hpp"
#include "stage.hpp"
#include "util.hpp"
#include "starfield.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "bullet.hpp"
#include "background.hpp"
#include <stdlib.h>
#include <iostream>

extern App   app;
extern Stage stage;

static void logic(void);
static void draw(void);
void initPlayer(void);
void fireBullet(void);
void doPlayer(void);
void doFighters(void);
void doBullets(void);
void drawEnemy(void);
void drawBullets(void);
void spawnEnemies(void);
int bulletHitFighter(Entity *b);
void doEnemies(void);
void fireAlienBullet(Entity *e);
void clipPlayer(void);
void resetStage(void);
void drawBackground(void);
void initStarfield(void);
void drawStarfield(void);
void doBackground(void);
void doStarfield(void);


static Entity      *player;
static SDL_Texture *alienBulletTexture;

static int          stageResetTimer;
int enemySpawnTimer;

void initStage(void)
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(&stage, 0, sizeof(Stage));
    stage.fighterTail = &stage.fighterHead;
    stage.bulletTail = &stage.bulletHead;
    //stage.explosionTail = &stage.explosionHead;
    //stage.debrisTail = &stage.debrisHead;

    resetStage();
}

// function to reset the game once player dead

void resetStage(void)
{
    Entity    *e;

    while (stage.fighterHead.next)
    {
        e = stage.fighterHead.next;
        stage.fighterHead.next = e->next;
        free(e);
    }

    while (stage.bulletHead.next)
    {
        e = stage.bulletHead.next;
        stage.bulletHead.next = e->next;
        free(e);
    }

    memset(&stage, 0, sizeof(Stage));
    stage.fighterTail = &stage.fighterHead;
    stage.bulletTail = &stage.bulletHead;


    initPlayer();

    initStarfield();

    enemySpawnTimer = 0;

    stageResetTimer = FPS * 4;
}

// game logic - pulling all functions

static void logic(void)
{
    doBackground();

    doStarfield();

    doPlayer();

    doEnemies();

    doFighters();

    doBullets();

    spawnEnemies();

    clipPlayer();

    if (player == NULL && --stageResetTimer <= 0)
    {
        resetStage();
    }
}

// draw function of all characters

static void draw(void)
{
    drawBackground();

    drawStarfield();

    drawEnemy();

    drawBullets();
}


