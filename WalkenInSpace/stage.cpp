// game stage

#include "common.hpp"
#include "texture.hpp"
#include "draw.hpp"
#include "stage.hpp"
#include "util.hpp"
#include "level.hpp"
#include "starfield.hpp"
#include "player.hpp"
#include "enemy.hpp"
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
static void doBullets(void);
void drawEnemy(void);
static void drawBullets(void);
void spawnEnemies(void);
static int  bulletHitFighter(Entity *b);
void doEnemies(void);
void fireAlienBullet(Entity *e);
void clipPlayer(void);
static void resetStage(void);
static void drawBackground(void);
void initStarfield(void);
void drawStarfield(void);
static void doBackground(void);
void doStarfield(void);


static Entity      *player;
static SDL_Texture *alienBulletTexture;
static SDL_Texture *background;
static int          stageResetTimer;
static int          backgroundY;
int enemySpawnTimer;

void initStage(void)
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(&stage, 0, sizeof(Stage));
    stage.fighterTail = &stage.fighterHead;
    stage.bulletTail = &stage.bulletHead;
    stage.explosionTail = &stage.explosionHead;
    stage.debrisTail = &stage.debrisHead;

    // character textures

    background = loadTexture("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/background_.png");
    resetStage();
}

// function to reset the game once player dead

static void resetStage(void)
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


static void doBackground(void)
{
    if (--backgroundY < -SCREEN_HEIGHT)
    {
        backgroundY = 0;
    }
}

// bullet creation




// remove bullet if it leaves the screen (except for right hand side)

static void doBullets(void)
{
    Entity *b, *prev;

    prev = &stage.bulletHead;

    for (b = stage.bulletHead.next; b != NULL; b = b->next)
    {
        b->x += b->dx;
        b->y += b->dy;

        if (bulletHitFighter(b) || b->x < -b->w || b->y < -b->h || b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT)
        {
            if (b == stage.bulletTail)
            {
                stage.bulletTail = prev;
            }

            prev->next = b->next;
            free(b);
            b = prev;
        }

        prev = b;
    }
}

// destroy enemy when bullet hits it

static int bulletHitFighter(Entity *b)
{
    Entity *e;

    for (e = stage.fighterHead.next; e != NULL; e = e->next)
    {
        if (e->side != b->side && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h))
        {
            if (e == player && e->hitCount == 0) {
                            e->hitCount = 1;
            } else if (e->hitCount == 1) {
                // Two bullets hit the player, kill the player
                b->health = 0;
                e->health = 0;
                e->hitCount = 0;
            } else if (e != player) {
                b->health = 0;
                e->health = 0;
            }
            return 1;
        }
    }

    return 0;
}

// draw function of all characters

static void draw(void)
{
    drawBackground();

    drawStarfield();

    drawEnemy();

    drawBullets();
}



// draw bullets to screen

static void drawBullets(void)
{
    Entity *b;

    for (b = stage.bulletHead.next; b != NULL; b = b->next)
    {
        blit(b->texture, b->x, b->y);
    }
}

// draw background to screen

static void drawBackground(void)
{
    SDL_Rect dest;
    int      y;

    for (y = backgroundY; y < SCREEN_HEIGHT; y += SCREEN_HEIGHT)
    {
        dest.x = 0;
        dest.y = y;
        dest.w = SCREEN_WIDTH;
        dest.h = SCREEN_HEIGHT;

        SDL_RenderCopy(app.renderer, background, NULL, &dest);
    }
}
