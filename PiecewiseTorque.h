#pragma once
#include <vector>

class PiecewiseTorque
{
public:
    std::vector<double> V; // рад/с
    std::vector<double> M; // Н·м

    double getM(double omega) const;
};
