#pragma once
#include "Engine.h"

struct PowerResult
{
    double max_power_kW;
    double omega_at_max;
    bool converged;
    int refinements;
};

class TestBenchMaxPower
{
private:
    Engine engine;
    double dt0;
    double tol;
    int max_refine;

public:
    TestBenchMaxPower(const Engine &eng, double dt_init, double tolerance, int maxr);
    std::pair<double, double> run_with_dt(double dt, double max_time = 1e6);
    PowerResult run_with_refinement();
};
