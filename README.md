# 🏨 HOTELIX — Hotel Operations System

> A console-based Hotel Management System built in C, developed as a First Year Programming Project.  
> Manages rooms, guest check-ins, check-outs, billing, and revenue reporting — all powered by dynamic memory allocation.

---

## 📋 Table of Contents

- [About the Project](#about-the-project)
- [Features](#features)
- [Tech Stack](#tech-stack)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [How to Use](#how-to-use)
- [Login Credentials](#login-credentials)
- [Concepts Used](#concepts-used)
- [Bug Fixes Applied](#bug-fixes-applied)
- [Author](#author)

---

## 📖 About the Project

**HOTELIX** is a fully functional Hotel Operations System written in the **C programming language**.  
It simulates a real-world hotel front desk — staff can log in securely, manage room inventory, check guests in and out, generate billing receipts, and view revenue summaries.

The project was built to demonstrate core **first-year C programming concepts** such as:
- Structures (`struct`)
- Dynamic memory (`malloc`, `calloc`, `realloc`, `free`)
- Functions and modular design
- Input validation using `scanf`
- Pointers and arrays

---

## ✨ Features

| Feature | Description |
|---|---|
| 🔐 **Secure Login** | 3-attempt lockout system with username & password authentication |
| 🛏️ **Room Management** | View all rooms, add new rooms with dynamic realloc |
| ✅ **Guest Check-In** | Register guests with name (supports spaces), phone, room & duration |
| 🧾 **Guest Check-Out** | Generates a formatted bill receipt on checkout |
| 📋 **Guest Directory** | View all active and historical guest records |
| 📊 **Revenue Report** | Summary of occupied rooms, realized revenue & pending receivables |
| 💾 **Dynamic Memory** | Arrays auto-expand using `realloc` when capacity is full |
| 🧹 **Memory Cleanup** | All heap memory safely released on exit |

---

## 🛠️ Tech Stack

| Technology | Detail |
|---|---|
| **Language** | C (Standard: C99) |
| **Compiler** | GCC (GNU Compiler Collection) |
| **Memory** | `calloc`, `realloc`, `free` (heap-based dynamic arrays) |
| **I/O** | Standard `stdio.h` with input validation |
| **Platform** | Windows / Linux / macOS (any system with GCC) |

---

## 📁 Project Structure

```
hotelix/
│
├── hotelix_final.c       ← Main source code (single file)
└── README.md             ← This file
```

> The entire project is contained in a **single `.c` file** — no external libraries or dependencies required.

---

## 🚀 Getting Started

### Prerequisites

Make sure you have **GCC** installed on your system.

**Check if GCC is installed:**
```bash
gcc --version
```

**Install GCC (if not installed):**
- **Windows** → Install [MinGW](https://www.mingw-w64.org/) or use Dev-C++
- **Linux** → `sudo apt install gcc`
- **macOS** → `xcode-select --install`

---

### Compilation

Open a terminal in the project folder and run:

```bash
gcc -o hotelix.exe hotelix_final.c
```

For strict warning checks (recommended):
```bash
gcc -Wall -Wextra -std=c99 -o hotelix.exe hotelix_final.c
```

---

### Run the Program

**Windows:**
```bash
hotelix.exe
```

**Linux / macOS:**
```bash
./hotelix
```

---

## 🖥️ How to Use

Once the program starts, you will see the **Login Screen**. After successful login, the main menu appears:

```
=====================================
     HOTELIX OPERATIONS SYSTEM
=====================================
1. View All Rooms
2. Add New Room
3. Guest Check-In
4. Guest Check-Out & Billing
5. View All Guest Records
6. Hotel Summary Report
0. Exit & Release Memory
-------------------------------------
Enter choice:
```

### Menu Options

| Option | Action |
|---|---|
| `1` | Display all rooms with type, rate, and availability status |
| `2` | Add a new room (room number, type, rate per night) |
| `3` | Check in a guest (room, nights, name, phone number) |
| `4` | Check out a guest and generate a printed bill receipt |
| `5` | View all guest records (active stays + checkout history) |
| `6` | View hotel summary — rooms occupied, revenue collected, pending bills |
| `0` | Exit the system and free all memory |

---

### Sample Check-In Flow

```
Enter Room Number for Check-In: 101
Enter Duration of Stay (Nights): 3
Enter Guest Name: Rajan Garg
Enter Phone Number: 9876543210

[+] Check-In successful! Guest ID: 1001 | Total: INR 3000.00
```

### Sample Bill Receipt

```
===================================
        OFFICIAL HOTEL RECEIPT
===================================
Guest ID     : 1001
Guest Name   : Rajan Garg
Phone        : 9876543210
Room Number  : 101
Nights Stayed: 3
-----------------------------------
TOTAL AMOUNT : INR 3000.00
===================================
```

---

## 🔐 Login Credentials

| Field | Value |
|---|---|
| **Username** | `admin` |
| **Password** | `1234` |

> ⚠️ After **3 failed attempts**, the system locks down automatically and exits.

---

## 🧠 Concepts Used

This project covers the following **first-year C programming concepts**:

- **Structures (`struct`)** — `Room` and `Guest` data models
- **Dynamic Memory Allocation** — `calloc`, `realloc`, `free`
- **Pointers** — pointer-based dynamic arrays (`struct Room *rooms`)
- **Functions** — modular design with separate functions for each feature
- **Loops** — `while` loop for menu, `for` loops for searching arrays
- **Conditional Statements** — `if-else` and `switch-case`
- **String Handling** — `strcpy`, `strcmp` from `<string.h>`
- **Input Validation** — `scanf` return value checking, `clearBuffer()`
- **Input with Spaces** — `scanf(" %[^\n]")` format for full name input
- **Memory Safety** — `NULL` checks after every allocation, safe `realloc` pattern

---

## 👨‍💻 Author

**Project:** HOTELIX — Hotel Operations System   
**Language:** C (C99 Standard)  
**Status:** ✅ Complete & Bug-Free

---

> *"Simple code, real concepts, practical output."*
