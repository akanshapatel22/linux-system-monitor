#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include "cpu_monitor.h"
#include "mem_monitor.h"
#include "proc_monitor.h"

#define REFRESH_RATE_SEC 1

int main() {
    /* Initialize ncurses for terminal UI */
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);

    CPUMonitor    cpu;
    MemMonitor    mem;
    ProcMonitor   proc;

    while (true) {
        clear();

        /* Header */
        mvprintw(0, 0, "=== Linux System Monitor ===");
        mvprintw(1, 0, "Press 'q' to quit");

        /* CPU Section */
        mvprintw(3, 0, "--- CPU Usage ---");
        CPUStats cpu_stats = cpu.getStats();
        mvprintw(4, 0, "CPU Usage : %.2f%%", cpu_stats.usage_percent);
        mvprintw(5, 0, "User      : %.2f%%", cpu_stats.user_percent);
        mvprintw(6, 0, "System    : %.2f%%", cpu_stats.system_percent);
        mvprintw(7, 0, "Idle      : %.2f%%", cpu_stats.idle_percent);

        /* Memory Section */
        mvprintw(9, 0,  "--- Memory Usage ---");
        MemStats mem_stats = mem.getStats();
        mvprintw(10, 0, "Total  : %lu MB", mem_stats.total_mb);
        mvprintw(11, 0, "Used   : %lu MB", mem_stats.used_mb);
        mvprintw(12, 0, "Free   : %lu MB", mem_stats.free_mb);
        mvprintw(13, 0, "Cache  : %lu MB", mem_stats.cache_mb);

        /* Process Section */
        mvprintw(15, 0, "--- Top Processes ---");
        mvprintw(16, 0, "%-10s %-20s %-10s %-10s",
                 "PID", "Name", "CPU%", "MEM%");

        std::vector<ProcStats> procs = proc.getTopProcesses(5);
        int row = 17;
        for (const auto& p : procs) {
            mvprintw(row++, 0, "%-10d %-20s %-10.2f %-10.2f",
                     p.pid, p.name.c_str(),
                     p.cpu_percent, p.mem_percent);
        }

        refresh();

        /* Check for quit */
        int ch = getch();
        if (ch == 'q' || ch == 'Q') break;

        sleep(REFRESH_RATE_SEC);
    }

    endwin();
    return 0;
}
