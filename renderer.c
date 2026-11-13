#include <raylib.h>
#include "renderer.h"
#include "physics.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define CENTER_X (WIN_WIDTH / 2)
#define CENTER_Y (WIN_HEIGHT / 2)

static double METERS_PER_PIXEL = 1.0e9;

static Color get_color(int color_id)
{
    switch (color_id)
    {
    case 0:
        return GOLD; // Sun
    case 1:
        return SKYBLUE; // Earth
    case 2:
        return LIGHTGRAY; // Mercury
    case 3:
        return RED; // Mars
    case 4:
        return ORANGE; // Venus
    case 5:
        return WHITE; // Comet
    case 6:
        return BROWN; // Jupiter
    case 7:
        return BEIGE; // Saturn
    case 8:
        return BLUE; // Uranus
    case 9:
        return DARKBLUE; // Neptune
    default:
        return MAGENTA;
    }
}

void gui_init()
{
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "N-body Solar System Simulator");
    SetTargetFPS(60);
}

int gui_should_close()
{
    return WindowShouldClose();
}

void gui_begin_frame()
{
    float wheel = GetMouseWheelMove();
    if (wheel != 0.0f)
        METERS_PER_PIXEL *= (wheel > 0.0f) ? 0.85 : 1.15;

    BeginDrawing();
    ClearBackground(BLACK);
}

void gui_end_frame()
{
    EndDrawing();
}

void gui_draw_trail(double x1, double y1, double x2, double y2, int color_id)
{
    int sx1 = CENTER_X + (int)(x1 / METERS_PER_PIXEL);
    int sy1 = CENTER_Y - (int)(y1 / METERS_PER_PIXEL);
    int sx2 = CENTER_X + (int)(x2 / METERS_PER_PIXEL);
    int sy2 = CENTER_Y - (int)(y2 / METERS_PER_PIXEL);

    Color col = Fade(get_color(color_id), 0.33f);
    DrawLine(sx1, sy1, sx2, sy2, col);
}

void gui_draw_planet(double x, double y, double radius, const char *name, int color_id)
{
    int screen_x = CENTER_X + (int)(x / METERS_PER_PIXEL);
    int screen_y = CENTER_Y - (int)(y / METERS_PER_PIXEL);

    DrawCircle(screen_x, screen_y, (float)radius, get_color(color_id));

    int text_offset = (my_strlen(name) * 9) / 2;
    DrawText(name, screen_x - text_offset, screen_y - (int)radius - 18, 16, LIGHTGRAY);
}

void gui_draw_leaderboard(char names[][16], int *speeds, int count)
{
    int start_x = WIN_WIDTH - 280;
    int start_y = 20;

    DrawText("Speed Leaderboard", start_x, start_y, 18, YELLOW);

    for (int i = 0; i < count; ++i)
    {
        const char *line = TextFormat("%d. %-10s %3d km/s", i + 1, names[i], speeds[i]);
        DrawText(line, start_x, start_y + 30 + i * 25, 16, WHITE);
    }
}