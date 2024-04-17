// game stage

#include "common.hpp"

#include "draw.hpp"
#include "stage.hpp"
#include "util.hpp"
#include "level.hpp"
#include "starfield.hpp"
#include <stdlib.h>
#include <iostream>

extern App   app;
extern Stage stage;

static void logic(void);
static void draw(void);
static void initPlayer(void);
static void fireBullet(void);
static void doPlayer(void);
static void doFighters(void);
static void doBullets(void);
static void drawFighters(void);
static void drawBullets(void);
static void spawnEnemies(void);
static int  bulletHitFighter(Entity *b);
static void doEnemies(void);
static void fireAlienBullet(Entity *e);
static void clipPlayer(void);
static void resetStage(void);
static void drawBackground(void);
void initStarfield(void);
void drawStarfield(void);
static void doBackground(void);
void doStarfield(void);


static Entity      *player;
static SDL_Texture *bulletTexture;
static SDL_Texture *enemyTexture;
static SDL_Texture *alienBulletTexture;
static SDL_Texture *playerTexture;
static SDL_Texture *background;
static int          enemySpawnTimer;
static int          stageResetTimer;
static int          backgroundY;


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
    bulletTexture = loadTexture("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/bullet.png");
    enemyTexture = loadTexture("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/spider128x128.png");
    alienBulletTexture = loadTexture("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/alienBullet.png");
    playerTexture = loadTexture("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/player64x64.png");
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

    stageResetTimer = FPS * 3;
}

// create player

static void initPlayer()
{
    player = (Entity *)malloc(sizeof(Entity));
    memset(player, 0, sizeof(Entity));
    stage.fighterTail->next = player;
    stage.fighterTail = player;

    player->health = 100;
    player->hitCount = 0;
    player->x = 300;
    player->y = 800;
    player->texture = playerTexture;
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);

    //std::cout << player->h << std::endl;
    //std::cout << player->w << std::endl;
    
    player->side = SIDE_PLAYER;
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


// keyboard control of player

static void doPlayer(void)
{
    if (player != NULL)
    {
        player->dx = player->dy = 0;

        if (player->reload > 0)
        {
            player->reload--;
        }

        if (app.keyboard[SDL_SCANCODE_UP])
        {
            player->dy = -PLAYER_SPEED;
        }

        if (app.keyboard[SDL_SCANCODE_DOWN])
        {
            player->dy = PLAYER_SPEED;
        }

        if (app.keyboard[SDL_SCANCODE_LEFT])
        {
            player->dx = -PLAYER_SPEED;
        }

        if (app.keyboard[SDL_SCANCODE_RIGHT])
        {
            player->dx = PLAYER_SPEED;
        }

        if (app.keyboard[SDL_SCANCODE_SPACE] && player->reload <= 0)
        {
            fireBullet();
        }
    }
}

// bullet creation

static void fireBullet(void)
{
    Entity *bullet;

    bullet = (Entity *)malloc(sizeof(Entity));
    memset(bullet, 0, sizeof(Entity));
    stage.bulletTail->next = bullet;
    stage.bulletTail = bullet;

    bullet->x = player->x;
    bullet->y = player->y;
    bullet->dy = -PLAYER_BULLET_SPEED;
    bullet->health = 1;
    bullet->texture = bulletTexture;
    bullet->side = SIDE_PLAYER;
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

    bullet->y += (player->h / 2) - (bullet->h / 2);

    player->reload = 8;
}

// enemy spawning

static void doEnemies(void)
{
    Entity *e;

    for (e = stage.fighterHead.next; e != NULL; e = e->next)
    {
        if (e != player && player != NULL && --e->reload <= 0)
        {
            fireAlienBullet(e);
        }
    }
}

// enemy bullet firing

static void fireAlienBullet(Entity *e)
{
    Entity *bullet;

    bullet = (Entity *)malloc(sizeof(Entity));
    memset(bullet, 0, sizeof(Entity));
    stage.bulletTail->next = bullet;
    stage.bulletTail = bullet;

    bullet->x = e->x;
    bullet->y = e->y;
    bullet->health = 1;
    bullet->texture = alienBulletTexture;
    bullet->side = SIDE_ALIEN;
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

    bullet->x += (e->w / 2) - (bullet->w / 2);
    bullet->y += (e->h / 2) - (bullet->h / 2);

    calcSlope(player->x + (player->w / 2), player->y + (player->h / 2), e->x, e->y, &bullet->dx, &bullet->dy);

    bullet->dx *= ALIEN_BULLET_SPEED;
    bullet->dy *= ALIEN_BULLET_SPEED;

    e->reload = (rand() % FPS * 2);
}

// enemy function when player hit

static void doFighters(void)
{
    Entity *e, *prev;

    prev = &stage.fighterHead;

    for (e = stage.fighterHead.next; e != NULL; e = e->next)
    {
        e->x += e->dx;
        e->y += e->dy;

        if (e != player && e->x < -e->w)
        {
            e->health = 0;
        }

        if (e->health == 0)
        {
            if (e == player)
            {
                player = NULL;
            }

            if (e == stage.fighterTail)
            {
                stage.fighterTail = prev;
            }

            prev->next = e->next;
            free(e);
            e = prev;
        }

        prev = e;
    }
}

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

// random spawning of enemies on the screen

static void spawnEnemies(void)
{
    Entity *enemy;

    if (--enemySpawnTimer <= 0)
    {
        enemy = (Entity *)malloc(sizeof(Entity));
        memset(enemy, 0, sizeof(Entity));
        stage.fighterTail->next = enemy;
        stage.fighterTail = enemy;

        enemy->y = -enemy->h;
        enemy->x = rand() % SCREEN_HEIGHT;
        enemy->texture = enemyTexture;
        SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

        enemy->dy = (2 + (rand() % 4));

        enemy->side = SIDE_ALIEN;
        enemy->health = 1;

        enemy->reload = FPS * (1 + (rand() % 3));

        enemySpawnTimer = 30 + (rand() % FPS);
    }
}

// player staying in the game screen

static void clipPlayer(void)
{
    if (player != NULL)
    {
        if (player->x < 0)
        {
            player->x = 0;
        }

        if (player->y < 0)
        {
            player->y = 0;
        }

        if (player->x > SCREEN_WIDTH)
        {
            player->x = SCREEN_WIDTH;
        }

        if (player->y > SCREEN_HEIGHT - player->h)
        {
            player->y = SCREEN_HEIGHT - player->h;
        }
    }
}

// draw function of all characters

static void draw(void)
{
    drawBackground();

    drawStarfield();

    drawFighters();

    drawBullets();
}
// draw enemies to screen

static void drawFighters(void)
{
    Entity *e;

    for (e = stage.fighterHead.next; e != NULL; e = e->next)
    {
        blit(e->texture, e->x, e->y);
    }
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

