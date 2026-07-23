# Linux System Monitor

A real-time system monitoring tool written in C++ on Linux, interfacing directly
with the /proc filesystem and system calls to track CPU, memory, and process-level
metrics for low-level performance analysis and system diagnostics.

## Overview

This project implements a lightweight, terminal-based system monitor that reads
kernel-exposed data from the /proc filesystem without relying on external libraries.
It demonstrates deep understanding of Linux internals, system calls, and real-time
performance monitoring — skills directly applicable to embedded Linux and driver
development roles.

## Features

- Real-time CPU usage monitoring using /proc/stat
- Memory usage monitoring (RAM, buffers, and cache statistics)
- Process monitoring using /proc entries with PID, process name, and CPU time statistics
- Terminal-based real-time monitoring interface using ncurses
- Configurable refresh rate

## Technical Details

| Parameter | Details |
|---|---|
| **Language** | C++11 |
| **Platform** | Linux |
| **Data Source** | /proc filesystem |
| **UI** | Terminal-based (ncurses) |
| **Build System** | Makefile |

## Project Structure
linux-system-monitor/
├── src/
│   ├── main.cpp          # Entry point and display loop
│   ├── cpu_monitor.cpp   # CPU usage from /proc/stat
│   ├── mem_monitor.cpp   # Memory stats from /proc/meminfo
│   └── proc_monitor.cpp  # Per-process stats from /proc/[pid]/stat
├── inc/
│   ├── cpu_monitor.h
│   ├── mem_monitor.h
│   └── proc_monitor.h
├── Makefile
└── README.md

## Key Concepts Demonstrated

- **/proc Filesystem:** Direct kernel interface for runtime system statistics
  without system call overhead
- **CPU Usage Calculation:** Delta-based tracking of idle vs total jiffies
  across refresh intervals
- **Memory Parsing:** Parsing /proc/meminfo fields for accurate RSS, VSZ,
  and cache breakdown
- **Process Enumeration:** Iterating /proc entries and parsing process information from /proc/[pid]/stat
- **Real-Time Refresh:** Non-blocking terminal updates using ncurses for
  live system visibility

## Tools & Environment

- GCC / G++ (C++11)
- GNU Make
- ncurses
- Linux
- GDB (Debugging)
- Valgrind for memory leak detection

## Skills Demonstrated

`C++` `Linux Internals` `/proc Filesystem` `System Calls` `Memory Management`
`Process Monitoring` `Real-Time Systems` `Performance Analysis` `Embedded Linux`
`Makefile` `GDB` `ncurses`
