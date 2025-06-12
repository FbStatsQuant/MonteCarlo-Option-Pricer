#include <iostream>
#include <iomanip>
#include "MonteCarloPricer.h"

int main() {
    double S0 = 100.0, K = 100.0, r = 0.05, sigma = 0.2, T = 1.0;
    int numPaths = 100000;

    double seCall, sePut;

    double callPrice = monteCarloPrice(CALL, S0, K, r, sigma, T, numPaths, &seCall);
    double putPrice  = monteCarloPrice(PUT,  S0, K, r, sigma, T, numPaths, &sePut);

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Call Price: " << callPrice << "  +/- " << seCall << std::endl;
    std::cout << "Put Price : " << putPrice  << "  +/- " << sePut << std::endl;

    exportTerminalPaths(S0, r, sigma, T, 10000, "paths.csv");
    std::cout << "\nExported 10,000 terminal prices to paths.csv\n";

    std::cout << "\nGreeks (Call):\n";
    std::cout << "Delta: " << estimateDelta(CALL, S0, K, r, sigma, T, numPaths) << std::endl;
    std::cout << "Vega : " << estimateVega(CALL, S0, K, r, sigma, T, numPaths) / 100.0 << std::endl;
    std::cout << "Theta: " << estimateTheta(CALL, S0, K, r, sigma, T, numPaths) << std::endl;


    return 0;
}

// g++ -std=c++20 -o mc_pricing main.cpp MonteCarloPricer.cpp