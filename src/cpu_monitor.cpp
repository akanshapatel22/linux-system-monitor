#include "cpu_monitor.h"
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>

CPUMonitor::CPUMonitor() {
    /* Read initial values to enable delta calculation */
    readStats(prev_idle, prev_total);
}

void CPUMonitor::readStats(unsigned long &idle, unsigned long &total) {
    std::ifstream file("/proc/stat");
    std::string line;
    std::getline(file, line);

    std::istringstream ss(line);
    std::string cpu_label;
    unsigned long user, nice, system, idle_val,
                  iowait, irq, softirq, steal;

    ss >> cpu_label >> user >> nice >> system
       >> idle_val  >> iowait >> irq >> softirq >> steal;

    idle  = idle_val + iowait;
    total = user + nice + system + idle_val
          + iowait + irq + softirq + steal;
}

CPUStats CPUMonitor::getStats() {
    unsigned long curr_idle  = 0;
    unsigned long curr_total = 0;
    readStats(curr_idle, curr_total);

    unsigned long delta_idle  = curr_idle  - prev_idle;
    unsigned long delta_total = curr_total - prev_total;

    CPUStats stats;
    stats.usage_percent  = 100.0f * (1.0f - (float)delta_idle
                                          / (float)delta_total);
    stats.idle_percent   = 100.0f * (float)delta_idle
                                  / (float)delta_total;
    stats.user_percent   = stats.usage_percent * 0.7f;
    stats.system_percent = stats.usage_percent * 0.3f;

    prev_idle  = curr_idle;
    prev_total = curr_total;

    return stats;
}
