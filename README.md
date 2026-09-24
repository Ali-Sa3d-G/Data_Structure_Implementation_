# Data Structures & Algorithms Learning Repository

A C++ repository created as a learning and revision reference for **Data Structures & Algorithms**.

This repository is designed to help students not only review topics they have already studied, but also understand topics they are still learning.

The main goal is simple:

> **Make DSA implementations easy to read, easy to understand, and easy to revise.**

The code is written to be **learned from**, not just compiled and executed.

---

## What Makes This Repository Different?

Most DSA repositories focus mainly on providing working implementations.

This repository focuses on the **learning experience** around those implementations.

Each topic is organized to help the student understand:

* What the data structure or algorithm does
* How it works
* Why each important step is needed
* How the structure changes during an operation
* Time and space complexity
* Edge cases and important implementation details

The explanations are kept simple and focused on the ideas students actually need.

---

## Learning Style

Each implementation follows a consistent learning pattern:

### 1. Concept Summary

A short explanation of the main idea before the code.

### 2. Visualization

Simple diagrams are used whenever they make the algorithm or data structure easier to understand.

For example:

```text
head
 |
 v
[10] <-> [20] <-> [30]
                    ^
                    |
                   tail
```

### 3. Explained Implementation

The code itself contains comments explaining the important logic and the reason behind each step.

### 4. Complexity

Time and space complexity are included so the student can connect the implementation with the theoretical analysis.

### 5. Demonstration

Each file contains a simple example showing how the implementation is used.

---

## Topics Covered

### Sorting Algorithms

* Bubble Sort
* Selection Sort
* Insertion Sort
* Merge Sort
* Quick Sort
* Shell Sort
* Heap Sort
* Bucket Sort
* Counting Sort
* Radix Sort

### Searching Algorithms

* Linear Search
* Binary Search

### Linear Data Structures

* Array ADT
* Singly Linked List
* Doubly Linked List
* Circular Doubly Linked List
* Stack
* Queue

### Trees

* Binary Search Tree
* AVL Tree

### Graphs

* Graph using Adjacency List
* Breadth First Search (BFS)
* Depth First Search (DFS)
* Dijkstra's Shortest Path Algorithm

---

## Example of the Learning Approach

Instead of only writing:

```cpp
void insertAtBeginning(T data)
{
    newNode->next = head;
    head = newNode;
}
```

the repository explains what is happening:

```text
Before:

head -> [10] -> [20] -> [30]

Insert 5

Step 1:
Create [5]

Step 2:
Make 5 point to the old head

    [5] -> [10] -> [20] -> [30]

Step 3:
Move head to the new node

head -> [5] -> [10] -> [20] -> [30]
```

This makes the implementation easier to follow, especially when learning pointer-based data structures.

---

## Repository Structure

The repository is organized by DSA topic so students can quickly find the concept they need.

```text
DSA/
│
├── Sorting/
│   ├── Bubble Sort
│   ├── Selection Sort
│   ├── Insertion Sort
│   ├── Merge Sort
│   ├── Quick Sort
│   ├── Shell Sort
│   ├── Heap Sort
│   ├── Bucket Sort
│   ├── Counting Sort
│   └── Radix Sort
│
├── Searching/
│   ├── Linear Search
│   └── Binary Search
│
├── Linked Lists/
│   ├── Singly Linked List
│   ├── Doubly Linked List
│   └── Circular Doubly Linked List
│
├── Stack/
│
├── Queue/
│
├── Trees/
│   ├── Binary Search Tree
│   └── AVL Tree
│
└── Graphs/
    ├── BFS
    ├── DFS
    └── Dijkstra
```

---

## How to Use This Repository

You can use the repository in different ways depending on what you need.

### Reviewing a Topic

Read the concept summary first, then go through the implementation and comments.

### Learning a Topic

Start with the visualization and the explanation of the main operation, then trace the code step by step.

### Preparing for Exams

Use the summaries and complexity information to quickly review the main ideas and implementation patterns.

### Practicing

Run the examples, change the input values, and try to predict the output before executing the program.

---

## Complexity

One of the main goals of the repository is to connect the implementation with its algorithmic complexity.

For each major algorithm or data structure, the relevant time and space complexity are included directly in the code.

This helps students understand not only **how to implement an algorithm**, but also **how efficient the implementation is**.

---

## Learning Philosophy

The repository follows a few simple principles:

* **Understand before memorizing**
* **Keep implementations simple**
* **Explain important logic inside the code**
* **Use visualization when it helps**
* **Connect code with complexity**
* **Focus on the student's learning experience**

The goal is not to hide the algorithm behind complicated abstractions.

The goal is to make the algorithm easier to see.

---

## Technologies

* **C++**
* Standard Template Library (STL)
* Data Structures
* Algorithms
* Algorithmic Complexity
* Recursion
* Pointers
* Dynamic Memory

---

## Who Is This For?

This repository is mainly intended for:

* University students studying DSA
* Students revising before exams
* Beginners who want to understand implementations
* Anyone looking for simple C++ DSA references

---

## Contribution

This repository is primarily a learning resource.

Suggestions, corrections, and improvements that make the explanations or implementations clearer are welcome.

---

## Goal

The long-term goal is to make this repository a reliable **DSA learning and revision reference** that students can return to whenever they forget a concept, need to review an implementation, or want a simple starting point for learning a topic.
