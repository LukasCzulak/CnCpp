#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    void gui_init();
    int gui_should_close();
    void gui_begin_frame();
    void gui_draw_trail(double x1, double y1, double x2, double y2, int color_id);
    void gui_draw_planet(double x, double y, double radius, const char *name, int color_id);
    void gui_draw_leaderboard(char names[][16], int *speeds, int count);
    void gui_end_frame();

#ifdef __cplusplus
}
#endif