#include "config.h"
#include <stdio.h>
#include <string.h>

// ==========================================
// 内部辅助函数：AABB 矩形碰撞检测
// ==========================================
static int check_aabb_collision(float x1, float y1, float w1, float h1,
                                float x2, float y2, float w2, float h2)
{
    return (x1 < x2 + w2) && (x1 + w1 > x2) &&
           (y1 < y2 + h2) && (y1 + h1 > y2);
}

// ==========================================
// 核心接口实现
// ==========================================

void init_game(GameContext *ctx)
{
    // 游戏状态初始化
    ctx->state = STATE_MENU;
    ctx->selected_char = CHAR_CHICKEN;
    ctx->current_level = 1;

    // 默认加载第一关
    load_level(ctx, ctx->current_level);
}

void load_level(GameContext *ctx, int level_num)
{
    // 只读模式打开外部关卡配置
    FILE *fp = fopen("./assets/levels.txt", "r");
    if (!fp)
    {
        // 文件缺失，直接触发通关/胜利状态以防止崩溃
        ctx->state = STATE_VICTORY;
        return;
    }

    char target_header[64];
    sprintf(target_header, "[Level %d]", level_num);
    char line[256];
    int found = 0;

    // 扫描定位目标关卡区块
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
        // 若没有找到后续关卡，修改状态为胜利
        ctx->state = STATE_VICTORY;
        fclose(fp);
        return;
    }

    // 解析目标关卡网格
    for (int r = 0; r < MAP_ROWS; r++)
    {
        if (!fgets(line, sizeof(line), fp))
            break;

        for (int c = 0; c < MAP_COLS; c++)
        {
            // 处理行尾回车或数据不足的安全填充
            if (line[c] == '\0' || line[c] == '\n' || line[c] == '\r')
            {
                ctx->map[r][c] = TILE_EMPTY;
            }
            else
            {
                ctx->map[r][c] = line[c];
            }

            // 起点解析与玩家重置
            if (ctx->map[r][c] == TILE_START)
            {
                ctx->start_pos.X = c * TILE_SIZE;
                ctx->start_pos.Y = r * TILE_SIZE;

                // 重置玩家物理参数
                ctx->player.x = (float)ctx->start_pos.X;
                ctx->player.y = (float)ctx->start_pos.Y;
                ctx->player.vx = 0.0f;
                ctx->player.vy = 0.0f;

                // 玩家尺寸设定 (略小于 TILE_SIZE 以允许流畅通过缝隙)
                ctx->player.width = TILE_SIZE - 4;
                ctx->player.height = TILE_SIZE - 2;

                // 状态标志归零
                ctx->player.is_grounded = 0;
                ctx->player.is_on_left_wall = 0;
                ctx->player.is_on_right_wall = 0;
            }
        }
    }

    fclose(fp);
}

void update_game(GameContext *ctx, float dt, int key_left, int key_right, int key_jump)
{
    if (ctx->state != STATE_PLAYING)
        return;

    Player *p = &ctx->player;
    int move_dir = key_right - key_left;

    // ------------------------------------------
    // 1. 物理输入与状态处理
    // ------------------------------------------
    if (p->is_grounded)
    {
        // 地面移动
        p->vx = move_dir * WALK_SPEED;

        // 起跳
        if (key_jump)
        {
            p->vy = JUMP_FORCE;
            p->is_grounded = 0;
        }
    }
    else
    {
        // 空中状态与墙跳
        int wall_jumped = 0;
        if (p->is_on_left_wall && key_jump)
        {
            p->vx = WALL_JUMP_X;
            p->vy = WALL_JUMP_Y;
            wall_jumped = 1;
        }
        else if (p->is_on_right_wall && key_jump)
        {
            p->vx = -WALL_JUMP_X;
            p->vy = WALL_JUMP_Y;
            wall_jumped = 1;
        }

        // 正常空中移动微调
        if (!wall_jumped)
        {
            p->vx = move_dir * WALK_SPEED;
        }
    }

    // 重力积分
    p->vy += GRAVITY * dt;

    // 挂墙摩擦阻尼 (当下落且贴墙时生效)
    if ((p->is_on_left_wall || p->is_on_right_wall) && p->vy > 0)
    {
        if (p->vy > WALL_SLIDE_SPEED)
        {
            p->vy = WALL_SLIDE_SPEED;
        }
    }

    // 重置本帧接触状态（将在碰撞检测中重新判定）
    p->is_grounded = 0;
    p->is_on_left_wall = 0;
    p->is_on_right_wall = 0;

    // ------------------------------------------
    // 2. 运动积分与分轴 AABB 碰撞响应
    // ------------------------------------------

    // --- X轴 更新与响应 ---
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
                        p->x = tx - p->width; // 撞到右侧墙壁
                        p->is_on_right_wall = 1;
                    }
                    else if (p->vx < 0)
                    {
                        p->x = tx + ts; // 撞到左侧墙壁
                        p->is_on_left_wall = 1;
                    }
                    p->vx = 0.0f;
                }
            }
        }
    }

    // --- Y轴 更新与响应 ---
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
                        p->y = ty - p->height; // 向下碰地
                        p->is_grounded = 1;
                    }
                    else if (p->vy < 0)
                    {
                        p->y = ty + ts; // 向上撞顶
                    }
                    p->vy = 0.0f;
                }
            }
        }
    }

    // ------------------------------------------
    // 3. 触发器判定 (陷阱与终点)
    // ------------------------------------------
    // 获取玩家中心点并转为网格索引
    int center_x = (int)(p->x + p->width / 2.0f);
    int center_y = (int)(p->y + p->height / 2.0f);
    int grid_c = center_x / TILE_SIZE;
    int grid_r = center_y / TILE_SIZE;

    // 安全边界防御 (严格限制在 0 ~ 极值 之间)
    if (grid_c >= 0 && grid_c < MAP_COLS && grid_r >= 0 && grid_r < MAP_ROWS)
    {
        char current_tile = ctx->map[grid_r][grid_c];

        if (current_tile == TILE_TRAP)
        {
            // 踩到陷阱，死亡重置
            p->x = (float)ctx->start_pos.X;
            p->y = (float)ctx->start_pos.Y;
            p->vx = 0.0f;
            p->vy = 0.0f;
        }
        else if (current_tile == TILE_GOAL)
        {
            // 到达终点，推进关卡
            ctx->current_level++;
            load_level(ctx, ctx->current_level);

            // 注意: 若 load_level 未能找到下一关，它会自动将 state 修改为 STATE_VICTORY
        }
    }
}