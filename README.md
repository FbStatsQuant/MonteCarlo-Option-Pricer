# Monte Carlo Option Pricer in C++

This project implements a **Monte Carlo simulation engine** in C++ to price **European call and put options** under the Black-Scholes model. It includes numerical estimation of **Delta**, **Vega**, and **Theta**, and exports terminal prices for visualization.

---

## 📌 Features

- Monte Carlo pricing for European options
- Standard error estimation
- Finite-difference estimation of Greeks:
  - Delta
  - Vega
  - Theta
- Exports terminal simulated prices to CSV (`paths.csv`)
- Deterministic random number generation (seeded)

---

## 📁 Files

| File                  | Description                                     |
|-----------------------|-------------------------------------------------|
| `main.cpp`            | Driver script – prints prices and Greeks        |
| `MonteCarloPricer.h`  | Function declarations and type definitions      |
| `MonteCarloPricer.cpp`| Core Monte Carlo and Greek estimation logic     |
| `paths.csv`           | Exported terminal prices from simulated paths   |
| `mc_pricing.exe`      | Optional precompiled executable (Windows)       |

---

## 📈 Sample Output

