/* Ultimate,Chicken Hor.e - ma,n.c.,,
    主程序：窗口创建、消息循环、渲染与事件处理 */
#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"

/* 读取 assets/levels.txt 中定义的关卡数量 */
int count_levels()
{
    FILE *fp = fopen("./assets/levels.txt", "r");
    if (!fp)
        return 0;
    char line[256];
    int cnt = 0;
    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, "[Level") != NULL)
            cnt++;
    }
    fclose(fp);
    return cnt;
}

// ---------------------------------------------------------
// Global game context and bitmaps
// ---------------------------------------------------------
GameContext ctx;

/* 全局资源：位图与 UI 字体句柄 */
HBITMAP bmp_wall = NULL;
HBITMAP bmp_trap = NULL;
HBITMAP bmp_goal = NULL;
HBITMAP bmp_chicken = NULL;
HBITMAP bmp_rabbit = NULL;
HBITMAP bmp_snake = NULL;
HBITMAP bmp_title = NULL;
HBITMAP bmp_char_bg = NULL;

HFONT hFontTitle = NULL;
HFONT hFontNormal = NULL;
HFONT hFontBig = NULL;
/* 按钮专用字体：小号用于暂停按钮，较大用于结算与菜单按钮 */
HFONT hFontBtnSmall = NULL;
HFONT hFontBtnLarge = NULL;

/* 胜利界面按钮位置（用于鼠标检测） */
RECT victory_btn_menu = {0};
RECT victory_btn_next = {0};

/* 将 UTF-8/ANSI 文本转换为宽字符，返回字符长度（不含结束符） */
static int to_wide(const char *text, wchar_t **out)
{
    if (!text || !out)
        return 0;
    int len = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text, -1, NULL, 0);
    UINT codepage = CP_UTF8;
    if (len <= 0)
    {
        len = MultiByteToWideChar(CP_ACP, 0, text, -1, NULL, 0);
        codepage = CP_ACP;
    }
    if (len <= 0)
        return 0;
    *out = malloc(len * sizeof(wchar_t));
    if (!*out)
        return 0;
    MultiByteToWideChar(codepage, 0, text, -1, *out, len);
    return len - 1;
}

static void TextOutU(HDC hdc, int x, int y, const char *text)
{
    wchar_t *wbuf;
    int len = to_wide(text, &wbuf);
    if (len)
    {
        TextOutW(hdc, x, y, wbuf, len);
        free(wbuf);
    }
}

static void GetTextExtentPoint32U(HDC hdc, const char *text, SIZE *outSize)
{
    if (!outSize)
        return;
    outSize->cx = outSize->cy = 0;
    wchar_t *wbuf;
    int len = to_wide(text, &wbuf);
    if (len)
    {
        GetTextExtentPoint32W(hdc, wbuf, len, outSize);
        free(wbuf);
    }
}

static int clamp(int value, int lo, int hi)
{
    return value < lo ? lo : value > hi ? hi
                                        : value;
}

static const char *rating_text(float t)
{
    return t <= RATING_T1   ? "夯"
           : t <= RATING_T2 ? "顶级"
           : t <= RATING_T3 ? "人上人"
           : t <= RATING_T4 ? "NPC"
                            : "拉完了";
}

/* 绘制按钮：填充背景、居中绘制文字；selected 为高亮状态 */
static void draw_button(HDC hdc, RECT r, const char *text, int selected)
{
    HBRUSH brush = CreateSolidBrush(selected ? RGB(90, 110, 150) : RGB(60, 80, 120));
    FillRect(hdc, &r, brush);
    DeleteObject(brush);

    // 计算文字尺寸以便在按钮内部居中绘制
    SIZE tsz = {0};
    GetTextExtentPoint32U(hdc, text, &tsz);
    int tx = r.left + ((r.right - r.left) - tsz.cx) / 2;
    int ty = r.top + ((r.bottom - r.top) - tsz.cy) / 2;
    TextOutU(hdc, tx, ty, text);

    if (selected)
    {
        HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
        HGDIOBJ old = SelectObject(hdc, pen);
        HGDIOBJ oldBrush = SelectObject(hdc, GetStockObject(NULL_BRUSH));
        Rectangle(hdc, r.left - 4, r.top - 4, r.right + 4, r.bottom + 4);
        SelectObject(hdc, oldBrush);
        SelectObject(hdc, old);
        DeleteObject(pen);
    }
}

/* 填充矩形颜色的简易封装 */
static void fill_rect(HDC hdc, RECT rect, COLORREF color)
{
    HBRUSH brush = CreateSolidBrush(color);
    FillRect(hdc, &rect, brush);
    DeleteObject(brush);
}

/* 将位图按目标矩形缩放并绘制 */
static void DrawBmpScaled(HDC hdcDest, int dx, int dy, int dw, int dh, HBITMAP hBmp)
{
    if (!hBmp)
        return;
    HDC hdcSrc = CreateCompatibleDC(hdcDest);
    HBITMAP old = (HBITMAP)SelectObject(hdcSrc, hBmp);
    BITMAP bm;
    GetObject(hBmp, sizeof(bm), &bm);
    SetStretchBltMode(hdcDest, HALFTONE);
    StretchBlt(hdcDest, dx, dy, dw, dh, hdcSrc, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
    SelectObject(hdcSrc, old);
    DeleteDC(hdcSrc);
}

// Pause/menu related rects
RECT pause_btn = {0};
RECT pause_menu_replay = {0};
RECT pause_menu_selectlevel = {0};
RECT pause_menu_selectchar = {0};
RECT pause_menu_exit = {0};

static void goto_level_select(GameContext *ctx)
{
    ctx->menu_selected_level = ctx->current_level;
    if (ctx->menu_selected_level > ctx->unlocked_level)
        ctx->menu_selected_level = ctx->unlocked_level;
    ctx->level_select_from_char = 1;
    ctx->state = STATE_LEVEL_SELECT;
}

static void start_level(GameContext *ctx, int level)
{
    ctx->current_level = clamp(level, 1, ctx->max_levels);
    ctx->level_time = 0.0f;
    ctx->prev_space_down = 0;
    ctx->level_select_from_char = 1;
    load_level(ctx, ctx->current_level);
    ctx->state = STATE_PLAYING;
}

// ---------------------------------------------------------
// Bitmap loading helper (loads BMP file into HBITMAP)
// ---------------------------------------------------------
HBITMAP LoadBMPAuto(const char *filepath, HDC hdc)
{
    FILE *file = fopen(filepath, "rb");
    if (!file)
    {
        // 按用户要求：静默失败（不弹出任何警告），返回 NULL 由调用方决定是否显示
        return NULL;
    }

    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
    fread(&bfh, sizeof(BITMAPFILEHEADER), 1, file);
    fread(&bih, sizeof(BITMAPINFOHEADER), 1, file);

    int width = bih.biWidth;
    int height = abs(bih.biHeight);
    int stride = ((width * bih.biBitCount + 31) / 32) * 4;
    int dataSize = stride * height;

    BYTE *pixels = (BYTE *)malloc(dataSize);
    fseek(file, bfh.bfOffBits, SEEK_SET);
    fread(pixels, 1, dataSize, file);
    fclose(file);

    BITMAPINFO bmi = {0};
    bmi.bmiHeader = bih;
    HBITMAP hBmp = CreateCompatibleBitmap(hdc, width, height);
    SetDIBits(hdc, hBmp, 0, height, pixels, &bmi, DIB_RGB_COLORS);

    free(pixels);
    return hBmp;
}

// ---------------------------------------------------------
// Transparent BMP drawing helper using TransparentBlt
// ---------------------------------------------------------
void DrawTransparentBmp(HDC hdcDest, int destX, int destY, int width, int height, HBITMAP hBmp)
{
    if (!hBmp)
        return;

    HDC hdcSrc = CreateCompatibleDC(hdcDest);
    HBITMAP hbmOld = (HBITMAP)SelectObject(hdcSrc, hBmp);

    /* 使用透明掩码颜色 RGB(255,0,255) 绘制位图 */
    TransparentBlt(hdcDest, destX, destY, width, height, hdcSrc, 0, 0, width, height, RGB(255, 0, 255));

    SelectObject(hdcSrc, hbmOld);
    DeleteDC(hdcSrc);
}

// ---------------------------------------------------------
// UI and game state rendering
// ---------------------------------------------------------
/* 渲染游戏当前界面：根据 ctx.state 绘制不同 UI */
void RenderGame(HDC hdcMem)
{
    SetBkMode(hdcMem, TRANSPARENT); // 设置文本背景为透明

    if (ctx.state == STATE_MENU)
    {
        /* 主菜单：绘制标题背景、提示与版本信息 */

        if (bmp_title)
        {
            DrawBmpScaled(hdcMem, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bmp_title);
        }
        else
        {
            RECT bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
            HBRUSH hBgBrush = CreateSolidBrush(RGB(20, 30, 50));
            FillRect(hdcMem, &bgRect, hBgBrush);
            DeleteObject(hBgBrush);
        }

        const char *prompt = ">>> 按 Enter 开始游戏 <<<";
        // 背景为浅色图时使用深色文字以提高对比度
        SetTextColor(hdcMem, RGB(30, 30, 30));
        SelectObject(hdcMem, hFontNormal);
        int center = SCREEN_WIDTH / 2;
        int promptY = 420;

        SIZE textSize;
        GetTextExtentPoint32U(hdcMem, prompt, &textSize);
        int padding = 25;
        RECT boxRect = {
            center - (textSize.cx / 2) - padding,
            promptY - padding,
            center + (textSize.cx / 2) + padding,
            promptY + textSize.cy + padding};

        // 使用深色边框以便在浅色标题图上可见
        HPEN hFramePen = CreatePen(PS_SOLID, 2, RGB(30, 30, 30));
        HPEN hOldPen = (HPEN)SelectObject(hdcMem, hFramePen);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdcMem, GetStockObject(NULL_BRUSH));
        Rectangle(hdcMem, boxRect.left, boxRect.top, boxRect.right, boxRect.bottom);
        SelectObject(hdcMem, hOldBrush);
        SelectObject(hdcMem, hOldPen);
        DeleteObject(hFramePen);

        TextOutU(hdcMem, center - (textSize.cx / 2), promptY, prompt);

        SetTextColor(hdcMem, RGB(30, 30, 30));
        const char *version = "v1.0.0 Powered by Win32 GDI";
        TextOutU(hdcMem, 10, SCREEN_HEIGHT - 30, version);
    }
    else if (ctx.state == STATE_CHAR_SELECT)
    {
        SetTextColor(hdcMem, RGB(30, 30, 30));
        SelectObject(hdcMem, hFontBig);
        // character select background (scaled image if available)
        if (bmp_char_bg)
            DrawBmpScaled(hdcMem, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bmp_char_bg);
        else
        {
            RECT bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
            HBRUSH hBgBrush = CreateSolidBrush(RGB(30, 30, 30));
            FillRect(hdcMem, &bgRect, hBgBrush);
            DeleteObject(hBgBrush);
        }

        // 选角页面在浅色背景下使用深色标题文字并居中显示
        SetTextColor(hdcMem, RGB(30, 30, 30));
        SelectObject(hdcMem, hFontTitle);
        const char *title = "角色选择";
        SIZE titleSz;
        GetTextExtentPoint32U(hdcMem, title, &titleSz);
        TextOutU(hdcMem, (SCREEN_WIDTH - titleSz.cx) / 2, 100, title);

        /* 角色选择：布局参数 */
        int boxW = 120, boxH = 150;
        int gap = 80;
        int startX = (SCREEN_WIDTH - (3 * boxW + 2 * gap)) / 2;
        int startY = 180;
        /* 角色资源与名称 */
        HBITMAP charBmps[3] = {bmp_chicken, bmp_rabbit, bmp_snake};
        const char *charNames[3] = {"[1] 奇克", "[2] 邦尼", "[3] 蛇嘶嘶"};
        CharacterType charTypes[3] = {CHAR_CHICKEN, CHAR_RABBIT, CHAR_SNAKE};

        SelectObject(hdcMem, hFontNormal);

        /* 遍历三个角色卡片并绘制 */
        for (int i = 0; i < 3; i++)
        {
            int cx = startX + i * (boxW + gap);
            int cy = startY;
            /* 选中项高亮显示 */
            if (ctx.selected_char == charTypes[i])
            {
                RECT highlight = {cx - 5, cy - 5, cx + boxW + 5, cy + boxH + 5};
                HBRUSH hHighBrush = CreateSolidBrush(RGB(255, 50, 50));
                FillRect(hdcMem, &highlight, hHighBrush);
                DeleteObject(hHighBrush);
            }
            /* 卡片背景 */
            RECT cardRect = {cx, cy, cx + boxW, cy + boxH};
            HBRUSH hCardBrush = CreateSolidBrush(RGB(60, 60, 80));
            FillRect(hdcMem, &cardRect, hCardBrush);
            DeleteObject(hCardBrush);
            /* 绘制角色图像 */
            DrawTransparentBmp(hdcMem, cx + (boxW - TILE_SIZE) / 2, cy + 30, TILE_SIZE, TILE_SIZE, charBmps[i]);
            /* 绘制角色名称 */
            SetTextColor(hdcMem, (ctx.selected_char == charTypes[i]) ? RGB(255, 255, 100) : RGB(200, 200, 200));
            TextOutU(hdcMem, cx + 25, cy + 100, charNames[i]);
        }

        // 底部提示也使用深色以便在浅色背景上可读
        SetTextColor(hdcMem, RGB(30, 30, 30));
        const char *prompt = "按 1/2/3 选择角色，Enter 开始";
        TextOutU(hdcMem, SCREEN_WIDTH / 2 - 160, 480, prompt);
    }
    else if (ctx.state == STATE_LEVEL_SELECT)
    {
        RECT bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        HBRUSH hBgBrush = CreateSolidBrush(RGB(30, 40, 70));
        FillRect(hdcMem, &bgRect, hBgBrush);
        DeleteObject(hBgBrush);

        SetTextColor(hdcMem, RGB(255, 255, 255));
        SelectObject(hdcMem, hFontTitle);
        const char *title = "关卡选择";
        TextOutU(hdcMem, SCREEN_WIDTH / 2 - 100, 40, title);

        SelectObject(hdcMem, hFontNormal);
        int cols = 3; // 3 columns
        int rows = 4; // 4 rows
        int boxW = 140, boxH = 100;
        int gap = 20;
        int total = ctx.max_levels;
        if (total > cols * rows)
            total = cols * rows; // show up to 12 slots
        int startX = (SCREEN_WIDTH - (cols * boxW + (cols - 1) * gap)) / 2;
        int startY = 120;
        char buf[64];
        for (int i = 0; i < total; i++)
        {
            int idx = i + 1;
            int cx = startX + (i % cols) * (boxW + gap);
            int cy = startY + (i / cols) * (boxH + gap);

            RECT box = {cx, cy, cx + boxW, cy + boxH};
            /* 选中项高亮：以填充色突出整个框 */
            if (idx == ctx.menu_selected_level)
            {
                HBRUSH hSelBrush = CreateSolidBrush(RGB(255, 215, 0));
                FillRect(hdcMem, &box, hSelBrush);
                DeleteObject(hSelBrush);
            }
            else
            {
                HBRUSH hBoxBrush = CreateSolidBrush(RGB(80, 90, 120));
                FillRect(hdcMem, &box, hBoxBrush);
                DeleteObject(hBoxBrush);
            }

            // 锁定显示（仍然以锁文字表示）
            if (idx > ctx.unlocked_level)
            {
                SetTextColor(hdcMem, RGB(100, 100, 100));
                const char *locked = "锁";
                TextOutU(hdcMem, cx + boxW / 2 - 8, cy + boxH / 2 - 8, locked);
                sprintf(buf, "%d", idx);
                TextOutU(hdcMem, cx + 6, cy + 6, buf);
            }
            else
            {
                // 显示关卡号：使用更大字体居中绘制，选中项使用深色文字以便在高亮背景上可读
                if (idx == ctx.menu_selected_level)
                    SetTextColor(hdcMem, RGB(30, 30, 30));
                else
                    SetTextColor(hdcMem, RGB(220, 220, 220));

                sprintf(buf, "%d", idx);
                // 使用标题字体放大关卡数字并居中
                SelectObject(hdcMem, hFontTitle);
                SIZE numSz;
                GetTextExtentPoint32U(hdcMem, buf, &numSz);
                TextOutU(hdcMem, cx + (boxW - numSz.cx) / 2, cy + (boxH - numSz.cy) / 2, buf);

                // 已完成显示评分（如果有），使用正常字体绘制在底部
                float bt = 0.0f;
                if (idx <= MAX_LEVELS)
                    bt = ctx.best_times[idx];
                if (bt > 0.0f)
                {
                    SelectObject(hdcMem, hFontNormal);
                    SetTextColor(hdcMem, (idx == ctx.menu_selected_level) ? RGB(30, 30, 30) : RGB(200, 230, 140));
                    TextOutU(hdcMem, cx + 8, cy + boxH - 24, rating_text(bt));
                }
                else
                {
                    // 若无评分，恢复默认小号字体以免影响下一项绘制
                    SelectObject(hdcMem, hFontNormal);
                }
            }
        }

        const char *hint = "←/→/↑/↓ 选择关卡，Enter 开始";
        SetTextColor(hdcMem, RGB(180, 180, 200));
        TextOutU(hdcMem, SCREEN_WIDTH / 2 - 140, SCREEN_HEIGHT - 40, hint);
    }
    else if (ctx.state == STATE_PLAYING)
    {
        /* 游戏中：绘制地图、玩家与 UI */
        RECT bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        HBRUSH hBgBrush = CreateSolidBrush(RGB(135, 206, 235));
        FillRect(hdcMem, &bgRect, hBgBrush);
        DeleteObject(hBgBrush);

        /* 绘制地图格子 */
        for (int r = 0; r < MAP_ROWS; r++)
        {
            for (int c = 0; c < MAP_COLS; c++)
            {
                int px = c * TILE_SIZE;
                int py = r * TILE_SIZE;
                char tile = ctx.map[r][c];

                if (tile == TILE_WALL)
                    DrawTransparentBmp(hdcMem, px, py, TILE_SIZE, TILE_SIZE, bmp_wall);
                else if (tile == TILE_TRAP)
                    DrawTransparentBmp(hdcMem, px, py, TILE_SIZE, TILE_SIZE, bmp_trap);
                else if (tile == TILE_GOAL)
                    DrawTransparentBmp(hdcMem, px, py, TILE_SIZE, TILE_SIZE, bmp_goal);
            }
        }

        /* 绘制玩家角色 */
        HBITMAP pBmp = bmp_chicken;
        if (ctx.selected_char == CHAR_RABBIT)
            pBmp = bmp_rabbit;
        if (ctx.selected_char == CHAR_SNAKE)
            pBmp = bmp_snake;
        DrawTransparentBmp(hdcMem, (int)ctx.player.x, (int)ctx.player.y, TILE_SIZE, TILE_SIZE, pBmp);

        /* 左上角：当前关卡编号与暂停按钮 */
        SelectObject(hdcMem, hFontNormal);
        SetTextColor(hdcMem, RGB(30, 30, 30));
        char lvlbuf[64];
        sprintf(lvlbuf, "关卡 %d", ctx.current_level);
        pause_btn.left = 10;
        pause_btn.top = 10;
        pause_btn.right = 10 + 56;
        pause_btn.bottom = 10 + 28;
        SelectObject(hdcMem, hFontBtnSmall);
        draw_button(hdcMem, pause_btn, "暂停", 0);
        SelectObject(hdcMem, hFontNormal);
        TextOutU(hdcMem, pause_btn.right + 8, 12, lvlbuf);

        // 右上角：计时器
        char timebuf[64];
        sprintf(timebuf, "时间: %.2f s", ctx.level_time);
        SIZE tsz;
        GetTextExtentPoint32U(hdcMem, timebuf, &tsz);
        TextOutU(hdcMem, SCREEN_WIDTH - tsz.cx - 10, 10, timebuf);
    }
    else if (ctx.state == STATE_VICTORY)
    {
        RECT bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        fill_rect(hdcMem, bgRect, RGB(10, 10, 20));

        SelectObject(hdcMem, hFontBig);
        SetTextColor(hdcMem, RGB(255, 220, 80));
        char finishbuf[128];
        sprintf(finishbuf, "通关时间: %.2f s", ctx.level_time);
        TextOutU(hdcMem, SCREEN_WIDTH / 2 - 160, SCREEN_HEIGHT / 2 - 80, finishbuf);

        const char *rating = rating_text(ctx.level_time);
        SelectObject(hdcMem, hFontTitle);
        SetTextColor(hdcMem, RGB(255, 255, 255));
        TextOutU(hdcMem, SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2 - 20, rating);

        RECT btnMenu = {SCREEN_WIDTH / 2 - 140, SCREEN_HEIGHT / 2 + 40, SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 + 80};
        RECT btnNext = {SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT / 2 + 40, SCREEN_WIDTH / 2 + 140, SCREEN_HEIGHT / 2 + 80};
        SelectObject(hdcMem, hFontBtnLarge);
        draw_button(hdcMem, btnMenu, "菜单", ctx.victory_choice == 0);
        draw_button(hdcMem, btnNext, "下一关", ctx.victory_choice != 0);
        SelectObject(hdcMem, hFontTitle);

        victory_btn_menu = btnMenu;
        victory_btn_next = btnNext;

        SetTextColor(hdcMem, RGB(180, 180, 200));
        TextOutU(hdcMem, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 90, "←/→ 选择，Enter 确认");
    }
    else if (ctx.state == STATE_PAUSED)
    {
        // handled in main loop: draw semi-transparent overlay and centered options
        // create 50% alpha overlay across whole screen
        HDC tmp = CreateCompatibleDC(hdcMem);
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = SCREEN_WIDTH;
        bmi.bmiHeader.biHeight = -SCREEN_HEIGHT; // top-down
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        void *bits = NULL;
        HBITMAP hbm = CreateDIBSection(tmp, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
        HBITMAP old = (HBITMAP)SelectObject(tmp, hbm);
        DWORD *px = (DWORD *)bits;
        int pixels = SCREEN_WIDTH * SCREEN_HEIGHT;
        for (int i = 0; i < pixels; i++)
            px[i] = (128 << 24) | (0 << 16) | (0 << 8) | 0;
        BLENDFUNCTION bf = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
        AlphaBlend(hdcMem, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, tmp, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bf);
        SelectObject(tmp, old);
        DeleteObject(hbm);
        DeleteDC(tmp);

        // centered menu
        int mw = 360, mh = 300;
        int mx = (SCREEN_WIDTH - mw) / 2;
        int my = (SCREEN_HEIGHT - mh) / 2;
        int bw = 220, bh = 44;
        int bx = mx + (mw - bw) / 2;
        int by = my + 80;
        pause_menu_replay.left = bx;
        pause_menu_replay.top = by;
        pause_menu_replay.right = bx + bw;
        pause_menu_replay.bottom = by + bh;
        /* 使用较大按钮字体绘制暂停菜单项 */
        SelectObject(hdcMem, hFontBtnLarge);
        draw_button(hdcMem, pause_menu_replay, "重玩", 0);
        pause_menu_selectlevel.left = bx;
        pause_menu_selectlevel.top = by + 56;
        pause_menu_selectlevel.right = bx + bw;
        pause_menu_selectlevel.bottom = by + 56 + bh;
        draw_button(hdcMem, pause_menu_selectlevel, "选关", 0);
        pause_menu_selectchar.left = bx;
        pause_menu_selectchar.top = by + 112;
        pause_menu_selectchar.right = bx + bw;
        pause_menu_selectchar.bottom = by + 112 + bh;
        draw_button(hdcMem, pause_menu_selectchar, "选择角色", 0);
        pause_menu_exit.left = bx;
        pause_menu_exit.top = by + 168;
        pause_menu_exit.right = bx + bw;
        pause_menu_exit.bottom = by + 168 + bh;
        draw_button(hdcMem, pause_menu_exit, "退出游戏", 0);
        /* 恢复默认字体 */
        SelectObject(hdcMem, hFontNormal);
    }
    else if (ctx.state == STATE_GAME_COMPLETE)
    {
        RECT bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        HBRUSH hBg = CreateSolidBrush(RGB(10, 10, 10));
        FillRect(hdcMem, &bgRect, hBg);
        DeleteObject(hBg);
        SelectObject(hdcMem, hFontTitle);
        SetTextColor(hdcMem, RGB(255, 220, 0));
        const char *msg = "？！强强！？";
        SIZE tsz;
        GetTextExtentPoint32U(hdcMem, msg, &tsz);
        TextOutU(hdcMem, (SCREEN_WIDTH - tsz.cx) / 2, (SCREEN_HEIGHT - tsz.cy) / 2, msg);
    }
}

// ---------------------------------------------------------
// Win32 window procedure
// ---------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        HDC hdc = GetDC(hwnd);

        /* 加载位图资源并创建 UI 字体 */
        bmp_wall = LoadBMPAuto("./assets/textures/wall.bmp", hdc);
        bmp_trap = LoadBMPAuto("./assets/textures/trap.bmp", hdc);
        bmp_goal = LoadBMPAuto("./assets/textures/goal.bmp", hdc);
        // 按用户要求：仅加载指定的 BMP 路径（静默失败）
        bmp_title = LoadBMPAuto("./assets/textures/title.bmp", hdc);
        bmp_char_bg = LoadBMPAuto("./assets/textures/Selectcharacter.bmp", hdc);
        bmp_chicken = LoadBMPAuto("./assets/textures/char_chicken.bmp", hdc);
        bmp_rabbit = LoadBMPAuto("./assets/textures/char_rabbit.bmp", hdc);
        bmp_snake = LoadBMPAuto("./assets/textures/char_snake.bmp", hdc);

        // 自定义 UI 字体（使用英文字体名避免编码问题）
        hFontTitle = CreateFontA(36, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "Microsoft YaHei");
        hFontNormal = CreateFontA(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "Microsoft YaHei");
        hFontBig = CreateFontA(48, 0, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "SimHei");
        hFontBtnSmall = CreateFontA(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "Microsoft YaHei");
        hFontBtnLarge = CreateFontA(22, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "Microsoft YaHei");

        ReleaseDC(hwnd, hdc);

        init_game(&ctx);
        // 确保菜单显示正确
        ctx.state = STATE_MENU;
        break;
    }
    case WM_KEYDOWN:
    {
        if (ctx.state == STATE_MENU)
        {
            if (wParam == VK_RETURN)
            {
                ctx.state = STATE_CHAR_SELECT;
            }
        }
        else if (ctx.state == STATE_CHAR_SELECT)
        {
            /* 角色选择：键盘输入处理 */
            if (wParam == '1')
            {
                ctx.selected_char = CHAR_CHICKEN;
                goto_level_select(&ctx);
            }
            if (wParam == '2')
            {
                ctx.selected_char = CHAR_RABBIT;
                goto_level_select(&ctx);
            }
            if (wParam == '3')
            {
                ctx.selected_char = CHAR_SNAKE;
                goto_level_select(&ctx);
            }
            if (wParam == VK_LEFT)
                ctx.selected_char = (ctx.selected_char == CHAR_CHICKEN) ? CHAR_SNAKE : ctx.selected_char - 1;
            if (wParam == VK_RIGHT)
                ctx.selected_char = (ctx.selected_char == CHAR_SNAKE) ? CHAR_CHICKEN : ctx.selected_char + 1;
            if (wParam == VK_RETURN)
                goto_level_select(&ctx);
        }
        else if (ctx.state == STATE_LEVEL_SELECT)
        {
            if (ctx.menu_selected_level > ctx.unlocked_level)
                ctx.menu_selected_level = ctx.unlocked_level;
            int cols = 3; // 与绘制时的列数保持一致
            if (wParam == VK_LEFT)
            {
                if (ctx.menu_selected_level > 1)
                    ctx.menu_selected_level--;
            }
            else if (wParam == VK_RIGHT)
            {
                if (ctx.menu_selected_level < ctx.unlocked_level)
                    ctx.menu_selected_level++;
            }
            else if (wParam == VK_UP)
            {
                if (ctx.menu_selected_level > cols)
                    ctx.menu_selected_level -= cols;
                else
                    ctx.menu_selected_level = 1;
            }
            else if (wParam == VK_DOWN)
            {
                if (ctx.menu_selected_level + cols <= ctx.unlocked_level)
                    ctx.menu_selected_level += cols;
                else
                    ctx.menu_selected_level = ctx.unlocked_level;
            }
            else if (wParam == VK_RETURN)
            {
                if (ctx.menu_selected_level <= ctx.unlocked_level)
                {
                    if (ctx.level_select_from_char)
                        start_level(&ctx, ctx.menu_selected_level);
                    else
                        ctx.state = STATE_CHAR_SELECT;
                }
            }
        }
        else if (ctx.state == STATE_VICTORY)
        {
            if (wParam == VK_RETURN)
            {
                if (ctx.victory_choice == 0)
                    goto_level_select(&ctx);
                else
                    start_level(&ctx, ctx.current_level < ctx.max_levels ? ctx.current_level + 1 : ctx.current_level);
            }
            else if (wParam == VK_LEFT || wParam == VK_RIGHT)
            {
                ctx.victory_choice = !ctx.victory_choice;
            }
        }
        break;
    }
    case WM_LBUTTONDOWN:
    {
        int mx = (int)(short)LOWORD(lParam);
        int my = (int)(short)HIWORD(lParam);
        POINT pt = {mx, my};
        if (ctx.state == STATE_PLAYING)
        {
            if (PtInRect(&pause_btn, pt))
            {
                ctx.state = STATE_PAUSED;
                InvalidateRect(hwnd, NULL, FALSE);
            }
        }
        else if (ctx.state == STATE_VICTORY)
        {
            if (PtInRect(&victory_btn_menu, pt))
            {
                goto_level_select(&ctx);
                InvalidateRect(hwnd, NULL, FALSE);
            }
            else if (PtInRect(&victory_btn_next, pt))
            {
                start_level(&ctx, ctx.current_level < ctx.max_levels ? ctx.current_level + 1 : ctx.current_level);
                InvalidateRect(hwnd, NULL, FALSE);
            }
        }
        else if (ctx.state == STATE_PAUSED)
        {
            if (PtInRect(&pause_menu_replay, pt))
            {
                start_level(&ctx, ctx.current_level);
                InvalidateRect(hwnd, NULL, FALSE);
            }
            else if (PtInRect(&pause_menu_selectlevel, pt))
            {
                goto_level_select(&ctx);
                InvalidateRect(hwnd, NULL, FALSE);
            }
            else if (PtInRect(&pause_menu_selectchar, pt))
            {
                ctx.state = STATE_CHAR_SELECT;
                InvalidateRect(hwnd, NULL, FALSE);
            }
            else if (PtInRect(&pause_menu_exit, pt))
            {
                PostQuitMessage(0);
            }
        }
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // 使用兼容内存 DC 进行双缓冲绘制
        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hbmMem = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
        HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);

        RenderGame(hdcMem);

        // 将内存缓冲区的画面复制到窗口 DC
        BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, hdcMem, 0, 0, SRCCOPY);

        SelectObject(hdcMem, hbmOld);
        DeleteObject(hbmMem);
        DeleteDC(hdcMem);
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        /* 窗口销毁：释放所有 GDI 资源 */
        if (bmp_wall)
            DeleteObject(bmp_wall);
        if (bmp_trap)
            DeleteObject(bmp_trap);
        if (bmp_goal)
            DeleteObject(bmp_goal);
        if (bmp_title)
            DeleteObject(bmp_title);
        if (bmp_char_bg)
            DeleteObject(bmp_char_bg);
        if (bmp_chicken)
            DeleteObject(bmp_chicken);
        if (bmp_rabbit)
            DeleteObject(bmp_rabbit);
        if (bmp_snake)
            DeleteObject(bmp_snake);

        if (hFontTitle)
            DeleteObject(hFontTitle);
        if (hFontNormal)
            DeleteObject(hFontNormal);
        if (hFontBig)
            DeleteObject(hFontBig);
        if (hFontBtnSmall)
            DeleteObject(hFontBtnSmall);
        if (hFontBtnLarge)
            DeleteObject(hFontBtnLarge);

        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// ---------------------------------------------------------
// WinMain and main loop
// ---------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "SuperChickenHorseEngine";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClassA(&wc))
        return -1;

    RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

    HWND hwnd = CreateWindowA(
        wc.lpszClassName, "Ultimate Chicken Horse - Win32",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left, rect.bottom - rect.top,
        NULL, NULL, hInstance, NULL);

    if (!hwnd)
        return -1;
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // 使用高精度计时器实现近似 60FPS 的游戏循环
    LARGE_INTEGER freq, last_time, curr_time;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&last_time);

    float accumulator = 0.0f;
    const float dt = 0.01667f;

    MSG msg = {0};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            QueryPerformanceCounter(&curr_time);
            float frameTime = (float)(curr_time.QuadPart - last_time.QuadPart) / freq.QuadPart;
            last_time = curr_time;
            accumulator += frameTime;

            while (accumulator >= dt)
            {
                if (ctx.state == STATE_PLAYING)
                {
                    int k_left = (GetAsyncKeyState(VK_LEFT) & 0x8000) ? 1 : 0;
                    int k_right = (GetAsyncKeyState(VK_RIGHT) & 0x8000) ? 1 : 0;
                    int k_space = (GetAsyncKeyState(VK_SPACE) & 0x8000) ? 1 : 0;
                    int k_space_edge = (k_space && !ctx.prev_space_down) ? 1 : 0;
                    ctx.prev_space_down = k_space;

                    update_game(&ctx, dt, k_left, k_right, k_space_edge);
                }
                accumulator -= dt;
            }
            InvalidateRect(hwnd, NULL, FALSE);
            Sleep(1);
        }
    }
    return (int)msg.wParam;
}