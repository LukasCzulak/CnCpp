#include "sim.hpp"
#include "physics.h"
#include "renderer.h"
#include <cstring>

Body::Body(const char *raw_name, double dist_m, double angle_rad, double speed_ms, double mass_kg, double radius_px, int color_id)
    : mass(mass_kg), radius_px(radius_px), color_id(color_id)
{
    std::strncpy(name, raw_name, 15);
    name[15] = '\0';
    to_upper(name);

    double x, y;
    polar_to_cartesian(dist_m, angle_rad, &x, &y);
    pos = Vec2(x, y);

    double vel_x, vel_y;
    polar_to_cartesian(speed_ms, angle_rad + PI / 2.0, &vel_x, &vel_y);
    vel = Vec2(vel_x, vel_y);
}

void Body::record_trail()
{
    trail.push_back(pos);
    if (trail.size() > TRAIL_LEN)
    {
        trail.erase(trail.begin());
    }
}

void SolarSystem::add_body(const Body &b)
{
    bodies.push_back(b);
}

void SolarSystem::step_physics(double dt, int substeps)
{
    double sub_dt = dt / substeps;
    int n = bodies.size();

    for (int step = 0; step < substeps; ++step)
    {
        std::vector<Vec2> acc(n, Vec2(0.0, 0.0));

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i == j)
                    continue;

                Vec2 diff = bodies[j].pos - bodies[i].pos;
                double dist = diff.length();

                double acceleration = (G * bodies[j].mass) / (dist * dist * dist);
                acc[i] += diff * acceleration;
            }
        }

        for (int i = 0; i < n; ++i)
        {
            bodies[i].vel += acc[i] * sub_dt;
            bodies[i].pos += bodies[i].vel * sub_dt;
        }
    }

    for (auto &b : bodies)
        b.record_trail();
}

void SolarSystem::render()
{
    for (const auto &b : bodies)
    {
        for (size_t i = 1; i < b.trail.size(); ++i)
        {
            gui_draw_trail(b.trail[i - 1].x, b.trail[i - 1].y, b.trail[i].x, b.trail[i].y, b.color_id);
        }
    }

    char names[16][16];
    int speeds[16];
    int count = bodies.size();

    for (int i = 0; i < count; ++i)
    {
        gui_draw_planet(bodies[i].pos.x, bodies[i].pos.y, bodies[i].radius_px, bodies[i].name, bodies[i].color_id);
        std::strncpy(names[i], bodies[i].name, 16);
        speeds[i] = (int)(bodies[i].vel.length() / 1000.0); // m/s -> km/s
    }

    sort_leaderboard(names, speeds, count);
    gui_draw_leaderboard(names, speeds, count);
}
