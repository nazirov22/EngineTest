#include "Engine.h"
#include <cmath>

Engine::Engine() : I(1.0), HM(0.0), HV(0.0), Ccool(0.0), T_env(20.0), omega(0.0), T(20.0) {}

void Engine::reset(double ambient)
{
    T_env = ambient;
    omega = 0.0;
    T = T_env;
}

std::tuple<double, double, double, double> Engine::step(double dt)
{
    double Mcur = torqueCurve.getM(omega);
    double a = Mcur / I;
    double omega_next = omega + a * dt;

    double VH = Mcur * HM + omega * omega * HV;
    double VC = Ccool * (T_env - T);
    double T_next = T + (VH + VC) * dt;

    double omega_before = omega;
    omega = omega_next;
    T = T_next;

    double Mnext = torqueCurve.getM(omega);
    return {omega_before, omega_next, T_next, Mnext};
}

double Engine::currentPower_kW() const
{
    double Mcur = torqueCurve.getM(omega);
    return (Mcur * omega) / 1000.0;
}
