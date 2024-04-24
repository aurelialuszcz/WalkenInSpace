#include "common.hpp"
#include "player.hpp"
#include "draw.hpp"
#include "stage.hpp"

static Entity      *player;
static SDL_Texture *playerTexture;
static SDL_Texture *bulletTexture;
extern App app;
extern Stage stage;

void fireBullet(void);
void clipPlayer(void);
void doPlayer(void);
void initPlayer()
{
    playerTexture = loadTexture("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/player64x64.png");
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

// player staying in the game screen

void clipPlayer(void)
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

        if (player->x > SCREEN_WIDTH - player->w)
        {
            player->x = SCREEN_WIDTH - player->w;
        }

        if (player->y > SCREEN_HEIGHT - player->h)
        {
            player->y = SCREEN_HEIGHT - player->h;
        }
    }
}

void doPlayer(void)
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

void fireBullet(void)
{
    Entity *bullet;
    
    bulletTexture = loadTexture("/Users/aurelialuszcz/Documents/WalkenInSpace/WalkenInSpace/assets/bullet.png");

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
