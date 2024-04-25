#include "bullet.hpp"
#include "common.hpp"
#include "draw.hpp"
#include "util.hpp"
#include "stage.hpp"

extern App app;
extern Stage stage;
static Entity *player;

int bulletHitFighter(Entity *e);

// remove bullet if it leaves the screen (except for top)

int bulletHitFighter(Entity *b)
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
            
            addPoints(e->x + e->w / 2, e->y + e->h / 2);
            
            return 1;
        }
    }

    return 0;
}


void doBullets(void)
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

// draw bullets to screen

void drawBullets(void)
{
    Entity *b;

    for (b = stage.bulletHead.next; b != NULL; b = b->next)
    {
        rectangle(b->texture, b->x, b->y);
    }
}
