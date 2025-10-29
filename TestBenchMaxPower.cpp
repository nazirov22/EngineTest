#include "TestBenchMaxPower.h"
#include <cmath>

TestBenchMaxPower::TestBenchMaxPower(const Engine &eng, double dt_init, double tolerance, int maxr)
    : engine(eng), dt0(dt_init), tol(tolerance), max_refine(maxr) {}

std::pair<double, double> TestBenchMaxPower::run_with_dt(double dt, double max_time)
{
    engine.reset(engine.T_env);
    double t = 0.0;
    double max_power = engine.currentPower_kW();
    double omega_at_max = engine.omega;

    while (t < max_time)
    {
        auto [omega_before, omega_after, Tnext, Mnext] = engine.step(dt);
        t += dt;

        double power = engine.currentPower_kW();
        if (power > max_power)
        {
            max_power = power;
            omega_at_max = engine.omega;
        }
        if (omega_after <= omega_before)
            break;
    }
    return {max_power, omega_at_max};
}

PowerResult TestBenchMaxPower::run_with_refinement()
{
    double dt = dt0;
    auto prev = run_with_dt(dt);
    bool converged = false;
    int iter = 0;

    for (iter = 0; iter < max_refine; ++iter)
    {
        double dt2 = dt / 2.0;
        auto next = run_with_dt(dt2);
        double diff = fabs(next.first - prev.first);
        prev = next;
        dt = dt2;
        if (diff <= tol)
        {
            converged = true;
            break;
        }
    }
    return {prev.first, prev.second, converged, iter + 1};
}
