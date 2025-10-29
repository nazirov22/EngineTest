#pragma once
#include "PiecewiseTorque.h"

class Engine
{
public:
    double I;
    PiecewiseTorque torqueCurve;
    double HM;
    double HV;
    double Ccool;
    double T_env;

    double omega;
    double T;

    Engine();
    void reset(double ambient);
    std::tuple<double, double, double, double> step(double dt);
    double currentPower_kW() const;
};
