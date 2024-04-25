#ifndef define_hpp
#define define_hpp

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define STRNCPY(dest, src, n) \
    strncpy(dest, src, n);    \
    dest[n - 1] = '\0'

#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 800

#define MAX_NAME_LENGTH 32
#define MAX_LINE_LENGTH 1024

#define FPS 60

#define PLAYER_SPEED        4
#define PLAYER_BULLET_SPEED 20
#define ALIEN_BULLET_SPEED  8

#define MAX_KEYBOARD_KEYS 350

#define SIDE_PLAYER 0
#define SIDE_ALIEN  1

#define MAX_STARS 500

#define MAX_SND_CHANNELS 8

#define NUM_HIGHSCORES 8

enum
{
    CH_ANY = -1,
    CH_PLAYER,
    CH_ALIEN_FIRE,
    CH_POINTS
};

enum
{
    SND_PLAYER_FIRE,
    SND_ALIEN_FIRE,
    SND_PLAYER_DIE,
    SND_ALIEN_DIE,
    SND_POINTS,
    SND_MAX
};


#endif /* define_h */
