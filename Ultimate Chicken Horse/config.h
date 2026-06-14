#// 配置头文件：屏幕、网格、物理常数、类型与跨模块声明（注释使用中文）
#ifndef CONFIG_H
#define CONFIG_H

#include <windows.h>

/* 画面与网格配置 */
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_ROWS 15
#define MAP_COLS 20
#define TILE_SIZE 40

/* 游戏物理常数 */
#define GRAVITY 1200.0f
#define WALK_SPEED 300.0f
#define JUMP_FORCE -550.0f
#define WALL_SLIDE_SPEED 80.0f
#define WALL_JUMP_X 400.0f
#define WALL_JUMP_Y -500.0f
#define WALL_JUMP_SHOVE_DISTANCE 48.0f
#define WALL_JUMP_COOLDOWN 0.25f
#define WALL_JUMP_SHOVE_DURATION 0.12f

/* 存档与关卡 */
#define MAX_LEVELS 100

/* 评分阈值（秒）：用于结算评级 */
#define RATING_T1 12.0f
#define RATING_T2 25.0f
#define RATING_T3 45.0f
#define RATING_T4 75.0f

/* 游戏状态与角色、地图枚举 */
typedef enum
{
    STATE_MENU,
    STATE_CHAR_SELECT,
    STATE_LEVEL_SELECT,
    STATE_PLAYING,
    STATE_VICTORY,
    STATE_PAUSED,
    STATE_GAME_COMPLETE
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

/* 玩家实体：位置、速度、碰撞与墙跳/推进相关变量 */
typedef struct
{
    float x, y;
    float vx, vy;
    int width, height;
    int is_grounded;
    int is_on_left_wall;
    int is_on_right_wall;
    float wall_jump_cooldown;
    float shove_total;
    float shove_time_remaining;
} Player;

/* 游戏全局上下文：状态、角色、关卡、计时、成绩与玩家 */
typedef struct
{
    GameState state;
    CharacterType selected_char;
    char map[MAP_ROWS][MAP_COLS];
    int current_level;
    int menu_selected_level;
    int level_select_from_char;
    float level_time;
    float best_times[MAX_LEVELS + 1];
    int max_levels;
    int unlocked_level;
    int victory_choice;
    int prev_space_down;
    Player player;
    COORD start_pos;
} GameContext;

/* 存档结构：保存已解锁关卡与默认角色 */
typedef struct
{
    int unlocked_level;
    CharacterType selected_char;
} SaveData;

/* 跨模块函数声明 */
int count_levels(void);
void init_game(GameContext *ctx);
void load_level(GameContext *ctx, int level_num);
void update_game(GameContext *ctx, float dt, int key_left, int key_right, int key_jump_edge);
void save_game(GameContext *ctx);
void load_save(GameContext *ctx);
void load_best_times(GameContext *ctx);
void save_best_time(GameContext *ctx, int level, float time);

#endif