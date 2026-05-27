#ifndef PROC_MONITOR_H
#define PROC_MONITOR_H

#include <string>
#include <vector>

struct ProcStats {
    int         pid;
    std::string name;
    float       cpu_percent;
    float       mem_percent;
};

class ProcMonitor {
public:
    ProcMonitor();
    std::vector<ProcStats> getTopProcesses(int count);
};

#endif /* PROC_MONITOR_H */
