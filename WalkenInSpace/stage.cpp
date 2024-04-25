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
#include "text.hpp"
#include "score.hpp"
#include <stdlib.h>
#include <iostream>
using namespace std;

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
static void drawHud(void);
void doPoints(void);
static void drawPoints(void);
void addPoints(int x, int y);

static Entity      *player;
SDL_Texture *pointsTexture;
static int          stageResetTimer;
int enemySpawnTimer;
static int          highscore;

void initStage(void)
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(&stage, 0, sizeof(Stage));
    stage.fighterTail = &stage.fighterHead;
    stage.bulletTail = &stage.bulletHead;
    //stage.explosionTail = &stage.explosionHead;
    //stage.debrisTail = &stage.debrisHead;

    pointsTexture = loadTexture("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/points.png");
    resetStage();
    
    initPlayer();

    //initStarfield();

    enemySpawnTimer = 0;

    stageResetTimer = FPS * 3;
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
    
    while (stage.pointsHead.next)
    {
        e = stage.pointsHead.next;
        stage.pointsHead.next = e->next;
        free(e);
    }

    stage.fighterTail = &stage.fighterHead;
    stage.bulletTail = &stage.bulletHead;
    stage.pointsTail = &stage.pointsHead;

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

    doPoints();
    
    spawnEnemies();

    clipPlayer();
    
}

void doPoints(void)
{
    Entity *e, *prev;

    prev = &stage.pointsHead;

    for (e = stage.pointsHead.next; e != NULL; e = e->next)
    {
        if (e->x < 0)
        {
            e->x = 0;
            e->dx = -e->dx;
        }

        if (e->x + e->w > SCREEN_WIDTH)
        {
            e->x = SCREEN_WIDTH - e->w;
            e->dx = -e->dx;
        }

        if (e->y < 0)
        {
            e->y = 0;
            e->dy = -e->dy;
        }

        if (e->y + e->h > SCREEN_HEIGHT)
        {
            e->y = SCREEN_HEIGHT - e->h;
            e->dy = -e->dy;
        }

        e->x += e->dx;
        e->y += e->dy;

        if (player != NULL && e != NULL && collision(player->x, player->y, player->w, player->h, e->x, e->y, e->w, e->h))
        {
            e->health = 0;
            
            stage.score++;
            
            std::cout << stage.score << std::endl;
            
            highscore = MAX(stage.score, highscore);
            
            drawHud();
        }
        
        if (--e->health <= 0)
        {
            if (e == stage.pointsTail)
            {
                stage.pointsTail = prev;
            }

            prev->next = e->next;
            free(e);
            e = prev;
        }

        prev = e;
    }
}

void addPoints(int x, int y)
{
    Entity *e;

    e = (Entity *)malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.pointsTail->next = e;
    stage.pointsTail = e;

    e->x = x;
    e->y = y;
    e->dx = -(rand() % 5);
    e->dy = (rand() % 5) - (rand() % 5);
    e->health = FPS * 10;
    e->texture = pointsTexture;

    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);

    //e->x -= e->w / 2;
    //e->y -= e->h / 2;
}

static void drawPoints(void)
{
    Entity *e;

    for (e = stage.pointsHead.next; e != NULL; e = e->next)
    {
        rectangle(e->texture, e->x, e->y);
    }
}

static void drawHud(void)
{
    drawText(10, 10, 255, 255, 255, "SCORE: %03d", stage.score);

    /*if (stage.score > 0 && stage.score == highscore)
    {
        drawText(200, 10, 0, 255, 0, "HIGHSCORE: %03d", highscore);
    }
    else
    {
        drawText(100, 10, 255, 255, 255, "HIGHSCORE: %03d", highscore);
    }*/
}

// draw function of all characters

static void draw(void)
{
    drawBackground();

    drawStarfield();
    
    drawPoints();

    drawEnemy();

    drawBullets();
    
    drawHud();
}


