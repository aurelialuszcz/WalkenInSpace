typedef struct Entity    Entity;
typedef struct Explosion Explosion;
typedef struct Debris    Debris;

typedef struct
{
    void (*logic)(void);
    void (*draw)(void);
} Delegate;

typedef struct
{
    SDL_Renderer *renderer;
    SDL_Window   *window;
    Delegate delegate;
    int keyboard[MAX_KEYBOARD_KEYS];
} App;

struct Entity
{
    float        x;
    float        y;
    int          w;
    int          h;
    float        dx;
    float        dy;
    int          health;
    int          reload;
    int          side;
    int          hitCount;
    SDL_Texture *texture;
    Entity      *next;
};

struct Bullet
{
    double        x;
    double        y;
    double        dx;
    double        dy;
    SDL_Texture *texture;
    Entity       *owner;
    Bullet       *next;
};

typedef struct
{
    Entity    playerHead, *playerTail;
    Entity    fighterHead, *fighterTail;
    Entity    bulletHead, *bulletTail;
} Stage;

typedef struct
{
    int x;
    int y;
    int speed;
} Star;
