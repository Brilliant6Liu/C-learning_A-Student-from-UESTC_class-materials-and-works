#ifndef CONFIG_H
#define CONFIG_H

#include <windows.h>

// 画面与网格配置
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_ROWS 15
#define MAP_COLS 20
#define TILE_SIZE 40 // 每个网格 40x40 像素

// 游戏物理常数
#define GRAVITY 1200.0f
#define WALK_SPEED 300.0f
#define JUMP_FORCE -550.0f
#define WALL_SLIDE_SPEED 80.0f
#define WALL_JUMP_X 400.0f
#define WALL_JUMP_Y -500.0f

// 游戏状态枚举
typedef enum
{
    STATE_MENU,
    STATE_CHAR_SELECT,
    STATE_PLAYING,
    STATE_VICTORY
} GameState;
typedef enum
{
    CHAR_CHICKEN,
    CHAR_RABBIT,
    CHAR_SNAKE
} CharacterType;
typedef enum
{
    TILE_EMPTY = ' ',
    TILE_WALL = '#',
    TILE_TRAP = '^',
    TILE_START = 'S',
    TILE_GOAL = 'G'
} TileType;

// 玩家实体结构体
typedef struct
{
    float x, y;
    float vx, vy;
    int width, height;
    int is_grounded;
    int is_on_left_wall;
    int is_on_right_wall;
} Player;

// 游戏全局上下文
typedef struct
{
    GameState state;
    CharacterType selected_char;
    char map[MAP_ROWS][MAP_COLS];
    int current_level;
    Player player;
    COORD start_pos;
} GameContext;

// 跨模块函数声明
void init_game(GameContext *ctx);
void load_level(GameContext *ctx, int level_num);
void update_game(GameContext *ctx, float dt, int key_left, int key_right, int key_jump);

#endif