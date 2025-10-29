#include "TestBenchHeat.h"
#include <limits>
#include <cmath>

TestBenchHeat::TestBenchHeat(const Engine &eng, double T_over, double dt_init, double tolerance, int maxr)
    : engine(eng), T_overheat(T_over), dt0(dt_init), tol(tolerance), max_refine(maxr) {}

double TestBenchHeat::run_with_dt(double dt, double max_time)
{
    engine.reset(engine.T_env);
    double t = 0.0;
    if (engine.T >= T_overheat)
        return 0.0;

    while (t < max_time)
    {
        auto [ob, on, Tnext, Mnext] = engine.step(dt);
        t += dt;
        if (Tnext >= T_overheat)
            return t;
    }
    return std::numeric_limits<double>::infinity();
}

HeatResult TestBenchHeat::run_with_refinement()
{
    double dt = dt0;
    double prev = run_with_dt(dt);
    bool converged = false;
    int iter = 0;

    for (iter = 0; iter < max_refine; ++iter)
    {
        double dt2 = dt / 2.0;
        double next = run_with_dt(dt2);
        double diff = fabs(next - prev);
        prev = next;
        dt = dt2;
        if (diff <= tol)
        {
            converged = true;
            break;
        }
    }
    return {prev, converged, iter + 1};
}
