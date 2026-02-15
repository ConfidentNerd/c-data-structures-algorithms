# C Data Structures and Algorithms

A comprehensive repository containing C implementations of various fundamental data structures and algorithms. This project was developed during the intensive Infinity Labs R&D training program to master memory management, algorithmic efficiency, and standard C build systems.

## Table of Contents

- [Directory Structure](#directory-structure)
- [Implemented Data Structures](#implemented-data-structures)
- [Implemented Algorithms](#implemented-algorithms)
- [Build Instructions](#build-instructions)
- [Usage](#usage)
- [Testing](#testing)
- [License](#license)
- [Author](#author)

## Directory Structure

The repository is organized into two main sections: `algorithms` and `data-structures`. Each section follows a consistent structure:

- **`inc/`**: Header files defining the API for each module.
- **`src/`**: Source files containing the implementation logic.
- **`test/`**: Unit tests to verify the correctness of the implementations.
- **`Makefile`**: Build script for compiling dynamic libraries and tests.

```text
.
├── algorithms/         # Algorithm implementations
│   ├── inc/
│   ├── src/
│   └── test/
├── data-structures/    # Data structure implementations
│   ├── inc/
│   ├── src/
│   └── test/
└── LICENSE
```

## Implemented Data Structures

The `data-structures/` directory contains efficient implementations of the following:

- **AVL Tree** (`avl.h`): A self-balancing binary search tree where the difference between heights of left and right subtrees cannot be more than one.
- **Bit Array** (`bitarr.h`): A space-efficient data structure that stores a collection of bits, useful for compact storage of boolean values.
- **Binary Search Tree (BST)** (`bst.h`): A node-based binary tree data structure where each node has a key greater than all keys in its left subtree and less than those in its right subtree.
- **Calculator** (`calculator.h`): A mathematical expression calculator supporting basic arithmetic and power operations, implemented using the Shunting-yard algorithm.
- **Circular Buffer** (`cbuff.h`): A fixed-size buffer that acts as if it were connected end-to-end, efficient for buffering data streams.
- **Doubly Linked List** (`dlist.h`): A linked list where each node contains pointers to both the next and previous nodes, allowing for bidirectional traversal.
- **Dynamic Vector** (`dvector.h`): A resizeable array implementation that automatically grows or shrinks its capacity based on the number of elements.
- **Hash Table** (`hash.h`): A data structure that maps keys to values for highly efficient lookup, insertion, and deletion operations.
- **Heap** (`heap.h`): A specialized tree-based data structure that satisfies the heap property (min-heap), commonly used for priority queues.
- **Priority Queue** (`pqueue.h`, `pqueue_heap.h`): An abstract data type where each element has a priority; elements with higher priority are served before lower ones. Implementations include both Sorted List and Heap variants.
- **Queue** (`queue.h`): A linear structure following the First In, First Out (FIFO) principle.
- **Scheduler** (`scheduler.h`, `scheduler_heap.h`): A task scheduling system that executes tasks at specified intervals, utilizing a priority queue (Heap or List based) to manage execution order.
- **Singly Linked List** (`slist.h`): A linear collection of elements where each element points to the next one.
- **Sorted Linked List** (`srtlist.h`): A linked list that maintains its elements in a sorted order during insertion.
- **Stack** (`stack.h`): A linear data structure following the Last In, First Out (LIFO) principle.
- **Task** (`task.h`): A structure representing a unit of work to be executed by the Scheduler, including action and cleanup functions.
- **UID** (`uid.h`): A utility for generating globally unique identifiers based on a counter, process ID, and timestamp.

## Implemented Algorithms

The `algorithms/` directory features implementations of classic algorithms:

- **Knight's Tour** (`knight_tour.h`): A backtracking algorithm that finds a sequence of moves of a knight on a chessboard such that the knight visits every square exactly once.
- **Recursion** (`recursion.h`): A collection of recursive solutions for problems like Fibonacci sequence generation, string manipulation, and stack sorting.
- **Sorting & Searching** (`sort.h`): A comprehensive suite of sorting and searching algorithms including:
  - Bubble Sort
  - Selection Sort
  - Insertion Sort
  - Counting Sort
  - Radix Sort
  - Merge Sort
  - Quick Sort
  - Binary Search (Iterative & Recursive)

## Build Instructions

Each subdirectory (`algorithms` and `data-structures`) contains its own dynamic `Makefile`. You can build specific targets or the entire project.

### Prerequisites
- GCC (GNU Compiler Collection)
- Make

### Common Make Targets
- `make all`: Builds the release library and runs cleanup.
- `make debug`: Builds the target executable with debug symbols.
- `make release`: Builds the target executable with optimization (`-O3`) and without debug symbols.
- `make clean`: Removes object files and shared libraries.
- `make cleanall`: Removes all generated files including executables.

### Building a Specific Module
To build a specific data structure or algorithm, use the `TARGET` variable.

**Example: Building the Stack implementation**
```bash
cd data-structures
make TARGET=stack
```
This will automatically map dependencies, compile `stack.c` and `stack_test.c`, create a shared library `libstack.so`, and generate a test executable `stack.out`.

## Usage

To use these data structures in your own C projects, include the relevant header file and link against the compiled shared library (`.so`). 

1. **Include the header:**
   ```c
   #include "data-structures/inc/stack.h"
   ```

2. **Compile and Link:**
   Ensure you add the include path and link the generated library. The `rpath` flag ensures the executable knows where to find the library at runtime.
   ```bash
   gcc my_program.c -I./data-structures/inc -L./data-structures -lstack -Wl,-rpath=./data-structures -o my_program
   ```

## Testing

Each module comes with a corresponding test file (e.g., `stack_test.c`). When you run `make TARGET=name`, the build system automatically compiles the test file into an executable (e.g., `stack.out`).

To run the tests:
1. Build the module: `make TARGET=stack`
2. Run the executable from within the same directory: 
   ```bash
   ./stack.out
   ```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Author

**Uri Naor**