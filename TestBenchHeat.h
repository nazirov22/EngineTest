#pragma once
#include "Engine.h"

struct HeatResult
{
    double time_to_overheat;
    bool converged;
    int refinements;
};

class TestBenchHeat
{
private:
    Engine engine;
    double T_overheat;
    double dt0;
    double tol;
    int max_refine;

public:
    TestBenchHeat(const Engine &eng, double T_over, double dt_init, double tolerance, int maxr);
    double run_with_dt(double dt, double max_time = 1e6);
    HeatResult run_with_refinement();
};
