# Fault-Tolerant Resource Manager

## Overview
This project implements a Fault-Tolerant Resource Manager in C++ to handle the allocation and deallocation of resources (e.g., workers, equipment) for large projects. The manager ensures proper resource management using advanced design patterns and modern C++ features.

## Features
- **RAII and Smart Pointers**: Ensures proper allocation and deallocation of resources using `std::unique_ptr`.
- **Exception Handling**: Manages unexpected resource shortages or allocation errors.
- **State Pattern**: Tracks the current status of resources (Idle, In Use, Under Maintenance).
- **Streams**: Logs all resource transactions and errors for auditing.
- **Design Patterns**: Utilizes Singleton, Strategy, and Factory patterns to handle complex allocation scenarios.

## Design Patterns
1. **Singleton Pattern**: Ensures only one instance of `ResourceManager` exists.
2. **Strategy Pattern**: Allows different allocation strategies to be set dynamically.
3. **Factory Pattern**: Simplifies resource creation using `std::make_unique`.
