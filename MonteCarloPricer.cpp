#include "MonteCarloPricer.h"
#include <random>
#include <fstream>
#include <cmath>
#include <vector>

double monteCarloPrice(OptionType type, double S0, double K, double r, double sigma, double T, int numPaths, double* stdErr) {
    std::mt19937_64 rng(42);
    std::normal_distribution<double> dist(0.0, 1.0);

    double sumPayoff = 0.0;
    double sumPayoffSq = 0.0;

    for (int i = 0; i < numPaths; ++i) {
        double Z = dist(rng);
        double ST = S0 * std::exp((r - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * Z);

        double payoff = 0.0;
        if (type == CALL)
            payoff = std::max(ST - K, 0.0);
        else
            payoff = std::max(K - ST, 0.0);

        sumPayoff += payoff;
        sumPayoffSq += payoff * payoff;
    }

    double mean = sumPayoff / numPaths;
    double price = std::exp(-r * T) * mean;

    if (stdErr) {
        double variance = (sumPayoffSq / numPaths - mean * mean);
        *stdErr = std::exp(-2 * r * T) * std::sqrt(variance / numPaths);
    }

    return price;
}

void exportTerminalPaths(double S0, double r, double sigma, double T, int numPaths, const std::string& filename) {
    std::mt19937_64 rng(42);
    std::normal_distribution<double> dist(0.0, 1.0);

    std::ofstream file(filename);
    file << "path_id,ST\n";

    for (int i = 0; i < numPaths; ++i) {
        double Z = dist(rng);
        double ST = S0 * std::exp((r - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * Z);
        file << i + 1 << "," << ST << "\n";
    }

    file.close();
}
double estimateDelta(OptionType type, double S0, double K, double r, double sigma, double T, int numPaths, double epsilon) {
    double up   = monteCarloPrice(type, S0 + epsilon, K, r, sigma, T, numPaths);
    double down = monteCarloPrice(type, S0 - epsilon, K, r, sigma, T, numPaths);
    return (up - down) / (2.0 * epsilon);
}

double estimateVega(OptionType type, double S0, double K, double r, double sigma, double T, int numPaths, double epsilon) {
    double up   = monteCarloPrice(type, S0, K, r, sigma + epsilon, T, numPaths);
    double down = monteCarloPrice(type, S0, K, r, sigma - epsilon, T, numPaths);
    return (up - down) / (2.0 * epsilon);
}

double estimateTheta(OptionType type, double S0, double K, double r, double sigma, double T, int numPaths, double epsilon) {
    double later = monteCarloPrice(type, S0, K, r, sigma, T + epsilon, numPaths);
    double now   = monteCarloPrice(type, S0, K, r, sigma, T, numPaths);
    return (now - later) / epsilon;
}

