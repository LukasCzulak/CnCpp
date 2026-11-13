#include "sim.hpp"
#include "renderer.h"
#include "physics.h"

int main(int argc, char *argv[])
{
    gui_init();

    SolarSystem sim;

    // Body(name, distance [m], angle [rad], speed [m/s], mass [kg], radius [px], color_id)
    sim.add_body(Body("sun", 0.0, 0.0, 0.0, 1.989e30, 20.0, 0));
    sim.add_body(Body("mercury", 5.791e10, 0.0, 47360.0, 3.301e23, 5.0, 2));
    sim.add_body(Body("venus", 1.082e11, 2.1, 35020.0, 4.867e24, 8.0, 4));
    sim.add_body(Body("earth", 1.496e11, 4.2, 29780.0, 5.972e24, 9.0, 1));
    sim.add_body(Body("mars", 2.279e11, 1.0, 24070.0, 6.417e23, 7.0, 3));
    sim.add_body(Body("jupiter", 7.779e11, 0.0, 13100.0, 1.899e27, 15.0, 6));
    sim.add_body(Body("saturn", 1.434e12, 2.8, 9690.0, 5.683e26, 13.0, 7));
    sim.add_body(Body("uranus", 2.872e12, 0.7, 6810.0, 8.681e25, 11.0, 8));
    sim.add_body(Body("neptune", 4.495e12, 4.6, 5430.0, 1.024e26, 11.0, 9));

    sim.add_body(Body("comet", 6.000e10, 3.14, 60366.0, 2.200e14, 4.0, 5));

    // 3600.0 = 1 hour per frame
    double dt = 3600.0 * 3.0;

    while (!gui_should_close())
    {
        sim.step_physics(dt, 60);

        gui_begin_frame();
        sim.render();
        gui_end_frame();
    }

    return 0;
}