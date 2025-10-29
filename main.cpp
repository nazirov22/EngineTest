#include <iostream>
#include <iomanip>
#include "Engine.h"
#include "TestBenchHeat.h"
#include "TestBenchMaxPower.h"

using namespace std;

int main()
{
    double ambient;
    cout << "Введите температуру окружающей среды (C): ";
    cin >> ambient;

    // Исходные данные
    Engine eng;
    eng.I = 10;
    eng.torqueCurve.V = {0, 75, 150, 200, 250, 300};
    eng.torqueCurve.M = {20, 75, 100, 105, 75, 0};
    eng.HM = 0.01;
    eng.HV = 0.0001;
    eng.Ccool = 0.1;
    eng.reset(ambient);

    double T_overheat = 110;
    double DEFAULT_DT = 0.01;
    double TOL_TIME = 1e-3;
    double TOL_POWER = 1e-3;
    int MAX_REFINE = 8;

    TestBenchHeat testHeat(eng, T_overheat, DEFAULT_DT, TOL_TIME, MAX_REFINE);
    auto heat = testHeat.run_with_refinement();
    cout << "Время до перегрева: " << fixed << setprecision(4)
         << heat.time_to_overheat << " сек\n";

    TestBenchMaxPower testPower(eng, DEFAULT_DT, TOL_POWER, MAX_REFINE);
    auto power = testPower.run_with_refinement();
    cout << "Максимальная мощность: " << power.max_power_kW << " кВт\n";
    cout << "Скорость при ней: " << power.omega_at_max << " рад/с\n";

    return 0;
}
