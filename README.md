# Modern C++ Search Tree Implementations

This repository provides a implementation of data structures, focusing on balancing algorithms and memory management. 

## Architecture

The project utilizes a class hierarchy within the `adsc` namespace to separate interface from implementation:

* **`adsc::BinaryTree`**: Standard BST implementation.
* **`adsc::AVLTree`**: Self-balancing BST using height-based rotations.

All structures are header-only, template-based, and support custom comparators through a functional interface.

## Performance Benchmark

The following measurements compare the standard `BinaryTree` against the `AVLTree` and `std::multiset`.

### Scenario 1: Randomized Data (N = 100,000)
| Structure | Insert (s) | RemoveMin (s) | Final Height |
| :--- | :--- | :--- | :--- |
| **BinaryTree** | 0.208359 | 0.092761 | 39 |
| **AVLTree** | 0.270049 | 0.201049 | 20 |
| **std::multiset** | 0.042717 | 0.006024 | N/A |

### Scenario 2: Sorted Data (N = 15,000)
| Structure | Insert (s) | RemoveMin (s) | Final Height |
| :--- | :--- | :--- | :--- |
| **BinaryTree** | 8.484736 | 0.002015 | 15,000 |
| **AVLTree** | **0.033910** | **0.021793** | **14** |
| **std::multiset** | 0.004351 | 0.000825 | N/A |

## Technical Highlights

* **Memory Safety & Smart Pointers**: Exclusive use of `std::unique_ptr` for RAII-compliant memory management. This ensures deterministic destruction and prevents memory leaks, with a conscious design trade-off between absolute performance and memory safety.
* **Move Semantics**: Optimized data handling using `std::move` to support non-copyable types and efficient data retrieval.
* **Unit Tested**: Using **GoogleTest** to ensure stability and cover edge cases.


## Build Requirements
* C++17 compliant compiler
* CMake 3.14+

### Building the project
```bash
mkdir build && cd build
cmake ..
make
./benchmark
```