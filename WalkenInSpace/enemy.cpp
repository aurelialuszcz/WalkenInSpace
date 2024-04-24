#include "enemy.hpp"
#include "common.hpp"
#include "draw.hpp"
#include "stage.hpp"
#include "player.hpp"
#include "util.hpp"

static Entity *enemy;
static Entity *player;
extern App app;
extern Stage stage;
extern int enemySpawnTimer;
static int playerShotCount = 0;

void fireAlienBullet(Entity *e);
void doEnemies(void);
void drawEnemy(void);
void doFighters(void);
void spawnEnemies(void);

static SDL_Texture *alienBulletTexture = loadTexture("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/alienBullet.png");

// enemy spawning

void doEnemies(void)
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

// random spawning of enemies on the screen

void spawnEnemies(void)
{
    Entity *enemy;
    
    static SDL_Texture *enemyTexture = loadTexture("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/spider128x128.png");

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


// enemy bullet firing

void fireAlienBullet(Entity *e)
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

    e->reload = (/*rand() %*/ FPS * 2);
}

// enemy function when player hit

void doFighters(void)
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

// draw enemies to screen

void drawEnemy(void)
{
    Entity *e;

    for (e = stage.fighterHead.next; e != NULL; e = e->next)
    {
        rectangle(e->texture, e->x, e->y);
    }
}
