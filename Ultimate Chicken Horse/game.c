#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 检查两个轴对齐矩形（AABB）是否相交，返回1表示碰撞，0表示不碰撞 */
static int check_aabb_collision(float x1, float y1, float w1, float h1,
                                float x2, float y2, float w2, float h2)
{
    return (x1 < x2 + w2) && (x1 + w1 > x2) &&
           (y1 < y2 + h2) && (y1 + h1 > y2);
}

/* 游戏核心实现：初始化、关卡加载、存档、成绩与每帧更新 */

/* 初始化游戏上下文：加载存档、设置默认并加载当前关卡 */
void init_game(GameContext *ctx)
{
    load_save(ctx);
    if (ctx->current_level <= 0)
        ctx->current_level = 1;
    if (ctx->selected_char < 0 || ctx->selected_char > CHAR_SNAKE)
        ctx->selected_char = CHAR_CHICKEN;
    ctx->state = STATE_MENU;
    ctx->menu_selected_level = ctx->current_level;
    ctx->level_select_from_char = 0;

    for (int i = 0; i <= MAX_LEVELS; i++)
        ctx->best_times[i] = 0.0f;
    ctx->max_levels = count_levels();
    if (ctx->max_levels <= 0)
        ctx->max_levels = 1;
    if (ctx->current_level > ctx->max_levels)
        ctx->current_level = ctx->max_levels;
    if (ctx->current_level < 1)
        ctx->current_level = 1;
    if (ctx->unlocked_level <= 0)
        ctx->unlocked_level = 1;

    ctx->victory_choice = 0;
    ctx->prev_space_down = 0;

    load_best_times(ctx);
    load_level(ctx, ctx->current_level);
}

/* 从 assets/levels.txt 加载指定关卡的地图并设置玩家起点 */
void load_level(GameContext *ctx, int level_num)
{
    FILE *fp = fopen("./assets/levels.txt", "r");
    if (!fp)
    {
        ctx->state = STATE_VICTORY;
        return;
    }

    char target_header[64];
    sprintf(target_header, "[Level %d]", level_num);
    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, target_header) != NULL)
        {
            found = 1;
            break;
        }
    }

    if (!found)
    {
        ctx->state = STATE_VICTORY;
        fclose(fp);
        return;
    }

    for (int r = 0; r < MAP_ROWS; r++)
    {
        if (!fgets(line, sizeof(line), fp))
            break;

        for (int c = 0; c < MAP_COLS; c++)
        {
            if (line[c] == '\0' || line[c] == '\n' || line[c] == '\r')
            {
                ctx->map[r][c] = TILE_EMPTY;
            }
            else
            {
                ctx->map[r][c] = line[c];
            }

            if (ctx->map[r][c] == TILE_START)
            {
                ctx->start_pos.X = c * TILE_SIZE;
                ctx->start_pos.Y = r * TILE_SIZE;

                ctx->player.x = (float)ctx->start_pos.X;
                ctx->player.y = (float)ctx->start_pos.Y;
                ctx->player.vx = 0.0f;
                ctx->player.vy = 0.0f;

                ctx->player.width = TILE_SIZE - 4;
                ctx->player.height = TILE_SIZE - 2;

                ctx->player.is_grounded = 0;
                ctx->player.is_on_left_wall = 0;
                ctx->player.is_on_right_wall = 0;
                ctx->player.wall_jump_cooldown = 0.0f;
                ctx->player.shove_total = 0.0f;
                ctx->player.shove_time_remaining = 0.0f;
            }
        }
    }

    fclose(fp);

    ctx->level_time = 0.0f;
    ctx->prev_space_down = 0;
}

/* 将简易存档写入 save.dat（已解锁关卡 与 默认角色） */
void save_game(GameContext *ctx)
{
    FILE *fp = fopen("./save.dat", "w");
    if (!fp)
        return;
    fprintf(fp, "%d %d\n", ctx->unlocked_level, (int)ctx->selected_char);
    fclose(fp);
}

/* 从 save.dat 加载存档；若不存在则使用默认值 */
void load_save(GameContext *ctx)
{
    FILE *fp = fopen("./save.dat", "r");
    if (!fp)
    {
        ctx->current_level = 1;
        ctx->selected_char = CHAR_CHICKEN;
        ctx->unlocked_level = 1;
        return;
    }
    int unlocked = 1, ch = 0;
    if (fscanf(fp, "%d %d", &unlocked, &ch) == 2)
    {
        ctx->unlocked_level = unlocked;
        ctx->current_level = ctx->unlocked_level;
        if (ch >= CHAR_CHICKEN && ch <= CHAR_SNAKE)
            ctx->selected_char = (CharacterType)ch;
        else
            ctx->selected_char = CHAR_CHICKEN;
    }
    else
    {
        ctx->current_level = 1;
        ctx->selected_char = CHAR_CHICKEN;
        ctx->unlocked_level = 1;
    }
    fclose(fp);
}

/* 从 best_times.txt 读取每关的最佳记录 */
void load_best_times(GameContext *ctx)
{
    FILE *fp = fopen("./best_times.txt", "r");
    if (!fp)
        return;
    int lvl;
    float t;
    while (fscanf(fp, "%d %f", &lvl, &t) == 2)
    {
        if (lvl >= 1 && lvl <= MAX_LEVELS)
            ctx->best_times[lvl] = t;
    }
    fclose(fp);
}

/* 保存并更新指定关卡的最佳记录，写回文件并检测是否全通获胜 */
void save_best_time(GameContext *ctx, int level, float time)
{
    if (level < 1 || level > MAX_LEVELS)
        return;
    if (ctx->best_times[level] == 0.0f || time < ctx->best_times[level])
        ctx->best_times[level] = time;

    FILE *fp = fopen("./best_times.txt", "w");
    if (!fp)
        return;
    for (int i = 1; i <= ctx->max_levels && i <= MAX_LEVELS; i++)
    {
        if (ctx->best_times[i] > 0.0f)
            fprintf(fp, "%d %.3f\n", i, ctx->best_times[i]);
    }
    fclose(fp);

    int all_top = 1;
    for (int i = 1; i <= ctx->max_levels && i <= MAX_LEVELS; i++)
    {
        if (ctx->best_times[i] <= 0.0f || ctx->best_times[i] > RATING_T1)
        {
            all_top = 0;
            break;
        }
    }
    if (all_top)
    {
        ctx->state = STATE_GAME_COMPLETE;
    }
}

/* 每帧更新游戏逻辑：输入、物理、碰撞、陷阱与终点判断 */
void update_game(GameContext *ctx, float dt, int key_left, int key_right, int key_jump_edge)
{
    if (ctx->state != STATE_PLAYING)
        return;

    ctx->level_time += dt;

    Player *p = &ctx->player;
    int move_dir = key_right - key_left;

    if (p->wall_jump_cooldown > 0.0f)
        p->wall_jump_cooldown -= dt;

    if (p->shove_time_remaining > 0.0f)
    {
        float move_per_sec = p->shove_total / WALL_JUMP_SHOVE_DURATION;
        float move = move_per_sec * dt;
        p->x += move;
        p->shove_time_remaining -= dt;
        if (p->shove_time_remaining <= 0.0f)
        {
            p->shove_time_remaining = 0.0f;
            p->shove_total = 0.0f;
        }
    }

    if (p->is_grounded)
    {
        p->vx = move_dir * WALK_SPEED;
        if (key_jump_edge)
        {
            p->vy = JUMP_FORCE;
            p->is_grounded = 0;
        }
    }
    else
    {
        int wall_jumped = 0;
        if (key_jump_edge && p->wall_jump_cooldown <= 0.0f)
        {
            if (p->is_on_left_wall)
            {
                p->vx = WALL_JUMP_X;
                p->vy = WALL_JUMP_Y;
                p->shove_total = WALL_JUMP_SHOVE_DISTANCE;
                p->shove_time_remaining = WALL_JUMP_SHOVE_DURATION;
                wall_jumped = 1;
            }
            else if (p->is_on_right_wall)
            {
                p->vx = -WALL_JUMP_X;
                p->vy = WALL_JUMP_Y;
                p->shove_total = -WALL_JUMP_SHOVE_DISTANCE;
                p->shove_time_remaining = WALL_JUMP_SHOVE_DURATION;
                wall_jumped = 1;
            }

            if (wall_jumped)
            {
                p->wall_jump_cooldown = WALL_JUMP_COOLDOWN;
            }
        }

        if (!wall_jumped)
        {
            p->vx = move_dir * WALK_SPEED;
        }
    }

    p->vy += GRAVITY * dt;

    if ((p->is_on_left_wall || p->is_on_right_wall) && p->vy > 0)
    {
        if (p->vy > WALL_SLIDE_SPEED)
        {
            p->vy = WALL_SLIDE_SPEED;
        }
    }

    p->is_grounded = 0;
    p->is_on_left_wall = 0;
    p->is_on_right_wall = 0;

    /* X 轴碰撞检测 */
    p->x += p->vx * dt;
    for (int r = 0; r < MAP_ROWS; r++)
    {
        for (int c = 0; c < MAP_COLS; c++)
        {
            if (ctx->map[r][c] == TILE_WALL)
            {
                float tx = c * TILE_SIZE;
                float ty = r * TILE_SIZE;
                float ts = TILE_SIZE;

                if (check_aabb_collision(p->x, p->y, p->width, p->height, tx, ty, ts, ts))
                {
                    if (p->vx > 0)
                    {
                        p->x = tx - p->width;
                        p->is_on_right_wall = 1;
                    }
                    else if (p->vx < 0)
                    {
                        p->x = tx + ts;
                        p->is_on_left_wall = 1;
                    }
                    p->vx = 0.0f;
                }
            }
        }
    }

    /* Y 轴碰撞检测 */
    p->y += p->vy * dt;
    for (int r = 0; r < MAP_ROWS; r++)
    {
        for (int c = 0; c < MAP_COLS; c++)
        {
            if (ctx->map[r][c] == TILE_WALL)
            {
                float tx = c * TILE_SIZE;
                float ty = r * TILE_SIZE;
                float ts = TILE_SIZE;

                if (check_aabb_collision(p->x, p->y, p->width, p->height, tx, ty, ts, ts))
                {
                    if (p->vy > 0)
                    {
                        p->y = ty - p->height;
                        p->is_grounded = 1;
                    }
                    else if (p->vy < 0)
                    {
                        p->y = ty + ts;
                    }
                    p->vy = 0.0f;
                }
            }
        }
    }

    /* 中心格子检测：处理陷阱与终点 */
    int center_x = (int)(p->x + p->width / 2.0f);
    int center_y = (int)(p->y + p->height / 2.0f);
    int grid_c = center_x / TILE_SIZE;
    int grid_r = center_y / TILE_SIZE;

    if (grid_c >= 0 && grid_c < MAP_COLS && grid_r >= 0 && grid_r < MAP_ROWS)
    {
        char current_tile = ctx->map[grid_r][grid_c];

        if (current_tile == TILE_TRAP)
        {
            p->x = (float)ctx->start_pos.X;
            p->y = (float)ctx->start_pos.Y;
            p->vx = 0.0f;
            p->vy = 0.0f;
        }
        else if (current_tile == TILE_GOAL)
        {
            float finish_time = ctx->level_time;
            save_best_time(ctx, ctx->current_level, finish_time);

            if (ctx->unlocked_level <= ctx->current_level)
                ctx->unlocked_level = ctx->current_level + 1;

            save_game(ctx);

            ctx->state = STATE_VICTORY;
        }
    }
}