# Task 2: Smart E-Commerce System

This project is a Small Smart E-Commerce System using Object-Oriented 
Programming (OOP) in C++

## Features

- Admin product management: add, edit, delete, and view statistics
- Customer browsing, cart actions, checkout, and recommendations
- Recommendation system:
The recommendation system engine consists of:
    - Input: user interaction history (views and purchases)
    - Output: Top N recommended products.
The scoring mechanism is computed by:
𝑠𝑐𝑜𝑟𝑒 = 𝑣𝑖𝑒𝑤_𝑐𝑜𝑢𝑛𝑡 ∗ 0.2 + 𝑝𝑢𝑟𝑐ℎ𝑎𝑠𝑒_𝑐𝑜𝑢𝑛𝑡 ∗ 0.8 + 𝑐𝑎𝑡𝑒𝑔𝑜𝑟𝑦_𝑏𝑜𝑛𝑢s
- Persistent storage for products, orders, and user interaction history

## Build

Use a C++ compiler such as `g++`:

```bash
g++ main.cpp src/Admin.cpp src/Cart.cpp src/Order.cpp src/Product.cpp src/RecommendationEngine.cpp src/Utils.cpp -o main
```

## Run

```bash
./main
```

On Windows, run:

```bash
main.exe
```

## Data Files

The app reads and writes these files:

- `database/products.txt`
- `database/orders.txt`
- `database/interactions.txt`

If a file is missing, the program creates default product data on first run.
