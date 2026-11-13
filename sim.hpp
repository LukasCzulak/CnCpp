#pragma once
#include <vector>
#include <cmath>

#define TRAIL_LEN 400

struct Vec2
{
    double x, y;

    Vec2(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    Vec2 operator+(const Vec2 &other) const { return Vec2(x + other.x, y + other.y); }
    Vec2 operator-(const Vec2 &other) const { return Vec2(x - other.x, y - other.y); }
    Vec2 operator*(double scalar) const { return Vec2(x * scalar, y * scalar); }

    void operator+=(const Vec2 &other)
    {
        x += other.x;
        y += other.y;
    }

    double length() const { return std::sqrt(x * x + y * y); }
};

class Body
{
public:
    char name[16];
    Vec2 pos;         // in m
    Vec2 vel;         // in m/s
    double mass;      // in kg
    double radius_px; // visual in pixels
    int color_id;

    std::vector<Vec2> trail;

    Body(const char *raw_name, double dist_m, double angle_rad, double speed_ms, double mass_kg, double radius_px, int color_id);
    void record_trail();
};

class SolarSystem
{
private:
    std::vector<Body> bodies;
    double G = 6.67430e-11; // gravitational constant G in m^3 * kg^-1 * s^-2

public:
    void add_body(const Body &b);

    void step_physics(double dt, int substeps);
    void render();
};