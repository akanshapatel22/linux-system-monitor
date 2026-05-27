#include "mem_monitor.h"
#include <fstream>
#include <sstream>
#include <string>

MemMonitor::MemMonitor() {}

MemStats MemMonitor::getStats() {
    std::ifstream file("/proc/meminfo");
    std::string line;
    MemStats stats = {0, 0, 0, 0};

    unsigned long total    = 0;
    unsigned long free_mem = 0;
    unsigned long buffers  = 0;
    unsigned long cache    = 0;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string key;
        unsigned long value;
        std::string unit;

        ss >> key >> value >> unit;

        if      (key == "MemTotal:")   total    = value;
        else if (key == "MemFree:")    free_mem = value;
        else if (key == "Buffers:")    buffers  = value;
        else if (key == "Cached:")     cache    = value;
    }

    /* Convert from kB to MB */
    stats.total_mb = total    / 1024;
    stats.free_mb  = free_mem / 1024;
    stats.cache_mb = (buffers + cache) / 1024;
    stats.used_mb  = stats.total_mb
                   - stats.free_mb
                   - stats.cache_mb;

    return stats;
}
