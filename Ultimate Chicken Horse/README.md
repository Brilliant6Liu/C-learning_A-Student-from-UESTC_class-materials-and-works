# Ultimate Chicken Horse C语言微复刻版

简体中文说明文档 — 项目简介、构建与运行步骤、文件分工与开发提示。

---

## 简介

`Ultimate Chicken Horse` 是一个基于 Win32 GDI 的小型关卡平台演示，包含关卡加载、简单物理（重力、墙跳）、UI 菜单与结算界面。源码以 `C` 语言编写，适合在 Windows + MinGW 环境下编译运行。

## 依赖与环境

- 操作系统：Windows
- 编译器：MinGW-w64 / GCC 或 Visual Studio（可移植）
- 链接库：`gdi32`、`Msimg32`（用于 `AlphaBlend`）
- 推荐字体：`Microsoft YaHei`（界面中文显示更佳）

## 构建（示例）

使用 MinGW 在命令行或 PowerShell 中运行：

```powershell
C:\mingw64\bin\gcc.exe -g "P:\C\Ultimate Chicken Horse\main.c" "P:\C\Ultimate Chicken Horse\game.c" -o "P:\C\Ultimate Chicken Horse\UltimateChickenHorse.exe" -lgdi32 -lMsimg32 -Wall -Wextra
```

工作区中也已配置 VS Code 任务 `C/C++: gcc.exe 生成活动文件`，可用于快速编译当前活动文件。

## 项目结构与分工

- `config.h`：全局配置、常量、类型与跨模块函数原型。
  - 定义画面尺寸、网格尺寸、物理常数（如 `GRAVITY`、`WALK_SPEED`）以及 `GameContext`、`Player` 等数据结构。
- `game.c`：游戏核心逻辑层。
  - 实现 `init_game()`、`load_level()`、`update_game()`、存档与成绩读写（`save_game()`、`load_save()`、`save_best_time()` 等）。
  - 负责物理、碰撞检测、陷阱/终点判定与关卡数据解析。
- `main.c`：窗口、渲染与输入层（UI）。
  - 实现 `WinMain()`、`WndProc()`、`RenderGame()`、资源加载与双缓冲渲染。
  - 管理 `HBITMAP` / `HFONT` 句柄、按钮绘制、界面状态切换，并调用 `game.c` 的接口驱动游戏。

另外，`assets/` 目录存放纹理和 `levels.txt` 等资源（请保证文件路径存在，否则运行时会弹出错误提示）。

## 关卡格式说明

- 关卡文件为 `assets/levels.txt`，按段落组织：

```
[Level 1]
####################
#S                G#
#   ^    ######    #
... (共 MAP_ROWS 行，每行 MAP_COLS 列)
```

- 每个格子使用字符定义：`#` 墙、`^` 陷阱、`S` 起点、`G` 目标、空格为空地。

## 开发提示

- 修改游戏规则/物理：编辑 `game.c` 中的 `update_game()` 与相关常量（`config.h`）。
- 修改 UI、字体或按钮：编辑 `main.c` 中的 `RenderGame()`、`draw_button()` 以及 `WM_CREATE` 中字体创建位置（`CreateFontA`）。
- 文本与编码：源码使用 UTF-8，Windows 控制台输出或任务中可能需要 `chcp 65001` 以避免乱码。

## 常见问题

- 链接错误（未定义 GDI 函数）：请确保编译时加上 `-lgdi32 -lMsimg32`。
- 运行时找不到纹理/关卡：检查 `assets/` 目录与文件名是否完整。

## 贡献与许可证

- 目前未添加许可证文件。如需分发或协作，请在仓库根目录添加 `LICENSE`。
- 欢迎提交改进（例如：更好的 UI、关卡编辑器或跨平台移植）。
