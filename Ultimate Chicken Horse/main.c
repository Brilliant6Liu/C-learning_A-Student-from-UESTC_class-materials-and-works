#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include "config.h"

// ---------------------------------------------------------
// 全局状态与资源定义
// ---------------------------------------------------------
GameContext ctx;

// 图像资源句柄
HBITMAP bmp_wall = NULL;
HBITMAP bmp_trap = NULL;
HBITMAP bmp_goal = NULL;
HBITMAP bmp_chicken = NULL;
HBITMAP bmp_rabbit = NULL;
HBITMAP bmp_snake = NULL;

// ---------------------------------------------------------
// 纯 C 语言 BMP 加载器 (初始化时调用)
// ---------------------------------------------------------
HBITMAP LoadBMPAuto(const char *filepath, HDC hdc)
{
    FILE *file = fopen(filepath, "rb");
    if (!file)
    {
        printf("Failed to load BMP: %s\n", filepath);
        return NULL;
    }

    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
    fread(&bfh, sizeof(BITMAPFILEHEADER), 1, file);
    fread(&bih, sizeof(BITMAPINFOHEADER), 1, file);

    // 计算图像像素数据的大小 (支持 24位 或 32位)
    int width = bih.biWidth;
    int height = abs(bih.biHeight);
    int stride = ((width * bih.biBitCount + 31) / 32) * 4;
    int dataSize = stride * height;

    BYTE *pixels = (BYTE *)malloc(dataSize);
    fseek(file, bfh.bfOffBits, SEEK_SET);
    fread(pixels, 1, dataSize, file);
    fclose(file);

    // 构造位图信息并利用原生 API 生成 HBITMAP 句柄
    BITMAPINFO bmi = {0};
    bmi.bmiHeader = bih;
    HBITMAP hBmp = CreateCompatibleBitmap(hdc, width, height);
    SetDIBits(hdc, hBmp, 0, height, pixels, &bmi, DIB_RGB_COLORS);

    free(pixels);
    return hBmp;
}

// ---------------------------------------------------------
// 透明色渲染函数 (遍历像素跳过粉色掩码)
// ---------------------------------------------------------
void DrawTransparentBmp(HDC hdcDest, int destX, int destY, int width, int height, HBITMAP hBmp)
{
    if (!hBmp)
        return;

    HDC hdcSrc = CreateCompatibleDC(hdcDest);
    SelectObject(hdcSrc, hBmp);

    // 严格按照纯 C 手工遍历像素，跳过 RGB(255,0,255)
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            COLORREF color = GetPixel(hdcSrc, i, j);
            if (color != RGB(255, 0, 255))
            {
                SetPixel(hdcDest, destX + i, destY + j, color);
            }
        }
    }
    DeleteDC(hdcSrc);
}

// ---------------------------------------------------------
// 游戏状态机与画面渲染分发
// ---------------------------------------------------------
void RenderGame(HDC hdcMem)
{
    // 绘制黑色背景底色
    RECT bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    HBRUSH hBgBrush = CreateSolidBrush(RGB(0, 0, 0));
    FillRect(hdcMem, &bgRect, hBgBrush);
    DeleteObject(hBgBrush);

    SetBkMode(hdcMem, TRANSPARENT);
    SetTextColor(hdcMem, RGB(255, 255, 255));

    if (ctx.state == STATE_MENU)
    {
        const char *title = "=== Super Chicken Engine ===";
        const char *prompt = "Press ENTER to Character Select";
        TextOutA(hdcMem, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 20, title, strlen(title));
        TextOutA(hdcMem, SCREEN_WIDTH / 2 - 110, SCREEN_HEIGHT / 2 + 20, prompt, strlen(prompt));
    }
    else if (ctx.state == STATE_CHAR_SELECT)
    {
        const char *prompt = "Select Skin: [1] Chicken  [2] Rabbit  [3] Snake";
        TextOutA(hdcMem, SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 50, prompt, strlen(prompt));

        // 渲染当前选择的角色预览
        HBITMAP previewBmp = bmp_chicken;
        if (ctx.selected_char == CHAR_RABBIT)
            previewBmp = bmp_rabbit;
        if (ctx.selected_char == CHAR_SNAKE)
            previewBmp = bmp_snake;
        DrawTransparentBmp(hdcMem, SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2, TILE_SIZE, TILE_SIZE, previewBmp);
    }
    else if (ctx.state == STATE_PLAYING)
    {
        // 渲染 15x20 网格地图
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

        // 渲染玩家
        HBITMAP pBmp = bmp_chicken;
        if (ctx.selected_char == CHAR_RABBIT)
            pBmp = bmp_rabbit;
        if (ctx.selected_char == CHAR_SNAKE)
            pBmp = bmp_snake;
        DrawTransparentBmp(hdcMem, (int)ctx.player.x, (int)ctx.player.y, TILE_SIZE, TILE_SIZE, pBmp);
    }
    else if (ctx.state == STATE_VICTORY)
    {
        const char *prompt = "VICTORY! All levels completed.";
        TextOutA(hdcMem, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, prompt, strlen(prompt));
    }
}

// ---------------------------------------------------------
// Win32 消息回调处理
// ---------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        HDC hdc = GetDC(hwnd);
        // 严禁绝对路径，必须按照基于工作目录的相对路径加载
        bmp_wall = LoadBMPAuto("./assets/textures/wall.bmp", hdc);
        bmp_trap = LoadBMPAuto("./assets/textures/trap.bmp", hdc);
        bmp_goal = LoadBMPAuto("./assets/textures/goal.bmp", hdc);
        bmp_chicken = LoadBMPAuto("./assets/textures/char_chicken.bmp", hdc);
        bmp_rabbit = LoadBMPAuto("./assets/textures/char_rabbit.bmp", hdc);
        bmp_snake = LoadBMPAuto("./assets/textures/char_snake.bmp", hdc);
        ReleaseDC(hwnd, hdc);

        init_game(&ctx);
        break;
    }
    case WM_KEYDOWN:
    {
        if (ctx.state == STATE_MENU && wParam == VK_RETURN)
        {
            ctx.state = STATE_CHAR_SELECT;
        }
        else if (ctx.state == STATE_CHAR_SELECT)
        {
            if (wParam == '1')
            {
                ctx.selected_char = CHAR_CHICKEN;
                ctx.state = STATE_PLAYING;
            }
            if (wParam == '2')
            {
                ctx.selected_char = CHAR_RABBIT;
                ctx.state = STATE_PLAYING;
            }
            if (wParam == '3')
            {
                ctx.selected_char = CHAR_SNAKE;
                ctx.state = STATE_PLAYING;
            }
        }
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // GDI 原生双缓冲像素缓冲区创建
        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hbmMem = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
        HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);

        RenderGame(hdcMem);

        // 将后台画布拷贝至前台显示屏幕
        BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, hdcMem, 0, 0, SRCCOPY);

        SelectObject(hdcMem, hbmOld);
        DeleteObject(hbmMem);
        DeleteDC(hdcMem);
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        // 显式释放内存及 GDI 句柄防止泄露
        if (bmp_wall)
            DeleteObject(bmp_wall);
        if (bmp_trap)
            DeleteObject(bmp_trap);
        if (bmp_goal)
            DeleteObject(bmp_goal);
        if (bmp_chicken)
            DeleteObject(bmp_chicken);
        if (bmp_rabbit)
            DeleteObject(bmp_rabbit);
        if (bmp_snake)
            DeleteObject(bmp_snake);

        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// ---------------------------------------------------------
// WinMain 入口与高精度定步长主循环
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
    {
        return -1;
    }

    // 创建固定大小窗口，并调整客户区适配 800x600
    RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

    HWND hwnd = CreateWindowA(
        wc.lpszClassName, "Super Chicken Game Engine - Pure C",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left, rect.bottom - rect.top,
        NULL, NULL, hInstance, NULL);

    if (!hwnd)
        return -1;
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // 高精度时间计数器配置
    LARGE_INTEGER freq, last_time, curr_time;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&last_time);

    float accumulator = 0.0f;
    const float dt = 0.01667f; // 锁定 1/60s 步长

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

            // 当累计时间达到一帧阈值，触发逻辑更新
            while (accumulator >= dt)
            {
                if (ctx.state == STATE_PLAYING)
                {
                    // 异步捕获物理键盘状态映射为 1/0
                    int k_left = (GetAsyncKeyState(VK_LEFT) & 0x8000) ? 1 : 0;
                    int k_right = (GetAsyncKeyState(VK_RIGHT) & 0x8000) ? 1 : 0;
                    int k_space = (GetAsyncKeyState(VK_SPACE) & 0x8000) ? 1 : 0;

                    update_game(&ctx, dt, k_left, k_right, k_space);
                }
                accumulator -= dt;
            }

            // 触发双缓冲渲染刷新
            InvalidateRect(hwnd, NULL, FALSE);
            Sleep(1); // 让出 CPU 控制权，防止 100% 占用空转
        }
    }
    return (int)msg.wParam;
}