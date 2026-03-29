## Project Description (Assignment)

This project was developed as part of our “C++ for Finance” course, in a team of 5 students, and received a final grade of **15/20**.

The objective was to design and implement a complete option pricing framework in C++, combining financial theory, numerical methods, and object-oriented programming.

The assignment was structured in several parts:

### 1. Black–Scholes Model
- Implementation of an abstract Option class and derived European vanilla options (Call/Put)
- Implementation of the Black–Scholes pricer for pricing and delta computation
- Use of analytical formulas under standard assumptions (lognormal dynamics, no arbitrage)

### 2. Binomial Model (CRR)
- Implementation of a generic BinaryTree<T> structure
- Construction of a Cox–Ross–Rubinstein (CRR) binomial tree
- Pricing of European options using backward induction
- Implementation of a closed-form binomial formula

### 3. Path-Dependent Options & Monte Carlo
- Extension of the framework to path-dependent options
- Implementation of Asian options using time discretization
- Simulation of Black–Scholes sample paths
- Monte Carlo pricing with:
  - incremental estimation,
  - confidence interval computation,
  - no path storage constraint

### 4. American Options & Extensions
- Extension of the CRR model to handle American options
- Computation of optimal early exercise strategies
- Storage of exercise decisions using a binary tree
- Approximation of Black–Scholes via binomial convergence

## Supplementary Material

This repository includes a supplementary PDF document detailing:
- Monte Carlo optimization techniques,
- OpenMP parallelization,
- performance considerations.

This document provides additional insights into the implementation choices and optimization strategies.
