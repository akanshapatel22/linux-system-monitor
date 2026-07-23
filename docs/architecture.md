# Linux System Monitor Architecture

## Overview

This document describes the architecture of the Linux System Monitor. The application reads system information directly from the Linux `/proc` virtual filesystem and displays real-time CPU, memory, and process statistics through a terminal-based interface.

The project is organized into independent monitoring modules for CPU, memory, and process information, making the design modular and easy to extend.

---

## System Architecture

```text
                    Linux Kernel
                          |
                  /proc Virtual Filesystem
                          |
        -----------------------------------------
        |                  |                    |
        |                  |                    |
   /proc/stat        /proc/meminfo      /proc/[pid]/stat
        |                  |                    |
        |                  |                    |
   CPU Monitor       Memory Monitor      Process Monitor
        |                  |                    |
        -----------------------------------------
                          |
                    main.cpp
                          |
                  ncurses Terminal UI
                          |
                       User Display
```

---

## Components

### 1. CPU Monitor

The CPU monitoring module reads CPU statistics from `/proc/stat`.

Responsibilities:

- Read CPU time counters
- Calculate CPU usage using consecutive samples
- Display CPU utilization statistics

---

### 2. Memory Monitor

The memory monitoring module reads system memory information from `/proc/meminfo`.

Responsibilities:

- Read total memory
- Read free memory
- Read buffer and cache information
- Calculate memory usage statistics

---

### 3. Process Monitor

The process monitoring module scans the `/proc` directory to identify running processes.

Responsibilities:

- Enumerate active processes
- Read process information from `/proc/[pid]/stat`
- Read process names from `/proc/[pid]/comm`
- Display process CPU time statistics

---

### 4. Main Application

The main application coordinates all monitoring modules.

Responsibilities:

- Initialize the terminal interface using ncurses
- Collect data from all monitoring modules
- Refresh the display periodically
- Handle user input

---

## Execution Flow

1. The application initializes the ncurses terminal interface.
2. CPU, memory, and process monitor modules are created.
3. Each refresh cycle reads system information from the `/proc` filesystem.
4. The collected statistics are displayed in the terminal.
5. The process repeats until the user exits the application.

---

## Design Highlights

- Modular C++ design
- Separation of CPU, memory, and process monitoring
- Direct interaction with the Linux `/proc` filesystem
- Terminal-based real-time monitoring using ncurses
- Makefile-based build system
