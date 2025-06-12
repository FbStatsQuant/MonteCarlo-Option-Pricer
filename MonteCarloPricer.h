#ifndef MONTE_CARLO_PRICER_H
#define MONTE_CARLO_PRICER_H

#include <string>

enum OptionType { CALL, PUT };

double monteCarloPrice(
    OptionType type,
    double S0,
    double K,
    double r,
    double sigma,
    double T,
    int numPaths,
    double* stdErr = nullptr  // Optional output
);

void exportTerminalPaths(
    double S0,
    double r,
    double sigma,
    double T,
    int numPaths,
    const std::string& filename
);

double estimateDelta(
    OptionType type,
    double S0,
    double K,
    double r,
    double sigma,
    double T,
    int numPaths,
    double epsilon = 1e-2
);

double estimateVega(
    OptionType type,
    double S0,
    double K,
    double r,
    double sigma,
    double T,
    int numPaths,
    double epsilon = 1e-2
);

double estimateTheta(
    OptionType type,
    double S0,
    double K,
    double r,
    double sigma,
    double T,
    int numPaths,
    double epsilon = 1e-3
);



#endif
