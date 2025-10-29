#include "PiecewiseTorque.h"
#include <algorithm>

double PiecewiseTorque::getM(double omega) const
{
    if (V.empty() || M.empty() || V.size() != M.size())
        return 0.0;
    if (omega <= V.front())
        return M.front();
    if (omega >= V.back())
        return M.back();

    auto it = std::upper_bound(V.begin(), V.end(), omega);
    size_t idx = it - V.begin();
    double V1 = V[idx - 1], V2 = V[idx];
    double M1 = M[idx - 1], M2 = M[idx];
    double t = (omega - V1) / (V2 - V1);
    return M1 + t * (M2 - M1);
}
